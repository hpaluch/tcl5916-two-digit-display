# Connecting TLC5916 to PC using LC 341A USB adapter

> WARNING!
>
> Work in progress. Currently sends `0` to `0xF` decoded to
> 1st digit on LED display.

Please see [master project README][2-digit 7-segment LED with TLC5916]
for Schematic and/or PCB.

Here is VisualStudio 2010 project to control 
[2-digit 7-segment LED with TLC5916][2-digit 7-segment LED with TLC5916]
using 
[CH341A USB to UART/IIC/SPI/TTL/ISP adapter EPP/MEM Parallel converter][CH341A USB to UART/IIC/SPI/TTL/ISP adapter EPP/MEM Parallel converter]

Please see one of my CH341 projects, for example
[Accessing Microwire EEPROM 93LC86 from LC CH341A USB using SPI mode][Accessing Microwire EEPROM 93LC86 from LC CH341A USB using SPI mode]
for generic HW/SW setup instructions. Here is project specific info only.


# Wiring LC341 with [TLC5916 LED board][2-digit 7-segment LED with TLC5916] and Logic Analyzer

Wire all 3 things together using table below:

|CH341A pin|Direction from CH341A|TLC5916 pin|Logic Analyzer pin|Description|
|----------|---------------------|-----------|------------------|-----------|
|GND|N/A|GND|GND|Common ground|
|CS0|Output|LE|CH1|Latch Enable - active in HIGH|
|CS1|Output|CLK|CH2|Clock - active in rising edge|
|CS2|Output|N/A|CH4|Fake /SS (slave select)<sup>1</sup>|
|MOSI|Output|SDI|CH3|serial data for TLC5916|

NOTE: The [TLC5916 LED board] uses its own `+5V` power supply,
      because the drawn current can be quite high - because
      of up to 16 LED lighting together...

<sup>1</sup>) trick so SPI decoder in Logic Analyzer will work with these data
  (that are not otherwise SPI compatible)

# Logic Analyzer output

Here is sample output sending 0xA5 data to TLC5916 (just for test):

![Sending data to TCL5916](https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/ch341-tlc5916/assets/PulseView/tcl5916-sending-data.png?raw=true)


[Accessing Microwire EEPROM 93LC86 from LC CH341A USB using SPI mode]: https://github.com/hpaluch/ch341-spi-93lc86 
[CH341A USB to UART/IIC/SPI/TTL/ISP adapter EPP/MEM Parallel converter]: http://www.chinalctech.com/cpzx/Programmer/Serial_Module/2019/0124/266.html 
[2-digit 7-segment LED with TLC5916]: https://github.com/hpaluch/tcl5916-two-digit-display
