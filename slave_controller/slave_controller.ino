#include <Wire.h>

#define SLAVE_ADDR             8
#define BATTERY_VOLTAGE_PIN   A0
#define LIGHT_SENSOR1_PIN     A1
#define LIGHT_SENSOR2_PIN     A2
#define LIGHT_SENSOR3_PIN     A3
#define LIGHT_SENSOR4_PIN     A6
#define SOLENOID_PIN           7
#define DRV_TB6612FGN // Comment this line if using DRV8833 DC motor driver
#define MOTOR_PWM_PIN          4
#define MOTOR_IN1_PIN          5
#define MOTOR_IN2_PIN          6

unsigned long prev_t = 0;
unsigned long control_time  = 50;  // run every ms 
unsigned long solenoid_t = 0;
unsigned long solenoid_timer = 100; //500 // solenoid active duration
bool start_solenoid_timer = false;

byte battery_voltage_sensor = 0;
byte light_sensor1 = 0;
byte light_sensor2 = 0;
byte light_sensor3 = 0;
byte light_sensor4 = 0;
bool motor_dir = true;
int motor_spd = 0;
bool is_deploy = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDR); // join i2c bus with defined address
  Wire.onRequest(requestEvent); // trigger function when request by master
  Wire.onReceive(receiveEvent); // trigger function when data sent from master

  pinMode(SOLENOID_PIN,OUTPUT);
  pinMode(MOTOR_PWM_PIN,OUTPUT);
  pinMode(MOTOR_IN1_PIN,OUTPUT);
  pinMode(MOTOR_IN2_PIN,OUTPUT);
}

void loop() {
  unsigned long cur_t = millis();
  if (cur_t - prev_t >= control_time) {
    prev_t = cur_t;
    battery_voltage_sensor = map(analogRead(BATTERY_VOLTAGE_PIN),0,1023,0,255);
    light_sensor1 = map(analogRead(LIGHT_SENSOR1_PIN),0,1023,0,255);
    light_sensor2 = map(analogRead(LIGHT_SENSOR2_PIN),0,1023,0,255);
    light_sensor3 = map(analogRead(LIGHT_SENSOR3_PIN),0,1023,0,255);
    light_sensor4 = map(analogRead(LIGHT_SENSOR4_PIN),0,1023,0,255);

    #ifdef DRV_TB6612FGN
    if (motor_spd == 0) {
      digitalWrite(MOTOR_IN1_PIN, LOW);
      digitalWrite(MOTOR_IN2_PIN, LOW);
    } else if (motor_dir) {
      digitalWrite(MOTOR_IN1_PIN, HIGH);
      digitalWrite(MOTOR_IN2_PIN, LOW);
    } else if (!motor_dir) {
      digitalWrite(MOTOR_IN1_PIN, LOW);
      digitalWrite(MOTOR_IN2_PIN, HIGH);
    }
    analogWrite(MOTOR_PWM_PIN, motor_spd);
    #else
    if (motor_spd == 0) {
      digitalWrite(MOTOR_IN1_PIN, LOW);
      digitalWrite(MOTOR_IN2_PIN, LOW);
    } else if (motor_dir) {
      analogWrite(MOTOR_IN1_PIN, motor_spd);
      digitalWrite(MOTOR_IN2_PIN, LOW);
    } else if (!motor_dir) {
      digitalWrite(MOTOR_IN1_PIN, LOW);
      analogWrite(MOTOR_IN2_PIN, motor_spd);
    }
    #endif

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

  }
}

void requestEvent() {
  Wire.write(battery_voltage_sensor);
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
