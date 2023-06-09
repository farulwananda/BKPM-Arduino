const int sensor_pin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float moisture_percentage;

  moisture_percentage = ( 100.00 - ((analogRead(sensor_pin)/1023.00) * 100.00) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.println(moisture_percentage);
  Serial.println("%");

  delay(1000);
}