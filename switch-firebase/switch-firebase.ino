#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <SPI.h>
const char* ssid = "Aruu";
const char* password = "pentagon";
FirebaseData firebaseData;
FirebaseJsonData result;
#define PIN D4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  SPI.begin();
  konekWifi();
  Firebase.begin("https://switch-button-f685c-default-rtdb.asia-southeast1.firebasedatabase.app/", "c2r6yUH1a0qxGEPRrxSj6XF3STKHN5oozkGGOEBg");
}

void konekWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Sukses terkoneksi wifi!");
  Serial.println("IP Address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.getString(firebaseData, "/FBStatus")) {
    if (firebaseData.dataType() == "string") 
    {
      String FBStatus = firebaseData.stringData();
      if (FBStatus == "ON") {
        Serial.println("Relay ON");
        digitalWrite(PIN, HIGH);
      } else if (FBStatus == "OFF") {
        Serial.println("Relay OFF");
        digitalWrite(PIN, LOW);
      }
      else {Serial.println("Salah kode! isi dengan data ON/OFF");}
    }
  }
}
