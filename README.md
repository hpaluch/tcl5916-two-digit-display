# Connecting 7-segment 2-digit display to TLC5916

Here is project how to use 2x TLC5916 with 7-segment 2-digit
LED display.


![PCB with TLC5916 in action](https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/assets/tcl5916-pcb.jpg?raw=true) 

Board revision 1.0 (initial) is shown on picture.


Project status:

Board was tested successfully. See 
subproject [Connecting TLC5916 to PC using LC 341A USB adapter][Connecting TLC5916 to PC using LC 341A USB adapter] for example.


# Design files

Design files are in revision 1.1, 2019-03-10. New values
of R1 and R2 were computed using this setup:

The relation between R<sub>ext</sub> and I<sub>led</sub> is following
(default configuration after power-up):

1. To get `I_led` in `[mA]` from `R_ext` in `[kOhm]` use:

   ```
   I_led = 1.25 * 15 / R_ext = 18.75 / R_ext
   ```
   
   For example (used in our circuit now): `R_ext = 1 [kOhm]` => `I_led = 18.75 [mA]` 
   
2. To get `R_ext` in `[kOhm]` from `I_led` in `[mA]` use:

   ```
   R_ext = 1.25 * 15 / I_led = 18.75 / I_led
   ```    


   For example: `I_led = 20 [mA]` => `R_ext = 0.937 [kOhm] = 937 [Ohm]`


Also see `Figure 4. Output Current vs Output Voltage` in data sheet
to verify that `VLED` (voltage connected to common LED anode) 
must be greater than `Voltage drop on LED` + `1V` (roughly).
In our case using `+5V` voltage is OK.


Design was done in [Eagle 9.3.0 Free][Eagle 9.3.0 Free]

Schematic is:

![Schematic of TLC5916 with LED display](https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-schematic.png?raw=true) 

Also in:
* [PDF version][Schematic PDF]
* [Eagle 9.3.0 Free version][Schematic Eagle]

PCB design is:


![PCB of TLC5916 with LED display](https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-pcb.png?raw=true) 

Also in:
* [PDF version][PCB PDF]
* [Eagle 9.3.0 Free version][PCB Eagle]


Following Eagle libraries were used:

* [zlalanne/eagle-library][zlalanne/eagle-library] for
  definition of [TLC5916][TLC5916]
* [moje.lbr][moje.lbr] - my own part library (originally for Eagle 3/DOS)
  made in late 90's in college - 
  used definition of [2-digit HD-A544D LED display][HD-A544D]

Board was made by [gatema.cz][gatema.cz] for
around 700 CZK (roughly 32 USD) including:

* 2 layers
* plated holes
* solder mask
* top silk screen

NOTE: Remember to follow instructions in 
[eagle-dokumentace.pdf][eagle-dokumentace.pdf]
from [Technicke informace][Technicke informace]
(provided in Czech only)


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

[Technicke informace]: https://www.gatema.cz/plosne-spoje/technicke-informace/default/7?do=reloadInfo
[eagle-dokumentace.pdf]: http://www.gatema.cz/file-link/eagle-dokumentace.pdf
[gatema.cz]: https://extranet.gatema.cz/dps/konfiguratorpool.aspx
[DS1021-1x20SF1-10]: https://www.gme.cz/oboustranny-kolik-s1g20-2-54mm-v-13-80mm
[TLC5916 - tme.eu]: https://www.tme.eu/en/details/tlc5916in/led-drivers/texas-instruments/
[Connecting TLC5916 to PC using LC 341A USB adapter]: https://github.com/hpaluch/tlc5916-two-digit-display/tree/master/ch341-tlc5916
[HD-A544D]: https://www.gme.cz/led-display-14-2mm-red-hd-a544d
[moje.lbr]: https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/Eagle/moje.lbr?raw=true
[TLC5916]: http://www.ti.com/lit/ds/slvs695d/slvs695d.pdf
[zlalanne/eagle-library]: https://github.com/zlalanne/eagle-library/blob/master/lbr/zlalanne.lbr
[PCB Eagle]: https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/Eagle/tlc5916-2seg.brd?raw=true
[PCB PDF]: https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-pcb.pdf?raw=true
[Schematic Eagle]: https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/Eagle/tlc5916-2seg.sch?raw=true
[Schematic PDF]: https://github.com/hpaluch/tlc5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-sch.pdf?raw=true
[Eagle 9.3.0 Free]: https://www.autodesk.com/products/eagle/free-download

