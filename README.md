# Electronic Guitar MK1

> A self-built, digitally-enhanced electric guitar featuring onboard effects, audio output and removable battery supply all integrated within a custom made Guitar.

---

## TL;DR Overview

- DIY portable electric guitar with integrated digital effects and modular power/audio system  
- Final version features Teensy 4.0, onboard FX, rotary encoder UI, OLED display, amp/speaker output, battery or DC power, and RGB lighting  
- Entire build: woodwork, PCBs, 3D prints, firmware, and more  
- Early prototype (Mk0) failed due to poor electrical design and overcomplex hardware, rebuilt from scratch over 12+ months with newly acquired engineering and fabrication skills  


<img src="https://github.com/user-attachments/assets/6f7fdf49-825d-451c-a7b9-8be3157fd3e8" data-canonical-src="https://github.com/user-attachments/assets/6f7fdf49-825d-451c-a7b9-8be3157fd3e8" width="275" height="400"/><img src="https://github.com/user-attachments/assets/fa07d7f7-db8a-4da3-886a-537a519272df" data-canonical-src="https://github.com/user-attachments/assets/fa07d7f7-db8a-4da3-886a-537a519272df" width="275" height="400"/><img src="https://github.com/user-attachments/assets/d93b2070-a9af-42f3-9944-c3cdc3873ebc" data-canonical-src="https://github.com/user-attachments/assets/d93b2070-a9af-42f3-9944-c3cdc3873ebc" width="275" height="400"/>

---

## Specs (MK1)

### Hardware Features

- **Microcontroller:** Teensy 4.0 (600 MHz ARM Cortex M7, 1MB RAM)  
- **Audio Codec:** SGTL5000 via Teensy Audio Shield Rev D2  
- **Display:** 2.42" 128x64 OLED  
- **UI:** 4x rotary encoders (Adafruit I2C) with push buttons  
- **Output Options:**
  - 1W LM386 speaker amp + 8Ω speaker  
  - 3.5mm headphone jack  
  - 1/4" AUX output  
- **SD Card:** for saving and loading effect presets  

<img src="https://github.com/user-attachments/assets/5239486c-7751-4ee9-8c51-16a76888f950" data-canonical-src="https://github.com/user-attachments/assets/5239486c-7751-4ee9-8c51-16a76888f950" width="275" height="400" /><img src="https://github.com/user-attachments/assets/2b61481e-fd04-4a99-8314-2ab62f885f4d" data-canonical-src="https://github.com/user-attachments/assets/2b61481e-fd04-4a99-8314-2ab62f885f4d" width="275" height="400"/>

### Physical Design

- Custom red cedar guitar body with Strat-style neck and 22 frets  
- SSH passive pickup layout with 5-way selector  
- CNC acrylic panels for access and wiring  
- Modular 3D-printed brackets for internals  
- Magnetic battery bay  

<img src="https://github.com/user-attachments/assets/9df731cb-8994-4f1a-941f-662791b46a10" data-canonical-src="https://github.com/user-attachments/assets/9df731cb-8994-4f1a-941f-662791b46a10" width="275" height="400"/>

### Power System

- **Battery:** 4S 18650 3500mAh Li-ion (16.8V max)  
- **BMS:** With overcharge/discharge protection  
- **Power Switching:** Automatically defaults to DC jack if plugged in  
- **Regulation:** L7805 LDO for logic, raw voltage for amp  
- **Runtime:** ~12 hours full load; much longer with optimized settings  

<img src="https://github.com/user-attachments/assets/a88d6ac0-515a-4c26-8ed4-063b8bcff47a" data-canonical-src="https://github.com/user-attachments/assets/a88d6ac0-515a-4c26-8ed4-063b8bcff47a" width="275" height="400"/>

### RGB Lighting

