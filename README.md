# The Electronic Guitar MK1

## Introduction
This is the repository for the Research and Development, Production, and assembly of the Electric Guitar MK1. 


<img src="https://github.com/user-attachments/assets/6f7fdf49-825d-451c-a7b9-8be3157fd3e8" data-canonical-src="https://github.com/user-attachments/assets/6f7fdf49-825d-451c-a7b9-8be3157fd3e8" width="275" height="400"/>

<img src="https://github.com/user-attachments/assets/d93b2070-a9af-42f3-9944-c3cdc3873ebc" data-canonical-src="https://github.com/user-attachments/assets/d93b2070-a9af-42f3-9944-c3cdc3873ebc" width="275" height="400"/>

<img src="https://github.com/user-attachments/assets/fa07d7f7-db8a-4da3-886a-537a519272df" data-canonical-src="https://github.com/user-attachments/assets/fa07d7f7-db8a-4da3-886a-537a519272df" width="275" height="400"/>




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
<img src="https://github.com/user-attachments/assets/9b4ad88e-3aeb-4436-89f3-a7abf6b0a5f4" data-canonical-src="https://github.com/user-attachments/assets/9b4ad88e-3aeb-4436-89f3-a7abf6b0a5f4" width="400" height="275"/>
<img src="https://github.com/user-attachments/assets/b2ceb06b-6ee6-4933-b40f-708f32b882f9" data-canonical-src="https://github.com/user-attachments/assets/b2ceb06b-6ee6-4933-b40f-708f32b882f9" width="400" height="275"/>
<img src="https://github.com/user-attachments/assets/148f8853-0d81-427b-8be9-8154661c2e9d" data-canonical-src="https://github.com/user-attachments/assets/148f8853-0d81-427b-8be9-8154661c2e9d" width="400" height="275"/>
<img src="https://github.com/user-attachments/assets/07cd014e-b3e3-4404-ae46-7ecd842fdd10" data-canonical-src="https://github.com/user-attachments/assets/07cd014e-b3e3-4404-ae46-7ecd842fdd10" width="400" height="275"/>
<img src="https://github.com/user-attachments/assets/7e0dccc6-ba05-4742-a6f2-0f62fcaea02e" data-canonical-src="https://github.com/user-attachments/assets/7e0dccc6-ba05-4742-a6f2-0f62fcaea02e" width="400" height="275"/>


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









## First Attempt 
I first came up with this concept around July 2023, where a regeular guitar could be retro fitted with electronics to create a cheap, simple portable electric guitar. Oh how wrong i was. With some moderate experience in playing with arduino's and Raspberry Pi's, a good bit of wood working experience with dad, and no electrical engineering experience, I set out on accomplishing my goal.

<img src="https://github.com/user-attachments/assets/6be55a72-e7aa-4a15-b726-ad1f1358878a" data-canonical-src="https://github.com/user-attachments/assets/6be55a72-e7aa-4a15-b726-ad1f1358878a" width="275" height="400"/>

For the Guitar itself i had a chinese strat laying around that i found second hand at an Op shop for 20$ that i never used, because obviously it sounded terrible. The electronics were barely working, it was missing a tuning peg and just sounded terrible! but after cleaning it up, re wiring it with new cheap pickups and new tuning pegs, it was somewhat playable. i then totally destroyed the guitar by then routing out long wire tracks and spots for components among other things. I reckon it was less then half the weight of its former self when i was done with it. I repainted The boddy and neck Black and moved on to the electronics.

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


## Technical In Depth


