/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLLa-yWQHe"
#define BLYNK_DEVICE_NAME "DHT11"
// #define BLYNK_AUTH_TOKEN ""


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN D4
#define DHTTYPE DHT11


char auth[] = "4a-7LxcrHYGCOqPuaDItfIBwHEvMN5S9";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lalala";
char pass[] = "berylonyx";

BlynkTimer timer;
float t;
float h;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}

void sendSensor(){
  h = dht.readHumidity();
  t = dht.readTemperature();

  if(isnan(h) || isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Kelembapan: "); Serial.println(h);
  Serial.print("Suhu: "); Serial.println(t);

  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V5, t);
}