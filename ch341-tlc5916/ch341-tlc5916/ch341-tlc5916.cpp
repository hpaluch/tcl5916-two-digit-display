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
#define HPCH_MASK_CLK  (1 << HPCH_BIT_CLK)
#define HPCH_MASK_MOSI (1 << HPCH_BIT_MOSI)
#define HPCH_MASK_MISO (1 << HPCH_BIT_MISO)


#define HPCH_TLC5916_MASK_LE  HPCH_MASK_CS0
#define HPCH_TLC5916_MASK_CLK HPCH_MASK_CS1
#define HPCH_TLC5916_MASK_SDI HPCH_MASK_MOSI


// send byte to TLC5916 using custom clocking (to avoid clock on latchEnable)
static int HpCh_Tlc5916_SendByte(ULONG iIndex, BYTE b, BOOL latchEnable){
	BYTE ioBuf[256];
	int  ioIdx = 0;
	int  i = 0;

	memset(ioBuf,0,sizeof(ioBuf));
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

	// set CS0 (LE), CS1 (CLK) and MOSI (SDI) as output
	// all pins active on high
	if (!CH341Set_D5_D0(iIndex,HPCH_TLC5916_MASK_LE|HPCH_TLC5916_MASK_CLK|HPCH_TLC5916_MASK_SDI,0 )){
			printf("CH341_D5_D0 failed\r\n");
			ret = EXIT_FAILURE;
			goto exit1;
	}

	// to have nice data on logic analyzer
	b = 0xa5;
	printf("Sending 0x%x to TLC5916...\n",b);
	if (!HpCh_Tlc5916_SendByte(iIndex,b,TRUE)){
		goto exit1;
	}


	for(i=0;i<5;i++){
		printf("Sending 0x%x to TLC5916...\n",i);
		if (!HpCh_Tlc5916_SendByte(iIndex,(BYTE)i,TRUE)){
			goto exit1;
		}
		Sleep(1000);
	}

	ret = EXIT_SUCCESS;
exit1:
	CH341CloseDevice(iIndex);
exit0:
	return ret;
}

