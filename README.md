<a href="https://certification.oshwa.org/at000006.html" title="Open Source Hardware Association Certificate"><img align="right" src="docs/oshw.svg" alt="Open Source Hardware Association Certificate"></a>

# Mini SiPM Driver (SiD) Board

**This is the latest hardware revision 3.0. For older revisions, please have a look at the [other branches](https://github.com/OpenGammaProject/Mini-SiD/branches). A comparison between the revision 2 and 3 hardware can be found [here](https://hackaday.io/project/188090-mini-sipm-driver-board/log/217563-new-hardware-revision).**

**This project is on [Hackaday.io](https://hackaday.io/project/188090-mini-sipm-driver-board), where I also post project logs, progress updates and other announcements.**

Minimalistic board that allows you to quickly and easily utilize a silicon photomultiplier (SiPM) within your other projects. Supports a range of input voltages, has a digital (TTL) pulse output for the registered counts and a direct output for the SiPM pulses for easy expansion. Similar to the original [Open Gamma Detector](https://github.com/OpenGammaProject/Open-Gamma-Detector), but without any direct way to perform gamma spectroscopy.

<p align="center">
  <img alt="Photo of the detector board with mounted SiPM and crystal" title="Photo of the detector board with mounted SiPM and crystal" height="210px" src="docs/img1.jpg">
  <img alt="Photo of the detector board with mounted SiPM and crystal" title="Photo of the detector board with mounted SiPM and crystal" height="210px" src="docs/img2.jpg">
</p>

All you need to build your own scintillation counter is this board, a scintillator and SiPM. The benefits of such a scintillation counter are that you can use it just like a Geiger counter, but it's much more sensitive, can be smaller, doesn't need 300+ Volts and you can also use it to do spectroscopy with some additional components. It mostly only registers gamma radiation though, so keep that in mind!

## How To Get One

* For quick access and purchase of all the parts (PCB and BOM), you can use [Kitspace](https://kitspace.org/boards/github.com/OpenGammaProject/Mini-SiD/). Otherwise, use a PCB manufacturer and an electronics distributor of your choice and proceed on your own.

* The fully assembled board can also be purchased on my [Tindie store](https://www.tindie.com/products/29487/). With your purchase your are also supporting me in my efforts to maintain and improve this project, thanks!

<a href="https://www.tindie.com/stores/nuclearphoenix/?ref=offsite_badges&utm_source=sellers_NuclearPhoenix&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>

**In both cases you will also need to buy a SiPM (e.g. the MICROFC-60035-SMT-TR) and scintillator (NaI(Tl) recommended) separately at a distributor of your choice.**

## Specifications

Here are some of the most important key facts:

* Compact design: Total size 100 x 25 mm. 53 x 25 mm area for electronics and additional 47 x 25 mm to mount a small scintillator.
* Input voltage: 3.2 V - 5.5 V.
* Low-voltage device: No HV needed like with a photomultiplier tube.
* SiPM voltage range from 27.5 V to 33.8 V.
* Low power consumption: <5 mA @ 5 V in standard operation.
* Adjustable gain for the SiPM pulses, also affects pulse decay time and therefore dead time.
* TTL output for counting pulses or time-over-threshold applications.
* Additional raw pulse output if you want to manipulate the signal or use it for spectroscopy.
* Dead time only limited by the speed of the scintillator and the gain. Typically <10 µs.
* Only needs an additional cheap microcontroller to, for example, build a simple scintillation counter.

## Working Principle

Here is a nice flow chart explaining how this device roughly works:

![Working Principle Flow Chart](docs/flow.drawio.svg)

## Hardware

Hardware design has been done with [EasyEDA](https://easyeda.com/) and all the needed files for you to import the project as well as the schematic can be found in the `hardware` folder. There is also a Gerber file available for you to go directly to the PCB manufacturing step.

![Front side rendering of the PCB](docs/pcb_front.png)

![Back side rendering of the PCB](docs/pcb_back.png)

This project utilizes a silicon photomultiplier (short SiPM) which is way smaller and more robust than a traditional photomultiplier tube and does not need a high-voltage supply (traditionally  around 1000 V). Here are some very helpful in-depth datasheets about the particular MicroFC SiPM used here:

* [C-Series SiPM Sensors datasheet](https://www.onsemi.com/pdf/datasheet/microc-series-d.pdf)
* [Linearity of the Silicon Photomultiplier](https://www.onsemi.com/pub/Collateral/AND9776-D.PDF)
* [Introduction to the SiliconPhotomultiplier (SiPM)](https://www.onsemi.com/pub/Collateral/AND9770-D.PDF)
* [Biasing and Readout of ON Semiconductor SiPM Sensors](https://www.onsemi.com/pub/Collateral/AND9782-D.PDF)

PCB size is 10 x 2.5 cm. If you don't need the additional space to mechanically mount the SiPM/scintillator assembly to the rest of the detector board, you can just cut it off at the white line and you're left with a much smaller detector (~5.3 x 2.5 cm).

The PCB is single-sided and mostly uses 0603 components or comparable IC packages to make it possible to solder it by hand or buy it cheaply online and at the same time keep it as small as reasonable.

The TTL-compatible `INT` output is an active high pin!

**Here is a helpful image about the potentiometer settings (turning increases each parameter):**

![Potentiometer Controls](docs/controls.png)

## Scintillation Counter

A great project utilizing the Mini SiD is building a scintillation counter, which can be much more powerful than a geiger counter while being safer to use, because of the relatively low voltages.

One great example build has been done by [RD-Gamma](https://rd-gammaspectra.xyz), who built one such device using a russian scintillator and a Broadcom AFBR SiPM.

[![Photo of the DIY scintillation counter](docs/example.jpg)](https://rd-gammaspectra.xyz/?p=255)

## Example Results

Here is a small collection of example results I got when measuring the count rate at the TTL output with my small 18 x 30 mm scintillator and a 6 mm MicroFC SiPM.

| Sample | Result Average [cps] |
| --- | --- |
| Background | 24 |
| Ionization Smoke Detector | 230 |
| Cup with Uraninite glaze | 64 |
| 5g LYSO scintillator | 34 |

## Some Ideas

### Coincidence Measurements

You can tie multiple boards' `INT` outputs together in an `AND` gate chip to only trigger a signal when all boards detected something. These AND gate ICs are very cheap, readily available and the output can then go into a microcontroller interrupt pin to count the gamma events.

To make the timing a bit easier for the gates and to consider delays, you can feed the board `INT` output into a [monostable multivibrator circuit](https://en.wikipedia.org/wiki/Multivibrator#Monostable) such as an NE555 timer IC. This will allow you to stretch all the signals by a certain time factor you can set.

---

Thanks for reading.
