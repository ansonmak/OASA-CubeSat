/*
  ESP32-CAM CubeSat (ESP32 library V.1.0.6 required)
  cubesat-esp32.ino (requires app_httpd.cpp)
  Based upon Espressif ESP32CAM Examples
  Uses TBA6612FNG H-Bridge Controller
  
*/

#include "esp_wifi.h"
#include "esp_camera.h"
#include <WiFi.h>
#include "esp32cam_pins.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "Wire.h"
#include "MPU9250/MPU9250.h"
#include <Adafruit_GFX.h> // Requires Adafruit GFX library
#include <Adafruit_SSD1306.h> // requires Adafruit SSD1306 library

// Setup WiFi Access Point Credentials
const char* ssid = "Anson iPhone"; //"chao"; //"wang";
const char* password = "ansonmak"; //"9C9fIfrw"; //"groupwang";

unsigned long slave_prev_t = 0;
unsigned long slave_talk_time = 100; // time interval get data from slave
unsigned long imu_prev_t = 0;
unsigned long imu_talk_time = 20;
// received data from slave
int battery_voltage_sensor = 0;
float battery_voltage = 0.0;
const float voltage_offset = 0.15;
const float battery_min_voltage = 3.2;
const float battery_max_voltage = 4.1;
float battery_percentage = 0.0;
int light_sensor1 = 0;
int light_sensor2 = 0;
int light_sensor3 = 0;
int light_sensor4 = 0;
float imu_roll = 0.0;
float imu_pitch = 0.0;
float imu_yaw = 0.0;
float imu_MagX = 0.0;
float imu_MagY = 0.0;
float imu_MagZ = 0.0;

// data send to slave
extern bool send_slave;
extern bool is_deploy;
extern byte motor_spd;
extern bool motor_dir;

MPU9250 IMU;

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

  // set up pin for buildin led
  ledcSetup(LED_CHN, PWM_FREQ, PWM_RES);
  ledcAttachPin(BUILDIN_LED_PIN, LED_CHN);

  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
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

  // setup I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  slave_prev_t = millis();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(500);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("WiFi Connected!");
  display.println("IP:");
  display.println(WiFi.localIP());
  display.display(); 

  // MPU 9250 i2c connection
  // if (!IMU.setup(0x68)) {
  //     while (1) {
  //         Serial.println("MPU connection failed. Please check your connection with connection_check example.");
  //         delay(3000);
  //     }
  // }
  // delay(5000);
  // IMU.setMagneticDeclination(-3.26); // Hong Kong
  // Serial.println("Calibrating Accelerometer Gyroscope...");
  // led_blink(); 
  // delay(3000);
  // IMU.calibrateAccelGyro();
  // Serial.println("Calibrating Magentometer...");
  // led_blink();
  // delay(3000);
  // IMU.calibrateMag();
  // led_multi_blink(5);
  // Serial.println("Calibration done.");
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
    battery_voltage = float(battery_voltage_sensor)/255 * 5.0 * 2.0 + voltage_offset;
    battery_percentage = mapfloat(battery_voltage, battery_min_voltage, battery_max_voltage, 0, 100);

    if (send_slave) {
      Wire.beginTransmission(SLAVE_ADDR);
      if (is_deploy) {
        Wire.write('!');
        is_deploy = false;
      }
      Wire.write(motor_dir ? '+' : '-');
      Wire.write(motor_spd);
      Wire.endTransmission();
      send_slave = false;
    }
  }

  if (cur_t - imu_prev_t >= imu_talk_time) {
    imu_prev_t = cur_t;
    // if (IMU.update()) {
    //   // Serial.print(IMU.getAccX()); Serial.print(", ");
    //   // Serial.print(IMU.getAccY()); Serial.print(", ");
    //   // Serial.print(IMU.getAccZ()); Serial.print(", ");
    //   // Serial.print(IMU.getGyroX()); Serial.print(", ");
    //   // Serial.print(IMU.getGyroY()); Serial.print(", ");
    //   // Serial.print(IMU.getGyroZ()); Serial.print(", ");
    //   // Serial.print(IMU.getMagX()); Serial.print(", ");
    //   // Serial.print(IMU.getMagY()); Serial.print(", ");
    //   // Serial.println(IMU.getMagZ());
    //   imu_roll = IMU.getRoll();
    //   imu_pitch = IMU.getPitch();
    //   imu_yaw = IMU.getYaw();
    //   imu_MagX = IMU.getMagX();
    //   imu_MagY = IMU.getMagY();
    //   imu_MagZ = IMU.getMagZ();
    //   // Serial.print(imu_roll); Serial.print(", ");
    //   // Serial.print(imu_pitch); Serial.print(", ");
    //   // Serial.println(imu_yaw);
    // }
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
