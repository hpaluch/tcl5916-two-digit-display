# Connecting 7-segment 2-digit display to TLC5916

Here is project how to use 2x TLC5916 with 7-segment 2-digit
LED display.

> WARNING!
>
> This project is in design stage. It was not yet verified!

# Design files

> Early design comments (prototype on bread-board):
>
> Use lower value for `R1` and `R2` - `1K` seems to be fine.
> I guessed the `5K` values because
> I can't understand the `R-EXT` calculations
> in [TLC5916 data-sheet][TLC5916]. Just having simple formula
> like `R_ext (Ohm) = x * I_led (mA)` would be fine...


Design was done in [Eagle 9.3.0 Free][Eagle 9.3.0 Free]

Schematic is:

![Schematic of TLC5916 with LED display](https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tcl5916-2seg-schematic.png?raw=true) 

Also in:
* [PDF version][Schematic PDF]
* [Eagle 9.3.0 Free version][Schematic Eagle]

PCB design is:


![PCB of TLC5916 with LED display](https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tcl5916-2seg-pcb.png?raw=true) 

Also in:
* [PDF version][PCB PDF]
* [Eagle 9.3.0 Free version][PCB Eagle]


Following Eagle libraries were used:

* [zlalanne/eagle-library][zlalanne/eagle-library] for
  definition of [TLC5916][TLC5916]
* [moje.lbr][moje.lbr] - my own part library (originally for Eagle 3/DOS)
  made in late 90's in college - 
  used definition of [2-digit HD-A544D LED display][HD-A544D]


# Bill of Material

* 2x [TLC5916][TLC5916 - tme.eu] - from tme.eu
* LED display [HD-A544D][HD-A544D] - from gme.cz
* 2x 1K resistor - from my inventory
* 2x 100nF capacitor - from my inventory
* pinhead connector 6 pins in 1 row - used
  20-pin [DS1021-1x20SF1-10][DS1021-1x20SF1-10] - from gme.cz


# Connecting TLC5916 to Interfaces

There are following subprojects:
* [Connecting TLC5916 to PC using LC 341A USB adapter][Connecting TLC5916 to PC using LC 341A USB adapter] - connecting
  this board to PC with USB adapter

# Known bugs/limitations

Design shortcomings:
* digital signals (`CLK`, `SDI`, `SDO`, `LE`) should be routed more
  carefully - not crossing `LED` lines (where are high current spikes).
* LED display power supply pins (`13` and `14`) should be
  wired  to `+5V` supply through jumper pins
  to allow custom power supply (for example `+12V`) different
  from main circuit `+5V` power supply.

[DS1021-1x20SF1-10]: https://www.gme.cz/oboustranny-kolik-s1g20-2-54mm-v-13-80mm
[TLC5916 - tme.eu]: https://www.tme.eu/en/details/tlc5916in/led-drivers/texas-instruments/
[Connecting TLC5916 to PC using LC 341A USB adapter]: https://github.com/hpaluch/tcl5916-two-digit-display/tree/master/ch341-tlc5916
[HD-A544D]: https://www.gme.cz/led-display-14-2mm-red-hd-a544d
[moje.lbr]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/moje.lbr?raw=true
[TLC5916]: http://www.ti.com/lit/ds/slvs695d/slvs695d.pdf
[zlalanne/eagle-library]: https://github.com/zlalanne/eagle-library/blob/master/lbr/zlalanne.lbr
[PCB Eagle]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg.brd?raw=true
[PCB PDF]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-pcb.pdf?raw=true
[Schematic Eagle]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg.sch?raw=true
[Schematic PDF]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-sch.pdf?raw=true
[Eagle 9.3.0 Free]: https://www.autodesk.com/products/eagle/free-download

