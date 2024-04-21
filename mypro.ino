#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3X-IlL1MU"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "QpeFQvsM98917FtGycBiVAGaa322ljLt"
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include "Students.h"
#include <SPI.h>
#include <MFRC522.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


#define RST_PIN 4
#define SS_PIN 5

Students name;
TinyGPSPlus gps;

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial gpsSerial(27, 26);
MFRC522 mfrc522(SS_PIN, RST_PIN);


int set1 = 0, set2 = 0, set3 = 0;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "EFWM";
char pass[] = "12345678";


#define LED_PIN 2
String Namelist;
int SeatCount = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  gpsSerial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  name.SETID();
  lcd.init();
  lcd.backlight();
  mfrc522.PCD_Init();


  name.ledState(LED_PIN);
  name.ledOn();
  SeatCount = 0;
  delay(1000);
  name.ledOff();

  Serial.println("Ready to read RFID tags...");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String content = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    Serial.println(content.substring(1));
    if (content.substring(1) == name.Vikash() && set1 == 0) {
      Blynk.virtualWrite(V1, "Vikash");
      Namelist = "Vikash";
      SeatCount += 1;
      set1 = 1;
    } else if (content.substring(1) == name.Vijay() && set2 == 0) {
      Blynk.virtualWrite(V3, "Vijay");
      Namelist = "Vijay";
      SeatCount += 1;
      set2 = 1;
    } else if (content.substring(1) == name.Kavin() && set3 == 0) {
      Blynk.virtualWrite(V4, "Kavin");
      Namelist = "Kavin";
      SeatCount += 1;
      set3 = 1;
    }
    Blynk.virtualWrite(V2, SeatCount);
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Seat Count : ");
  lcd.print(SeatCount);
  lcd.setCursor(0, 1);
  lcd.print("Name : " + Namelist);
  delay(500);

  if (SeatCount == 0) {
    Blynk.virtualWrite(V1, " ");
    Blynk.virtualWrite(V3, " ");
    Blynk.virtualWrite(V4, " ");
    Blynk.virtualWrite(V2, SeatCount);
  }

   if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
}
