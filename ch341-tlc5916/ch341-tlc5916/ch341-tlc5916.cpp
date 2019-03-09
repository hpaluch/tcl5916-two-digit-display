//
// ch341-tlc5916.cpp : Controlling 2-digit 7-segment display HD-A544D using TCL5916 LED driver
//

#include "stdafx.h"

// bit numbers for D7-D0 in bit-stream modes
#define HPCH_BIT_CS0  0
#define HPCH_BIT_CS1  1
#define HPCH_BIT_CS2  2
#define HPCH_BIT_CLK  3
#define HPCH_BIT_MOSI 5
#define HPCH_BIT_MISO 7

#define HPCH_MASK_CS0  (1 << HPCH_BIT_CS0)
#define HPCH_MASK_CS1  (1 << HPCH_BIT_CS1)
#define HPCH_MASK_CS2  (1 << HPCH_BIT_CS2)
#define HPCH_MASK_CLK  (1 << HPCH_BIT_CLK)
#define HPCH_MASK_MOSI (1 << HPCH_BIT_MOSI)
#define HPCH_MASK_MISO (1 << HPCH_BIT_MISO)


#define HPCH_TLC5916_MASK_LE  HPCH_MASK_CS0
#define HPCH_TLC5916_MASK_CLK HPCH_MASK_CS1
#define HPCH_TLC5916_MASK_SDI HPCH_MASK_MOSI
// fake Slave Select /SS - to allow SPI decoder to work in Logic Analyzer
#define HPCH_LOCIC_MASK_FAKE_SS HPCH_MASK_CS2


// maps 1st digit value 0 to 0xf to 7-segment display digit...
//     a
//   +---+
//  f| g |b
//    ---
//  e|   |c
//    ---   +p
//     d   
// 1st digit is mapped to byte:
//    76543210
//    bagfedcp

static BYTE DIGI1_MAP[16] = {
                        //    7654 3210
                        //    bagf edcp       
	0xde,  // 0 = abcdef => 0b1101 1110
	0x82,  // 1 = bc     => 0b1000 0010
	0xec,  // 2 = abged  => 0b1110 1100
	0xe6,  // 3 = abcdg  => 0b1110 0110
	0xb2,  // 4 = bcfg   => 0b1011 0010
	0x76,  // 5 = acdfg  => 0b0111 0110
	0x7e,  // 6 = acdefg => 0b0111 1110
	0xc2,  // 7 = abc    => 0b1100 0010
	0xfe,  // 8 = abcdefg=> 0b1111 1110
	0xf6,  // 9 = abcdfg => 0b1111 0110
	0xfa,  // A = abcefg => 0b1111 1010
	0x3e,  // b = cdefg  => 0b0011 1110
	0x5c,  // C = adef   => 0b0101 1100
	0xae,  // d = bcdeg  => 0b1010 1110
	0x7c,  // E = adefg  => 0b0111 1100
	0x78  // F = aefg   => 0b0111 1000
};

static BYTE HpCh_Tlc5916_Map1stDigit(BYTE digNum){
	return DIGI1_MAP[ digNum & 0xf ];
}

// maps 2nd digit value 0 to 0xf to 7-segment display digit...
//     a
//   +---+
//  f| g |b
//    ---
//  e|   |c
//    ---   +p
//     d   
// 2nd digit is mapped to byte:
//    76543210
//    edgcpbaf

static BYTE DIGI2_MAP[16] = {
                        //    7654 3210
                        //    edgc pbaf       
	0xd7,  // 0 = abcdef => 0b1101 0111
	0x14,  // 1 = bc     => 0b0001 0100
	0xe6,  // 2 = abged  => 0b1110 0110
	0x76,  // 3 = abcdg  => 0b0111 0110
	0x35,  // 4 = bcfg   => 0b0011 0101
	0x73,  // 5 = acdfg  => 0b0111 0011
	0xf3,  // 6 = acdefg => 0b1111 0011
	0x16,  // 7 = abc    => 0b0001 0110
	0xf7,  // 8 = abcdefg=> 0b1111 0111
	0x77,  // 9 = abcdfg => 0b0111 0111
	0xb7,  // A = abcefg => 0b1011 0111
	0xf1,  // b = cdefg  => 0b1111 0001
	0xc3,  // C = adef   => 0b1100 0011
	0xf4,  // d = bcdeg  => 0b1111 0100
	0xe3,  // E = adefg  => 0b1110 0011
	0xa3   // F = aefg   => 0b1010 0011
};

