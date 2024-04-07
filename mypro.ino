#include <SPI.h>
#include <MFRC522.h>
#include "Students.h"


Students name;

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL3Rs_C7oze"
#define BLYNK_TEMPLATE_NAME "EFM"
#define BLYNK_AUTH_TOKEN "5lNgGe9ekjEbnJkDpNDWxUQU3l0TqWzS"

#include <BlynkSimpleEsp32.h>


#define RST_PIN 15
#define SS_PIN 5

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "EFWM";
char pass[] = "12345678";

MFRC522 mfrc522(SS_PIN, RST_PIN);

#define LED_PIN 2


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  name.SETID();

  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
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
    Serial.print(content.substring(1));
    if (content.substring(1) == name.Vikash()) {
      digitalWrite(LED_PIN, HIGH);
      Blynk.virtualWrite(V1, "vikash");
      delay(2000);
      Blynk.virtualWrite(V1, " ");
      digitalWrite(LED_PIN, LOW);
    }
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
