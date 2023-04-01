#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D2
#define RST_PIN D3

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

String strID;

// Isikan sesuai pada Firebase
#define FIREBASE_HOST "https://sensor-rfid-2882a-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "0RcM4g223zqJ8Gzih445fqQeC5uIAPOC6XPTPcte"

//Nama Wifi
#define WIFI_SSID "Beryl_Onyx"
#define WIFI_PASSWORD "berylonyx"  

// mendeklarasikan objek data dari FirebaseESP8266
FirebaseData firebaseData;

void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  rfid.PCD_Init();
  Serial.begin(9600);
  Serial.println("I am waiting for card...");

    // Koneksi ke Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  strID = "";
  for(byte i = 0; i < rfid.uid.size; i++){
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +

      String(rfid.uid.uidByte[i], HEX) +
      (i != rfid.uid.size - 1 ? ":" : "");
  }

  strID.toUpperCase();
  Serial.print("Kartu ID Anda : ");
  Serial.println(strID);
  Firebase.setString(firebaseData, "Data_RFID/data", strID);
  delay(1000);
}