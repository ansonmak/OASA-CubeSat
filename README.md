# OASA-CubeSat
<p align = "center">
<img src="Figures/CAD_model.png" height="220"> 
<img src="Figures/Assembled_model.jpg" height="220"> 
</p>

## 1. Overview
OASA-CubeSat is an educational satellite designed to imitate the stucture and functions of a CubeSat, which is a cubic miniature satellite with a size of 10x10x10cm. This educational CubeSat is a single 18650 3.6V battery powered device controlled by two microcontrollers: Arduino Nano and ESP32-CAM. It consists of one 12V geared DC motor for rotating the reaction wheel and two 5V solenoid actuators for deploying the solar panels. The CubeSat also contains a camera with a maximum resolution of 1600 x 1200. With our software uploaded to the microcontrollers, the camera live feed is able to transmit to and view it on the PC through its connected WiFi network. The electronics are all connected through our custom PCB boards which are stacked within the CubeSat’s 3D printed structure.

This repository contains the instructions of how to assemble the CubeSat, guidelines of how to upload the included source code to the CubeSat, and the STL files of the 3D printed parts for replacement of the broken parts or customization.  

## 2. Assembly
Before assembling the CubeSat, check if anything in the box is missing with the list below: 
- [OASA-CubeSat Kits Checklist](Docs/Checklist.md)

To assemble the CubeSat, follow the instructions below:
- [CubeSat Assembly Instruction](Docs/Assembly.md)

For printing the 3D printed parts with your printer, check out the folder, [STL](STL/), for the STL files.

## 3. Software
The source code for the CubeSat is located at the folder: [Software](Software/). Follow the tutorial below to see how to upload the software to the CubeSat:
- [Environment Setup and Software Upload](Docs/Software.md)

## 4. Copyright
**Copyright © 2023 Orion Astropreneur Space Academy (Hong Kong) Ltd.** 

The intellectual property of this educational CubeSat belongs to Orion Astropreneur Space Academy (Hong Kong) Ltd. All rights reserved.

## 5. Maintenance
For any technical issues, please contact Anson Mak with ansonmak1997@gmail.com.