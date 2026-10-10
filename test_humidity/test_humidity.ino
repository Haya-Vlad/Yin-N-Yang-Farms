#include <Wire.h>

#define SDA_PIN 3
#define SCL_PIN 4

#define SENSOR_ADDRESS 0x44

void setup() {
  Serial.begin(115200);

  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println();
  Serial.println("==============================");
  Serial.println("7Semi ES-13511 Test");
  Serial.println("==============================");
}

void loop() {

  // Send high-precision measurement command
  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(0xFD);
  byte error = Wire.endTransmission();

  if (error != 0) {
    Serial.print("I2C communication error: ");
    Serial.println(error);
    delay(1000);
    return;
  }

  // ES-13511 high precision measurement takes up to ~8.3 ms
  delay(10);

  // Read 6 bytes:
  // Temperature MSB
  // Temperature LSB
  // Temperature CRC
  // Humidity MSB
  // Humidity LSB
  // Humidity CRC
  int received = Wire.requestFrom(SENSOR_ADDRESS, 6);

  if (received != 6) {
    Serial.print("Expected 6 bytes, received: ");
    Serial.println(received);
    delay(1000);
    return;
  }

  uint16_t temperatureRaw =
      ((uint16_t)Wire.read() << 8) | Wire.read();

  byte temperatureCRC = Wire.read();

  uint16_t humidityRaw =
      ((uint16_t)Wire.read() << 8) | Wire.read();

  byte humidityCRC = Wire.read();

  // Convert raw values
  float temperatureC =
      -45.0 + 175.0 * ((float)temperatureRaw / 65535.0);

  float humidity =
      -6.0 + 125.0 * ((float)humidityRaw / 65535.0);

  // Limit RH to physical range
  if (humidity < 0) {
    humidity = 0;
  }

  if (humidity > 100) {
    humidity = 100;
  }

  Serial.print("Temperature: ");
  Serial.print(temperatureC, 2);
  Serial.println(" °C");

  Serial.print("Humidity:    ");
  Serial.print(humidity, 2);
  Serial.println(" %RH");

  Serial.println("------------------------------");

  delay(1000);
}