static BYTE HpCh_Tlc5916_Map2ndDigit(BYTE digNum){
	return DIGI2_MAP[ digNum & 0xf ];
}


// send byte to TLC5916 using custom clocking (to avoid clock on latchEnable)
static int HpCh_Tlc5916_SendByte(ULONG iIndex, BYTE b, BOOL latchEnable){
	BYTE ioBuf[256];
	int  ioIdx = 0;
	int  i = 0;

	memset(ioBuf,0,sizeof(ioBuf));
	// lower fake /SS for SPI decoder in Logical Analyzer
	ioBuf[ ioIdx++ ] = 0;
	for(i=0;i<8;i++){
		BYTE ioData = ( (b & ( 1 << (8-i-1))) ? HPCH_TLC5916_MASK_SDI : 0);
		ioBuf[ ioIdx++ ] = ioData;
		ioBuf[ ioIdx++ ] = ioData | HPCH_TLC5916_MASK_CLK;
		ioBuf[ ioIdx++ ] = ioData & ~ HPCH_TLC5916_MASK_CLK;
	}

	if (latchEnable){
		// set LE *without* setting clock - this is the sole reason why
		// we can't use CLK output from CH341A
		ioBuf[ ioIdx++ ] = HPCH_TLC5916_MASK_LE;
		ioBuf[ ioIdx++ ] = 0;
	}
	// raise fake /SS for SPI decoder in Logical Analyzer
	ioBuf[ ioIdx++ ] = HPCH_LOCIC_MASK_FAKE_SS;
	printf("ioIdx==%u\n",ioIdx);
	if (!CH341BitStreamSPI(iIndex,ioIdx,ioBuf)){
		fprintf(stderr,"CH341BitStreamSPI() failed\n");
		return FALSE;
	}
	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int      i = 0;
	BOOL   ret  = EXIT_FAILURE;
	HANDLE h341 = NULL;
	ULONG iIndex = 0; // first device
	BYTE  b = 0;

	printf("CH341 library version: %lu\n", CH341GetVersion());

	printf("Opening device# %lu\r\n", iIndex);
	h341 = CH341OpenDevice(iIndex);
	if (h341 == NULL){
		fprintf(stderr, "CH341OpenDevice(iDevIndex=%lu) failed\r\n", iIndex);
		goto exit0;
	}

	// NOTE: must be called *after* CH341OpenDevice()
	printf("CH341 driver  version: %lu\n", CH341GetDrvVersion());

	// set CS0 (LE), CS1 (CLK), CS2 (Fake /SS for Analyzer) and MOSI (SDI) as output
	// all pins but "Fake /SS" active on high
	if (!CH341Set_D5_D0(iIndex,
			HPCH_TLC5916_MASK_LE|HPCH_TLC5916_MASK_CLK|HPCH_TLC5916_MASK_SDI|HPCH_LOCIC_MASK_FAKE_SS,
			HPCH_LOCIC_MASK_FAKE_SS )){
			printf("CH341_D5_D0 failed\r\n");
			ret = EXIT_FAILURE;
			goto exit1;
	}

#if 0
	// to have nice data on logic analyzer
	b = 0xa5;
	printf("Sending 0x%x to TLC5916...\n",b);
	if (!HpCh_Tlc5916_SendByte(iIndex,b,TRUE)){
		goto exit1;
	}
#endif

	for(i=0;i<16;i++){
		char dummy[16];

		BYTE d1 = HpCh_Tlc5916_Map1stDigit((BYTE)i);
		BYTE d2 = HpCh_Tlc5916_Map2ndDigit((BYTE)i);

		printf("Sending 2nd digit 0x%x =>  0x%x to TLC5916...\n",i,d2);
		if (!HpCh_Tlc5916_SendByte(iIndex,d2,FALSE)){
			goto exit1;
		}

		printf("Sending 1st digit 0x%x =>  0x%x to TLC5916...\n",i,d1);
		if (!HpCh_Tlc5916_SendByte(iIndex,d1,TRUE)){
			goto exit1;
		}
		printf("Press ENTER to continue...\n");
		fgets(dummy,sizeof(dummy)-1,stdin);
		//Sleep(1000);
	}

	ret = EXIT_SUCCESS;
exit1:
	CH341CloseDevice(iIndex);
exit0:
	return ret;
}

