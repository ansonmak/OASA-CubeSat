#include <Wire.h>

#define SLAVE_ADDR             8
#define BATTERY_VOLTAGE_PIN   A0
#define SOLAR_VOLTAGE_PIN     A1
#define LIGHT_SENSOR1_PIN     A2
#define LIGHT_SENSOR2_PIN     A3
#define LIGHT_SENSOR3_PIN     A6
#define LIGHT_SENSOR4_PIN     A7
#define LED1_PIN               2
#define SERVO1_PIN             3
#define LED2_PIN               4
#define MOTOR_PWM1_PIN         5
#define MOTOR_PWM2_PIN         6
#define SOLENOID_PIN           7
#define LED3_PIN               8
#define SERVO2_PIN             9
#define SERVO3_PIN            10
#define SERVO4_PIN            11
#define LED4_PIN              12

unsigned long prev_t = 0;
unsigned long control_time = 50;  // run every ms 
unsigned long solenoid_t = 0;
const unsigned long solenoid_timer = 50; //500 // solenoid active duration
bool start_solenoid_timer = false;

byte battery_voltage_sensor = 0;
byte solar_voltage_sensor = 0;
byte light_sensor1 = 0;
byte light_sensor2 = 0;
byte light_sensor3 = 0;
byte light_sensor4 = 0;
bool motor_dir = true;
int motor_spd = 0;
bool is_deploy = false;
bool is_light_track = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDR); // join i2c bus with defined address
  Wire.onRequest(requestEvent); // trigger function when request by master
  Wire.onReceive(receiveEvent); // trigger function when data sent from master

  pinMode(SOLENOID_PIN,OUTPUT);
  pinMode(MOTOR_PWM1_PIN,OUTPUT);
  pinMode(MOTOR_PWM2_PIN,OUTPUT);
}

void loop() {
  unsigned long cur_t = millis();
  if (cur_t - prev_t >= control_time) {
    prev_t = cur_t;
    battery_voltage_sensor = map(analogRead(BATTERY_VOLTAGE_PIN),0,1023,0,255);
    solar_voltage_sensor = map(analogRead(SOLAR_VOLTAGE_PIN),0,1023,0,255);
    light_sensor1 = map(analogRead(LIGHT_SENSOR1_PIN),0,1023,0,255);
    light_sensor2 = map(analogRead(LIGHT_SENSOR2_PIN),0,1023,0,255);
    light_sensor3 = map(analogRead(LIGHT_SENSOR3_PIN),0,1023,0,255);
    light_sensor4 = map(analogRead(LIGHT_SENSOR4_PIN),0,1023,0,255);

    set_motor(motor_spd, motor_dir);

    if(is_deploy) {
      digitalWrite(SOLENOID_PIN,HIGH);
      if (!start_solenoid_timer) {
        Serial.println("Solenoid active");
        solenoid_t = cur_t;
        start_solenoid_timer = true;
      }
      if (start_solenoid_timer && cur_t - solenoid_t >= solenoid_timer) {
        digitalWrite(SOLENOID_PIN,LOW);
        Serial.println("Solenoid inactive");
        is_deploy = false;
        start_solenoid_timer = false;
      }
    } 

    if (is_light_track) {
      //TODO: function for students to implement
      byte light_left = max(light_sensor1,light_sensor2); //return max of 1/2
      byte light_right =  max(light_sensor3,light_sensor4); //return max of 3/4
      byte range = 150; //threshold to rotate the CubeSat
      int track_speed = 80; //speed of rotate the CubeSat
      if (light_left - light_right > range && light_left > 800) { //if left side brighter
        set_motor(track_speed, 1); //turn left
      } else if (light_right - light_left > range && light_right > 800) { //if right side brighter
        set_motor(track_speed, 0); //turn right
      } else {
        set_motor(0, 0); //stay
      }
    }

  }
}

void requestEvent() {
  Wire.write(battery_voltage_sensor);
  Wire.write(solar_voltage_sensor);
  Wire.write(light_sensor1);
  Wire.write(light_sensor2);
  Wire.write(light_sensor3);
  Wire.write(light_sensor4);
}

void receiveEvent(int howMany) {
  while (Wire.available() > 1) {
    char c = Wire.read();
    switch (c) {
      case '!':
        Serial.println("Deploy!");
        is_deploy = true;
        break;
      case '^':
        is_light_track = !is_light_track;
        if (!is_light_track) set_motor(0, 0);
        Serial.print("Light tracking: ");
        Serial.println(is_light_track ? "ON" : "OFF");
        break;
      case '+':
        motor_dir = true;
        Serial.print(c);
        break;
      case '-':
        motor_dir = false;
        Serial.print(c);
        break;
    } 
  }
  motor_spd = Wire.read();
  Serial.println(motor_spd);
}

void set_motor(int spd, bool dir) {
  if (spd == 0) { //stop
    digitalWrite(MOTOR_PWM1_PIN, LOW);
    digitalWrite(MOTOR_PWM2_PIN, LOW);
  } else if (dir) { //Clockwise
    digitalWrite(MOTOR_PWM1_PIN, LOW);
    analogWrite(MOTOR_PWM2_PIN, spd);
  } else if (!dir) { //Anticlockwise
    analogWrite(MOTOR_PWM1_PIN, spd);
    digitalWrite(MOTOR_PWM2_PIN, LOW);
  }
}