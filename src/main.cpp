#include <Arduino.h>

#define SERIAL_BAUNDRATE 115200

#define PIN_MOTOR_LEFT_FORWARD 2
#define PIN_MOTOR_LEFT_REVERSE 3
#define PIN_MOTOR_RIGHT_FORWARD 4
#define PIN_MOTOR_RIGHT_REVERSE 5

#define COMMAND_FORWARD 0x30
#define COMMAND_LEFT 0x31
#define COMMAND_RIGHT 0x32
#define COMMAND_BACK 0x33
#define COMMAND_FORWARD_LEFT 0x34
#define COMMAND_BACK_LEFT 0x35
#define COMMAND_FORWARD_RIGHT 0x36
#define COMMAND_BACK_RIGHT 0x37
#define COMMAND_STOP 0x38


#define TIMEOUT 2000

unsigned long previousMillis = 0;

void stop(void);
void back(void);
void forward(void);

void setup() {
    Serial.begin(SERIAL_BAUNDRATE);
    pinMode(PIN_MOTOR_LEFT_FORWARD, OUTPUT);
    pinMode(PIN_MOTOR_LEFT_REVERSE, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT_FORWARD, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT_REVERSE, OUTPUT);

}

void loop() {
  unsigned long currentMillis = 0;
  currentMillis = millis();
  while (Serial.available()) {
    byte data = Serial.read();
    if (data != 0x02 && data != 0x00){
      Serial.write(data);
      switch(data){
        case COMMAND_FORWARD: {
          forward();
          break;
        }
        case COMMAND_BACK: {
          back();
          break;
        }
        case COMMAND_STOP: {
          stop();
          break;
        }
        default: break;
        break;
      }
    }
  }
  if (currentMillis - previousMillis >= TIMEOUT) {
    previousMillis = currentMillis;
    stop();
  }
}

void stop(){
  digitalWrite(13, LOW);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE, HIGH);
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE, HIGH);
}

void back(){
  digitalWrite(13, LOW);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE, LOW);
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE, LOW);
}


void forward(){
  digitalWrite(13, HIGH);
  digitalWrite(PIN_MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(PIN_MOTOR_LEFT_REVERSE, HIGH);
  digitalWrite(PIN_MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(PIN_MOTOR_RIGHT_REVERSE, HIGH);
}