- 6x WS2812B addressable LEDs  
- Controlled via UI with adjustable patterns and brightness  
- 5V from Teensy board, expandable via breakout  
- Mounted in a custom 3D enclosure with acrylic cover  
- See [Demo](https://github.com/Wierdwizard2587/ElectricGuitarMK1/raw/main/Progress%20Photos/Woodworking/IMG_9428.MOV)



### Design Decisions

- Abandoned analog FX + digipots due to impractical voltage/current handling  
- Digital FX chain implemented using Teensy Audio Library and CODEC  
- Custom single-layer PCB with JST headers for modularity  
- UI system built around I2C rotary encoders and OLED display  
- 3D-printed brackets standardized component mounting across internal assemblies  

### Tools and Processes

#### PCB Manufacturing

- **Chemical Etching:** Photoresist UV method with ferric chloride; scrapped due to accuracy and double-sided complexity  
- **CNC Milling:** Used FlatCAM to generate G-code, 3018 CNC and Candle for trace and drill cuts  

#### SMD Soldering

- **Stencil:** CNC-cut mylar sheets for paste application  
- **Soldering:** SMD components placed and reflowed on hot plate  

<img src="https://github.com/user-attachments/assets/7e0dccc6-ba05-4742-a6f2-0f62fcaea02e" data-canonical-src="https://github.com/user-attachments/assets/7e0dccc6-ba05-4742-a6f2-0f62fcaea02e" width="400" height="275"/>

#### CAD and Design

- **KiCAD:** For schematic capture and board layout  
- **FreeCAD:** For PCB enclosure, LED mount, Guitar Body, Acrylic Plates/Panels and Router Jigs  

<img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9158.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9158.JPEG" width="275" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9142.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9142.JPEG" width="275" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9143.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9143.JPEG" width="275" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9144.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9144.JPEG" width="275" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9148.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9148.JPEG" width="275" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9157.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Design%20Phase/IMG_9157.JPEG" width="275" height="400"/>


---

## Mk0 — The Failed First Attempt

The Mk0 was an ambitious retrofit of a cheap Stratocaster copy, originally sourced second-hand for $20 AUD. At the time, I had no electrical engineering knowledge and was only experienced with basic Arduino and Raspberry Pi projects.

### Body and Structural Work
- The original guitar was re-routed to fit electronics, resulting in reduced structural integrity and balance
- Body was repainted and cleaned up with minor woodworking skills from high school
- Attempted to house a Raspberry Pi, amplifier board, fans, wiring and more. all glued to plywood mounts inside the guitar

<img src="https://github.com/user-attachments/assets/ff773c03-f57a-496b-be22-04634716b997" data-canonical-src="https://github.com/user-attachments/assets/ff773c03-f57a-496b-be22-04634716b997" width="275" height="400"/><img src="https://github.com/user-attachments/assets/0ef9ab9a-f143-429b-a4f2-014b8baf1da7" data-canonical-src="https://github.com/user-attachments/assets/0ef9ab9a-f143-429b-a4f2-014b8baf1da7" width="275" height="400"/>

### Electronics and Power Mistakes
- Raspberry Pi 3B+ used for DSP software and effects switching via Linux keybinds
- 10x SPST buttons mapped to GPIO pins, wired manually without debounce or shielding
- Cooling: a heatsink and fan were mounted directly into the guitar body, protruding through the top
- Power: attempted to use a Makita 18V battery regulated by a voltage divider made from two 10W resistors (which exploded)
- Eventually switched to an XL6009 buck converter, mounted haphazardly on wood

<img src="https://github.com/user-attachments/assets/6be55a72-e7aa-4a15-b726-ad1f1358878a" data-canonical-src="https://github.com/user-attachments/assets/6be55a72-e7aa-4a15-b726-ad1f1358878a" width="275" height="400"/><img src="https://github.com/user-attachments/assets/2291a653-926c-473b-aa5e-9037798f8677" data-canonical-src="https://github.com/user-attachments/assets/2291a653-926c-473b-aa5e-9037798f8677" width="275" height="400"/><img src="https://github.com/user-attachments/assets/fd7dbe5e-e7b7-4618-843a-95f4d449869e" data-canonical-src="https://github.com/user-attachments/assets/fd7dbe5e-e7b7-4618-843a-95f4d449869e" width="300" height="400"/>

### Audio and Shielding Failures
- Output sound had constant noise and interference, making the guitar unplayable
- Tried shielding the cavity with copper tape and spray enamel, but issues persisted
- Lack of analog audio knowledge led to poor layout and grounding, introducing hum and feedback

### Realization and Reset
- The experience made clear the importance of proper voltage regulation, shielding, grounding, and modular design
- Mk0 taught me the value of planning, measurement, and using the right components for audio and power
- In October 2023, I decided to scrap the build and committed to rebuilding everything from scratch

---

## The Learning Curve

To succeed with Mk1, I developed and refined skills across multiple disciplines:

- **Electrical theory and circuit design**
  - Learned core principles like Ohm’s Law, impedance, decoupling, signal paths, and analog vs digital tradeoffs by experimenting with breadboarded op-amp FX circuits and 555 timer modules.


- **Breadboarding, debugging, and perfboarding**
  - Built multiple guitar pedal-style analog effects, troubleshooting noise, biasing, and layout issues. Early soldering mistakes taught me good pad heating, proper joint inspection, and signal path discipline.


- **Custom PCB manufacturing**

  - *Chemical etching:* Photoresist and ferric chloride techniques worked for simple single-sided boards, but alignment and etch consistency were poor for complex layouts.

<img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Skills%20Learnt/IMG_8117.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Skills%20Learnt/IMG_8117.JPEG" width="300" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Skills%20Learnt/IMG_8118.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Skills%20Learnt/IMG_8118.JPEG" width="300" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Skills%20Learnt/IMG_8143.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Skills%20Learnt/IMG_8143.JPEG" width="300" height="400"/>

https://github.com/user-attachments/assets/e00821a1-996f-4fed-b84c-7d602e0a9be1


  - *CNC milling:* FlatCAM used to generate G-code from KiCAD Gerbers. I used a 3018 CNC with Candle to reliably cut traces and drill holes. Ultimately switched to ordered boards for reliability.

https://github.com/user-attachments/assets/3b78b966-fe12-4d0b-8b32-34254987f5ec

- **SMD workflow and hot plate reflow soldering**
  - Designed and cut my own mylar stencils for solder paste, allowing for precise paste application and fast assembly of SMD components on the hot plate.

<img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Embedded%20Electronics/IMG_8835.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Embedded%20Electronics/IMG_8835.JPEG" width="400" height="300"/>

- **Power systems and battery safety**
  - Studied Li-ion cell characteristics, pack balancing, protection circuits, and BMS behavior. Designed a 4S pack system with safe cutoff and swappable magnetic connection.

- **CAD and fabrication**
  - *KiCAD:* Used to design full schematics and board layouts with JST headers and part footprints.

  - *FreeCAD:* Modeled body routing templates, control panel shapes, bracket mounting, and tolerance-critical neck fits.

- **CNC woodworking and mechanical precision**
  - Created tight-fitting neck pockets and pickup cutouts with minimal play, ensuring mechanical stability and alignment.
 
<img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Woodworking/IMG_9408.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Woodworking/IMG_9408.JPEG" width="300" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Woodworking/IMG_9404.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Woodworking/IMG_9404.JPEG" width="300" height="400"/><img src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Woodworking/IMG_9453.JPEG" data-canonical-src="https://github.com/Wierdwizard2587/ElectricGuitarMK1/blob/main/Progress%20Photos/Woodworking/IMG_9453.JPEG" width="300" height="400"/>


Each step of the learning process fed directly into the reliability and performance of the final Mk1 design.

---

## Final Words

This project started with a failed experiment and turned into a comprehensive learning journey in electrical engineering, embedded systems, and digital fabrication. Every element—hardware, software, and mechanical—was designed, built, and tested from scratch with the goal of making a fully integrated, self-contained electric guitar. I am very proud of what I was able to accomplish and am very excited to now use and build this new knowledge and gained abilitys to even bigger and better things!
