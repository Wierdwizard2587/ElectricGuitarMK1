# The Electronic Guitar MK1

<img src="https://github.com/user-attachments/assets/6f7fdf49-825d-451c-a7b9-8be3157fd3e8" data-canonical-src="https://github.com/user-attachments/assets/6f7fdf49-825d-451c-a7b9-8be3157fd3e8" width="275" height="400"/>

<img src="https://github.com/user-attachments/assets/fa07d7f7-db8a-4da3-886a-537a519272df" data-canonical-src="https://github.com/user-attachments/assets/fa07d7f7-db8a-4da3-886a-537a519272df" width="275" height="400"/>

<img src="https://github.com/user-attachments/assets/d93b2070-a9af-42f3-9944-c3cdc3873ebc" data-canonical-src="https://github.com/user-attachments/assets/d93b2070-a9af-42f3-9944-c3cdc3873ebc" width="275" height="400"/>


## Table of Contents

- [Overview](#overview)
- [My Prior Background](#my-prior-background)
- [Features](#features)
  - [AFPI Features](#afpi-features)
  - [Power Supply Features](#power-supply-features)
  - [RGB Lighting Features](#rgb-lighting-features)
  - [Physical Design Features](#physical-design-features)
  - [Guitar Specific Features](#guitar-specific-features)
- [Electric Guitar MK0 First attempt](#electric-guitar-mk0-first-attempt)
- [Skills learnt](#skills-learnt)
- [Technical In Depth](#technical-in-depth)


## Overview
During the second half of 2023, I began experimenting with a concept of an 'all in one portable electric guitar'. The device would contain built in electronics for digital audio effects and signal modulation with an optional audio output between a 1 watt amplifier and speaker, headphone amp with 3.5mm jack, or a 1/4" jack for aux out for further modulation and amplification, all of which powered by either a removable rechargable battery or 2.5mm DC jack. My first attempt at this concept to put it simply was a failure, but a neccesary one. Read [First Attempt Mk0](#electric-guitar-mk0-first-attempt) for the full breakdown of my first attempt. 

After my failed attempt I spent 6 months learning electrical concepts through both personal research and Uni as at this point I switched degrees to Electrical Engineering as I found the hardware aspect of electronics fascinating, mostly because of this project. I went down routes of different analog guitar effect and amplifier circuits to get a footing in circuit design and electrical principles, understanding how different components and layouts modified electrical signals. I even went as far as experimenting with different methods of creating my own PCB boards (chemical etching and CNC milling) and smt stencils with relative success (although i ended up just ordering the boards for simplicity). While I ended up not using analog circuitry for the audio modulation (execpt for amplification) and instead persued a digital route, the experience and knowledge gained in this period was instrumental in the projects success as it let apply my electrical theory knowledge and grow from any mistakes made along the way. Read [Skills Obtained](#skills-learnt) to understand the other various processes and skills I learnt, both hardware and software to design, test, machine and assemble the guitar.

After this period of research, planning, design and experimentation, I finally was ready to begin the excecution of the Electronic Guitar Mk1. I initially had 2 Concepts for how the Audio effect system would integrate with the guitar signal and be manipulated by the user:
1. Physical analog effects with digitally controlled potentiometers controlled by a micro controller
2. digitally programmed effects with a DAC and audio CODEC

After the failure of the raspberry Pi in Mk0, I was inclined to persue the first option, however the inability to add new effects (without a removable cartridge setup) was impractical to me as it was space intensive, more costly and didnt really fit into the ethos of the project. Not only that but the interfacing between the analog circuits and the digital microcontroller was a challenge. I intended to use the Teensy 4.0 as it was compact, relatively  power efficent and packed a massive punch in its speed and memory, and between this MCU and the FX circuits i intended to use either Digital potentiometers like the X9C104, or Light dependent Resistors (LDR) to 'Vactrol' the value of resistors in the analog FX circuits to mimic the use of turning Potentiometers. These both ended up being very impractical as the Digi Pots had very low voltage and current tolerances, and the LDRs were inprecice due to their logarithmic nature, not to mention both costing alot per unit. 

After a few months of experimentation I made the decision to persue fully digital FX, and lucky for me my chosen microcontroller had possessed this ability all along, only needing a audio Codec to handle the DAC conversion and manipulation. After even more research into the matter and a bit of tinkering i had a fully fledged system that had 4 rotary encoders for controlling parameters and navigating the UI, an OLED screen to display the parameter values and the UI, and a home button. pairing these features with the teensy and CODEC I was able to have a number of effects that I could tweak with code, as well as modify the audio output between the CODECS headphone amp, a generic AUX out and a 1 watt amplifier circuit that lead to a 8ohm speaker. Through the use of KiCAD I designed the single Layer PCB to mount and connect the various peripherals to the Teensy Micro Controller and CODEC with JST Connectors for easy assembly. 

## My Prior Background
I had started my Computer Science degree at the start of 2023 and before that had fiddled around with arduino and ESP32 Microcontroller projects, creating basic circuits and novice C programming with some very basic electrical theory, however this project was nothing like I had ever attempted. I also had some experience with woodworking through high school and personal jobs in the shed at home, but the craftmanship I needed for this task was also not ready. While my background was rather unimpressive, I was determined to complete this project myself by any means. This of course meant a great deal of learning and problem solving, and over the next 1.5 years (august 2023 - december 2024) I did sought out to do just that. Read












## Features
The features of this Guitar are seperated into the following sections:

### AFPI Features:
  - **Teensy 4.0 microcontroller:**
    - ARM Cortex M7 600MHz 
    - 2mB Flash
    - 1mB RAM
    - 40 GPIO pins
    - 100mA @ 5V
   
    <br> 
  - **Teensy Audio Shield Rev D2:**
    - SGTL5000 Audio Codec
    - integrated Headphone Amp
    - SD Card Slot

    <br>
  - **Power regulation**
    - Recieves power input from battery/DC jack
    - L7805 LDO regulator to reduce voltage to 5V for Digital Circuit components
    - uses regular voltage from input for speaker amp for a louder sound

  
    <br> 
  - **Adafruit IC2 Quad Rotary Encoder Board:**
    - Communication to Microcontroller via IC2 protocol
    - 1x4 20 position rotary encoders with push down buttons
   
     <br> 
  - **2.42 inch 128*64 OLED Display Module:**
    - SSD1306 OLED display library
   
    <br> 
  - **1 watt Speaker amplifier:**
    - lm386 op amp
    - trimmable Volume and Gain for installation
    - based on Ruby Amp design
   
    
  - Firmware switchable audio output between Built in speaker, Headphones or Aux out
  - Aux in 3.5mm jack for playing external audio from other devices
  - SD card memory to recall saved user settings for effects and other settings

<img src="https://github.com/user-attachments/assets/5239486c-7751-4ee9-8c51-16a76888f950" data-canonical-src="https://github.com/user-attachments/assets/5239486c-7751-4ee9-8c51-16a76888f950" width="275" height="400" />
<img src="https://github.com/user-attachments/assets/2b61481e-fd04-4a99-8314-2ab62f885f4d" data-canonical-src="https://github.com/user-attachments/assets/2b61481e-fd04-4a99-8314-2ab62f885f4d" width="275" height="400"/>
<img src="https://github.com/user-attachments/assets/2b68e03b-8055-459c-a632-ab9024afa71e" data-canonical-src="https://github.com/user-attachments/assets/2b68e03b-8055-459c-a632-ab9024afa71e" width="275" height="400"/>
<img src="https://github.com/user-attachments/assets/63045354-3f7c-42b4-bcbc-4b9c1ad852f8" data-canonical-src="https://github.com/user-attachments/assets/63045354-3f7c-42b4-bcbc-4b9c1ad852f8" width="400" height="275"/>

<img src="https://github.com/user-attachments/assets/148f8853-0d81-427b-8be9-8154661c2e9d" data-canonical-src="https://github.com/user-attachments/assets/148f8853-0d81-427b-8be9-8154661c2e9d" width="400" height="275"/>




### Power Supply Features:
  - Power supply from either DC 2.5mm Barrel Connector OR 3500mAh battery
  - switches to wired power supply over the battery automatically when plugged in

  - **DC Input:**
    - 2.5mm DC 
    - 7V to 18V input
  
  
  - **Removable 3500mAh Battery:**
    - 4S 18650 3.7V Li ion Battery cell arrangement
    - 16.8 Nominal Voltage
    - 10.5V over-discharge and 17V over-charge protection
    - magnetic connecting pins between battery casing and built-in battery slot in guitar
    - ~12hrs run time when operating speaker on maximum volume, full LED brightness and OLED brightness.
    - Run time increases greatly when limiting brightness and audio settings slightly
    - Capability to provide Battery charge to Microcontroller in future modifications

<img src="https://github.com/user-attachments/assets/a88d6ac0-515a-4c26-8ed4-063b8bcff47a" data-canonical-src="https://github.com/user-attachments/assets/a88d6ac0-515a-4c26-8ed4-063b8bcff47a" width="275" height="400"/>


### RGB Lighting Features:
  - 1x6 row of WS2812B 5050 SMD NeoPixel RGB LED's
  - each LED uniquely addressable via IC2 Protocol, allowing for any colour and brightness on each LED
  - Control the LEDs settings and the preset effect styles selectable through the User Interface
  - 5V operating Voltage and data supplied from AFPI to RGB lighting PCB
  - RGB PCB including extra Data Output for modular expansion of lighting to other areas of the Guitar
  - RGB PCB encased in a 3d printed mounting bracket to fit in the body, as well as to attach clear acrylic cover plate


https://github.com/Wierdwizard2587/ElectricGuitarMK1/raw/refs/heads/main/Progress%20Photos/Woodworking/IMG_9428.MOV


### Physical Design Features:
  - Custom designed Body shape
  - Red Ceder wood for body
  - CNC milled Acrylic Top and Back plates for switch plates and wire route coverings
  - 3D printed Components for mounting electrical components into Body as modular sections

<img src="https://github.com/user-attachments/assets/9df731cb-8994-4f1a-941f-662791b46a10" data-canonical-src="https://github.com/user-attachments/assets/9df731cb-8994-4f1a-941f-662791b46a10" width="275" height="400"/>

### Guitar specific Features:
  - SSH passive pickup layout, with pins available for active pickups
  - 22 Fret stratocaster syle neck
  - 5 way pickup selector switch layout
  - 1x master Volume potentiometer
  - 1x master Gain potentiometer









## Electric Guitar MK0 First attempt
The goal of this attempt was to retro fit a cheap electric guitar with electronics to create a cheap, simple portable electric guitar. Oh how wrong i was. With some moderate experience in playing with arduino's and Raspberry Pi's, a good bit of wood working experience, and no electrical engineering experience, I set out on accomplishing my goal.

<img src="https://github.com/user-attachments/assets/6be55a72-e7aa-4a15-b726-ad1f1358878a" data-canonical-src="https://github.com/user-attachments/assets/6be55a72-e7aa-4a15-b726-ad1f1358878a" width="275" height="400"/>

For the Guitar itself i had a chinese strat laying around that i found second hand at an Op shop for 20$ AUD that i never used, because obviously it sounded terrible. The electronics were barely working, it was missing a tuning peg and just wasn't in good condition! but after cleaning it up, re wiring it with new cheap pickups and new tuning pegs, it was somewhat playable. I then mangled the guitar by routing out long wire tracks and spots for components among other things. I reckon it was less then half the weight of its former self when i was done with it. I repainted The boddy and neck Black and moved on to the electronics.

<img src="https://github.com/user-attachments/assets/ff773c03-f57a-496b-be22-04634716b997" data-canonical-src="https://github.com/user-attachments/assets/ff773c03-f57a-496b-be22-04634716b997" width="275" height="400"/>
<img src="https://github.com/user-attachments/assets/0ef9ab9a-f143-429b-a4f2-014b8baf1da7" data-canonical-src="https://github.com/user-attachments/assets/0ef9ab9a-f143-429b-a4f2-014b8baf1da7" width="275" height="400"/>


For the Audio processing and effect portion of the guitar i chose a raspberry Pi 3 B+, not for any spec reasons, but because it was just laying around. after fiddling around with some DSP applications for linux i chose one that had multiple effect presets and keybinded them each. I then got 10 SPST buttons and wired each individual one to 10 different GPIO pins very inefficiently. these buttons then used a simple script to map each button to a key press to toggle the presets, that was the entire interface portion of the Guitar. The processing requirements for the DSP really created a cooling problem for the guitar which i 'solved' by mounting a large heatsink and fan to the processor, which required a large hole to be cut out of the guitar body, not only to accomodate the Pi itself, but also to fit the fan raised by the large heat pipes. 



<img src="https://github.com/user-attachments/assets/fd7dbe5e-e7b7-4618-843a-95f4d449869e" data-canonical-src="https://github.com/user-attachments/assets/fd7dbe5e-e7b7-4618-843a-95f4d449869e" width="300" height="400"/>



For power delivery, about the only thing to stay remotely similar to the final guitar was to have a DC jack and a Battery, however instead of a custom battery, I made use of a makita 18v tool battery and just got a mount from ebay, which wasnt a terrible idea as using a pre existing battery would make it easier, however we are a ryobi family! i had to borrow a mates battery which got definetly annoying when he needed it for work. 

Now this is where it gets really embarrasing. my lack of electrical engineering knowledge led me down the research path of how i can regulate the voltage down to 5v for the Raspberry Pi, and i discovered the voltage divider circuit which obviously is not the way to solve my problem due to the incredible inneficiency and the lack of any actual regulation of voltage, but 18yr old me thought it did. so strapped 2x 10Watt resistors into a very poor arrangement to lower the voltage, which most definetely wasn't done correctly and one of them blew up. this lead me to try the DCDC converter XL6009 which was better. But again, I was mounting all this on bare ply wood with hot glue, it was such a poor design approach from me. I included an audio amplifier module for 2 speakers at 5w 4ohm each.

After testing it out together, all i got was terrible noise from the pickups, resulting in an unplayable device. I wrapped the interior with copper tape and sprayed in with a non conductive enamel coat to prevent shorts. This was done to prevent EMI which i though was the issue, however looking back on it, there were definetely other issues at play relating to my poor designing techniques and a million other things. 

<img src="https://github.com/user-attachments/assets/2291a653-926c-473b-aa5e-9037798f8677" data-canonical-src="https://github.com/user-attachments/assets/2291a653-926c-473b-aa5e-9037798f8677" width="275" height="400"/>
<img src="https://github.com/user-attachments/assets/872ba47c-ba6c-46c9-a032-880b84e251ca" data-canonical-src="https://github.com/user-attachments/assets/872ba47c-ba6c-46c9-a032-880b84e251ca" width="275" height="400"/>

This all took place between July 2023 to October 2023 and after repeated failures to get the guitar to sound remotely like a guitar, I decided to remember what worked, what didnt and i scrapped my current progress and started from scratch. I vowed to create as much of the guitar myself so i could fully grasp what was taking place within the product. whether it be circuit boards, programming, woodworking and CNC work, I then embarked on a 1 year long journey to create the Electronic Guitar no matter the cost, and no matter what problems stood in my way as this became personal. I would take my time researching not only different components, tools, techniques and practises, but also the basis of managing a project. From the design progress, cost management and other essential skills, I used my determination to succeed (My goal was to get it finished by July 2024, I was far off).


## Skills learnt

<img src="https://github.com/user-attachments/assets/7e0dccc6-ba05-4742-a6f2-0f62fcaea02e" data-canonical-src="https://github.com/user-attachments/assets/7e0dccc6-ba05-4742-a6f2-0f62fcaea02e" width="400" height="275"/>



### Electrical theory
- Assembled many breadboard circuits of various guitar pedal effects, learning how each component influences the circuit as I went
- Began using basic concepts of voltage, current, resistance and power to make simple custom circuits with 555 timers
- Began experimenting with perf boards for more permanent guitar pedals but had trouble at first with bugs due to soldering skills. After practicing however and correcting my mistakes my failure rate dropped. 
- At this point perf boards were becoming tedious to repeatedly make circuits, compared to breadboards, so I  heavily experimented with pcbs, however instead of ordering them I would DIY them. 




### Custom pcb manufacturing

- PCB manufacturing at a basic level consists of etching traces on a copper topped fibreglass board and drilling any through holes required. 
- I would experiment with two different forms of etching, Chemical etching and CNC etching. 


#### chemical etching 

Chemical etching involved imprinting an image of the circuit traces onto the copper of the board then chemically removing the copper not covered with the circuit image, leaving being only traces.



This was done by first:

using photoresist coated pcb blanks and getting a printed copy of the pcb traces in black and white, soaking the paper in mineral oil and placing it over the photoresist. 
The board was then placed in a custom uv light chamber which itself used a pcb I custom made to control the uv intensity and timer. This was then used to cure the photo resist. 
After the curing stage was over I would place the board in a positive resist solution to remove the excess ink from the board to leave behind only the circuit trace on the board covered by the photo resist
The board was then put into a tub of ferric chloride to then dissolve the copper not covered by the photo resist
The board is then taken out of the ferric chloride and placed in water to stop the dissolving process. Acetone was then applied on top to remove the photoresist over the traces to leave behind an etched PCB
All that’s left is to drill through holes with a dremel for components and solder them on. 


This worked for a while, but overall it was a process that was time consuming and was difficult to achieve 2 layered boards accurately as lining them up on both sides proved troublesome. I was always going to utilise a CNC mill for making components for the guitar but I found it could be used for milling PCB traces so I began experimenting. 


## Technical In Depth


