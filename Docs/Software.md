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
In **Tools** > **Manage Libraries...** or click the **Library Manager** icon on the left bar, install the following three libraries with the latest version.
- **3.1** **WiFiManager** by *tzapu*  
<img src="../Figures/Software_Tutorial/3.1.png" width="500">

- **3.2** **Adafruit SSD1306** by *Adafruit*  
<img src="../Figures/Software_Tutorial/3.2.png" width="500">

- **3.3** **Adafruit GFX Library** by *Adafruit*  
<img src="../Figures/Software_Tutorial/3.3.png" width="500">

## 4. Upload Code to ESP32-CAM
**4.1** Open the file [`ESP32-CAM.ino`](../Software/ESP32-CAM/ESP32-CAM.ino) in the folder [`Software/ESP32-CAM`](../Software/ESP32-CAM/) with Arduino IDE.

**4.2** Turn off the CubeSat by pushing the power switch upward and turn the CubeSat into **upload mode** by sliding the switch to the side of **Upload**.  
<img src="../Figures/Software_Tutorial/4.2a.jpg" height="400">
<img src="../Figures/Software_Tutorial/4.2b.jpg" height="400">

**4.3** Plug in the mini USB wire to the ESP32 Programmer (Red Module) and connect to your PC.  
<img src="../Figures/Software_Tutorial/4.3.jpg" width="300">

**4.4** In your Arduino IDE, go to **Tools** > **Board** > **esp32** > select **ESP32 Wrover Module**.  
<img src="../Figures/Software_Tutorial/4.4.png" width="800">

**4.5** In **Tools**, select the upload configuration as follows:
- **Port**: COMX (Try different COM port one by one if multiple COM ports appear)
- **Core Debug Level**: None
- **Flash Frequency**: 80MHz
- **Flash Mode**: QIO
- **Partition Scheme**: Huge App (3MB No OTA)
- **Upload Speed**: 921600

**4.6** Click the **Upload** arrow icon on the top left corner to start compile and upload the code to ESP32-CAM.  
<img src="../Figures/Software_Tutorial/4.6.png" width="500">

During uploading, the message ***"Writing at 0x00000000... (xx%)"*** will be shown up in the **Output** window at the botton of Arduino IDE.  
***Please do not unplug the USB wire during this process.***

If the message ***"Leaving... Hard resetting via RIS Pin..."*** shows up, the upload is completed and the Mini USB wire can be unplugged.

**4.7** Switch the CubeSat back to **Program Mode** for running the uploaded program.
<img src="../Figures/Software_Tutorial/4.7.jpg" width="500">

## 5. Upload Code to Arduino Nano
**5.1** Plug the Mini USB connected to your PC to Arduino Nano.  
<img src="../Figures/Software_Tutorial/5.1.jpg" width="300">

**5.2** In **Tools** > **Board** > **Arduino AVR Boards** > select **Arduino Nano**.  
In  **Tools** > **Processor** > select **ATmega328P (Old Bootloader)**.  (If the upload failed, try different processor since the processor varies across different manufracturers.)  
<img src="../Figures/Software_Tutorial/5.2a.png" height="300">
<img src="../Figures/Software_Tutorial/5.2b.png" height="300">

**5.3** Click the **Upload** arrow icon on the top left corner to start compile and upload the code.  
If completed, the message ***"Done Uploading"***  will be shown and the Mini USB wire can be unplugged.

## 6. Power the CubeSat and Connect to WiFi
**6.1** Turn on the power switch by pushing the lever downward.  
<img src="../Figures/Software_Tutorial/6.1.jpg" height="400">

**6.2** The message ***"Searching WiFi..."*** will be shown on the OLED diplay and the ESP32-CAM will search for the saved WiFi credentials in the board, which is the SSID and the password of a hotspot.  
<img src="../Figures/Software_Tutorial/6.2.jpg" width="500">

**6.3** If the LED on the ESP32-CAM will flash multiple times, the ESP32-CAM is connected to the WiFi network and its IP adress will be shown on the display.  
<img src="../Figures/Software_Tutorial/6.3.jpg" width="500">  
If the message ***"SSID not found. Entered config mode."*** is shown on the display, the ESP32-CAM cannot found its saved WiFi network. See ***Sec. 6.5*** for changing its WiFi configurations.

**6.4** Connect your device (PC, laptop, mobile phone, or tablet) to the same WiFi network that the CubeSat is connected to. Open the browser and search with the IP address. A web page of CubeSat's control panel will be shown.  Go to ***Sec. 7*** to see how to control the CubeSat.  
<img src="../Figures/Software_Tutorial/6.4.jpg" width="400">

**6.5** If the saved WiFi credentials is not found, the CubeSat will turn into **Config mode** and display its SSID name on the OLED display.  
<img src="../Figures/Software_Tutorial/6.5.jpg" width="500">

**6.6** Use any device with WiFi connectivity to search SSID name of the CubeSat.  
<img src="../Figures/Software_Tutorial/6.6.jpg" height="500">

**6.7** After your device is connected to the CubeSat through the SSID, the **WiFi Manager** page will show up on your device. Click **configure WiFi** > select the WiFi network that you want your CubeSat to connect or type the SSID and password in the box below.  
<img src="../Figures/Software_Tutorial/6.7a.jpg" width="400">
<img src="../Figures/Software_Tutorial/6.7b.jpg" width="400">


**6.8** Click save afterward and close the **WiFi Manager** page on your device. Turn off power of your CubeSat and turn on again to reset. Repeat ***Sec. 6.1*** to try the new WiFi connection.

**6.9** If you want to erase the saved WiFi credentials to reconfigure the WiFi settings, you can press the button next to ESP32-CAM while turning on the CubeSat. This can force the ESP32-CAM entering the **Config mode**.  
<img src="../Figures/Software_Tutorial/6.9.jpg" width="400">

## 7. Control the CubeSat Remotely with the Control Panel
**7.1** Camera Live Stream

**7.2** Solar Panel Deploy

**7.3** Reaction Wheel Control

**7.4** Light Sensor Readings

**7.5** Battery Voltage Meter

**7.6** CubeSat LED Flash

**7.7** Auto Light Tracking
