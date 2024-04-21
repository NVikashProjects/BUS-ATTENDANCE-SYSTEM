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

float Students::calculateDistance(float lat1, float lon1, float lat2, float lon2){
  float dLat = radians(lat2 - lat1);
  float dLon = radians(lon2 - lon1);
  float a = sin(dLat / 2) * sin(dLat / 2) +
            cos(radians(lat1)) * cos(radians(lat2)) *
            sin(dLon / 2) * sin(dLon / 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  float distance = 6371 * c;
  return distance;
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