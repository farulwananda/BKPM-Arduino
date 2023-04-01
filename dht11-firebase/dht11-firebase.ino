#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

#define FIREBASE_HOST "https://sensor-dht11-46357-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "QKPlOZAMtegnwqTUDVF2uWTXQyqEzXczBmYO3LwN"
#define WIFI_SSID "Da_Vinci"
#define WIFI_PASSWORD "pentagon"


#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT Sensor!"));
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  String fireHumid = String(h) + String("%");
  Serial.print("% Temperature: ");
  Serial.print(t);
  Serial.println("C");
  String fireTemp = String(t) + String("C");
  delay(5000);

  Firebase.pushString("/DHT11/Humidity", fireHumid);
  Firebase.pushString("/DHT11/Temperature", fireTemp);
  if (Firebase.failed()) {
    Serial.print("Pushing / logs failed:");
    Serial.print(Firebase.error());
    return;
  }

}
