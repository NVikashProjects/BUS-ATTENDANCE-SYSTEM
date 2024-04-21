#ifndef Students_h
#define Students_h
#include <Arduino.h>


class Students {
  private:
  String vikashId;
  String vijayId;
  String kavinId;

  //led pin mode
  int led;

public:
  void SETID();
  String Vikash();
  String Vijay();
  String Kavin();
  void ledState(int pinNumber);
  void ledOn();
  void ledOff();
  float calculateDistance(float lat1, float lon1, float lat2, float lon2);
};

#endif