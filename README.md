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


### RGB Lighting Features:
  - 1x6 row of WS2812B 5050 SMD NeoPixel RGB LED's
  - each LED uniquely addressable via IC2 Protocol, allowing for any colour and brightness on each LED
  - Control the LEDs settings and the preset effect styles selectable through the User Interface
  - 5V operating Voltage and data supplied from AFPI to RGB lighting PCB
  - RGB PCB including extra Data Output for modular expansion of lighting to other areas of the Guitar
  - RGB PCB encased in a 3d printed mounting bracket to fit in the body, as well as to attach clear acrylic cover plate


### Physical Design Features:
  - Custom designed Body shape
  - Red Ceder wood for body
  - CNC milled Acrylic Top and Back plates for switch plates and wire route coverings
  - 3D printed Components for mounting electrical components into Body as modular sections


### Guitar specific Features:
  - SSH passive pickup layout, with pins available for active pickups
  - 22 Fret stratocaster syle neck
  - 5 way pickup selector switch layout
  - 1x master Volume potentiometer
  - 1x master Gain potentiometer



## First Attempt 

## Skills learnt

## Technical In Depth


