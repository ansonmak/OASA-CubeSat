# Software Tutorial

## 1. Install Arduino IDE
Visit https://www.arduino.cc/en/software to download and install Arduino IDE software on your PC.

## 2. Install ESP32 Board in Arduino IDE
After you have installed Arduino IDE on your PC, you will need to install the ESP32 board library in Arduino IDE before uploading code to the ESP32 board. 

**2.1** Launch Arduino IDE and go to **Files** > **Preferences**.  
<img src="../Figures/Software_Tutorial/2.1.png" width="500">

**2.2** In **Additional Boards Manager URLs**, paste the following link:
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```  
<img src="../Figures/Software_Tutorial/2.2a.png" width="500">
<img src="../Figures/Software_Tutorial/2.2b.png" width="500">

**2.3** In **Tools** > **Board** > **Boards Manager** or click the **Boards Mananger** icon on the left bar, search **ESP32** and install with **version 1.0.6**.  
<img src="../Figures/Software_Tutorial/2.3.png" width="500">

## 3. Install Libraries in Arduino IDE
**3.1** In **Tools** > **Manage Libraries...** or click the **Library Manager** icon on the left bar, install the following three libraries with the latest version.
- **WiFiManager** by *tzapu*
<img src="../Figures/Software_Tutorial/3.1.png" width="500">

- **Adafruit SSD1306** by *Adafruit*
<img src="../Figures/Software_Tutorial/3.2.png" width="500">

- **Adafruit GFX Library** by *Adafruit*
<img src="../Figures/Software_Tutorial/3.3.png" width="500">

## 4. Upload Code to ESP32-CAM
**4.1** Open the file [`ESP32-CAM.ino`](../Software/ESP32-CAM/ESP32-CAM.ino) in the folder [`Software/ESP32-CAM`](../Software/ESP32-CAM/) with Arduino IDE.

**4.2** Turn off the CubeSat by pushing the power switch upward and turn the CubeSat into upload mode by sliding the switch to the upload side.  
*Figure of CubeSat power switch and upload switch*

**4.3** Plug in the mini USB wire to the ESP32 Programmer (Red Module) and connect with your PC.  
*Figure of mini usb wire plug into FTDI programmer*

**4.4** 

## 5. Upload Code to Arduino Nano

## 6. Power the CubeSat and Connect to WiFi
