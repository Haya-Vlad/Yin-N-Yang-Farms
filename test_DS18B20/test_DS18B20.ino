#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20_PIN 16

OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32-S2 DS18B20 Test");
  Serial.println("==============================");

  sensors.begin();

  Serial.print("Number of sensors found: ");
  Serial.println(sensors.getDeviceCount());
}

void loop() {

  sensors.requestTemperatures();

  float temperatureC = sensors.getTempCByIndex(0);

  if (temperatureC == DEVICE_DISCONNECTED_C) {
    Serial.println("ERROxR: DS18B20 not detected!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(temperatureC, 2);
    Serial.println(" °C");
  }

  delay(1000);
}