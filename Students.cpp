#include "esp32-hal-gpio.h"
#include "Students.h"


void Students::SETID() {
  vikashId = "53 7B 2C DD";
  vijayId = "63 87 0A FB";
  kavinId = "39 E8 CB 99";
}
void Students::ledState(int pinNumber) {
    pinMode(pinNumber, OUTPUT);
    led = pinNumber;
}

void Students::ledOn(){
  digitalWrite(led, HIGH);
}

void Students::ledOff(){
  digitalWrite(led, LOW);
}

String Students::Vikash() {
  return vikashId;
}

String Students::Vijay() {
  return vijayId;
}

String Students::Kavin() {
  return kavinId;
}