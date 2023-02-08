/*
  OASA CubeSat with ESP32-CAM(ESP32 library V.1.0.6 required)
  Based upon Espressif ESP32-CAM Examples
  Author: Anson Mak
  
  ESP32 Board Library Version 1.0.6
  Library Requirement:
  - WiFi Manager by Tzapu, tablatronix
  - Adafruit GFX library
  - Adafruit SSD1306 library
*/

#include "esp_wifi.h"
#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiManager.h>
#include "esp32cam_pins.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Wire.h"
#include <Adafruit_GFX.h> // Requires Adafruit GFX library
#include <Adafruit_SSD1306.h> // Requires Adafruit SSD1306 library

// AP Credentials
// const String CUBESAT_ID = "000";
// const String AP_SSID = "CubeSat" + CUBESAT_ID;
// const String AP_PW = "cubesat"+ CUBESAT_ID;

// Setup WiFi Access Point Credentials
// const char* ssid = "********";
// const char* password = "********";

unsigned long slave_prev_t = 0;
unsigned long slave_talk_time = 100; // time interval get data from slave
// received data from slave
int battery_voltage_sensor = 0;
float battery_voltage = 0.0;
float R1 = 100; //(k ohm) Resistance of R1
float R2 = 100; //(k ohm) Resistance of R2
float voltage_divider_constant = (R1+R2)/R2; // V_battery  = (R1+R2)/R2 * V_Measure 
const float voltage_offset = 0.15;
const float battery_min_voltage = 3.2;
const float battery_max_voltage = 4.1;
float battery_percentage = 0.0;
int light_sensor1 = 0;
int light_sensor2 = 0;
int light_sensor3 = 0;
int light_sensor4 = 0;

// data send to slave
extern bool send_slave;
extern bool is_deploy;
extern bool set_light_track;
extern byte motor_spd;
extern bool motor_dir;
extern bool is_flash;
bool start_led_flash_timer = false;
unsigned long led_flash_t = 0;
const unsigned long led_flash_timer = 500; //ms

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void startCameraServer();
void led_blink();

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector
  
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  //drop down frame size for higher initial frame rate
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, (framesize_t)3);
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
  s->set_quality(s, 35);
  

  // Set up pin for buildin led
  ledcSetup(LED_CHN, PWM_FREQ, PWM_RES);
  ledcAttachPin(BUILDIN_LED_PIN, LED_CHN);

  // Set up pin for triggering WIFI Configuration 
  pinMode(WIFI_RESET_TRIGGER, INPUT_PULLUP);

  // Set up I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  
  // Set up OLED SSD1306 Connection
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(100);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Searching WiFi...");
  display.display(); 
  delay(1000);

  // WiFi.begin(ssid, password);

  WiFiManager wfm;
  if (digitalRead(WIFI_RESET_TRIGGER) == LOW)
    wfm.resetSettings(); // erase saved credentials
  wfm.setAPCallback(configModeCallback); // call configModeCallback() when entered config WiFi mode
  // wfm.autoConnect(AP_SSID.c_str(),AP_PW.c_str()) //use define AP name and password
  if(!wfm.autoConnect()) { // auto generated AP name from chipID
      Serial.println("Failed to connect");
      // ESP.restart();
  }
  WiFi.setSleep(false);
  
  display.println("Saved SSID Found");
  display.print("WiFi Connecting");
  display.display(); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display(); 
    led_blink();
  }
  Serial.println("");
  Serial.println("WiFi connected");
  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  // flash led
  led_multi_blink(5);
  
  // display connection message
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connected to: ");
  display.println(WiFi.SSID());
  display.println("");
  display.println("Control Panel IP:");
  display.println(WiFi.localIP());
  display.display(); 

  slave_prev_t = millis();
}

void loop() {
  unsigned long cur_t = millis();

  if (cur_t - slave_prev_t >= slave_talk_time) {
    slave_prev_t = cur_t;
    int byte_num = 5; // number of bytes to request
    Wire.requestFrom(SLAVE_ADDR, byte_num);

    char receive_byte[byte_num];
    int receive_idx = 0;
    while (Wire.available()) { 
      receive_byte[receive_idx] = Wire.read(); //read byte
      receive_idx++;
    }
    battery_voltage_sensor = int(receive_byte[0]);
    light_sensor1 = int(receive_byte[1]);
    light_sensor2 = int(receive_byte[2]);
    light_sensor3 = int(receive_byte[3]);
    light_sensor4 = int(receive_byte[4]);
    battery_voltage = float(battery_voltage_sensor)/255 * 5.0 * voltage_divider_constant + voltage_offset;
    battery_percentage = mapfloat(battery_voltage, battery_min_voltage, battery_max_voltage, 0, 100);

    if (send_slave) {
      Wire.beginTransmission(SLAVE_ADDR);
      if (is_deploy) {
        Wire.write('!');
        is_deploy = false;
      }
      if (set_light_track) {
        Wire.write('^');
        set_light_track = false;
      }
      Wire.write(motor_dir ? '+' : '-');
      Wire.write(motor_spd);
      Wire.endTransmission();
      send_slave = false;
    }
  }

  if (is_flash) {
    ledcWrite(LED_CHN,1);
    if (!start_led_flash_timer) {
        led_flash_t = cur_t;
        start_led_flash_timer = true;
      }
      if (start_led_flash_timer && cur_t - led_flash_t >= led_flash_timer) {
        ledcWrite(LED_CHN,0);
        is_flash = false;
        start_led_flash_timer = false;
    }
  }


}

void led_blink() {
  ledcWrite(LED_CHN,1);
  delay(50);
  ledcWrite(LED_CHN,0);
  delay(50); 
}

void led_multi_blink(int times) {
  for (int i=0;i<times;i++) {
    led_blink(); 
  }
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  if (x < in_min) return out_min;
  else if (x > in_max) return out_max;
  else return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void configModeCallback(WiFiManager *myWiFiManager) {
  if (digitalRead(WIFI_RESET_TRIGGER) == LOW) {
    display.println("Resetting SSID");
  } else {
    display.println("SSID not found");
  }
  display.println("Entered config mode");
  display.println("Configure via AP:");
  display.println(myWiFiManager->getConfigPortalSSID());
  display.println("With IP:");
  display.println("192.168.4.1");
  display.display();
}
