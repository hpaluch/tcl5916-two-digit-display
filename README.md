# Connecting 7-segment 2-digit display to TCL5916

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
> in [TCL5916 data-sheet][TLC5916]. Just having simple formula
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
  definition of [TCL5916][TLC5916]
* [moje.lbr][moje.lbr] - my own part library (originally for Eagle 3/DOS)
  made in late 90's in college - 
  used definition of [2-digit HD-A544D LED display][HD-A544D]


# Setup

TODO


[HD-A544D]: https://www.gme.cz/led-display-14-2mm-red-hd-a544d
[moje.lbr]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/moje.lbr?raw=true
[TLC5916]: http://www.ti.com/lit/ds/slvs695d/slvs695d.pdf
[zlalanne/eagle-library]: https://github.com/zlalanne/eagle-library/blob/master/lbr/zlalanne.lbr
[PCB Eagle]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg.brd?raw=true
[PCB PDF]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-pcb.pdf?raw=true
[Schematic Eagle]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg.sch?raw=true
[Schematic PDF]: https://github.com/hpaluch/tcl5916-two-digit-display/blob/master/Eagle/tlc5916-2seg-sch.pdf?raw=true
[Eagle 9.3.0 Free]: https://www.autodesk.com/products/eagle/free-download

