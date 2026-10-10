#define MHZ19_RX 16   // ESP32 receives from MH-Z19B TX
#define MHZ19_TX 17   // ESP32 transmits to MH-Z19B RX

HardwareSerial MHZ19(1);

void setup() {
  Serial.begin(115200);

  // MH-Z19B UART
  // 9600 baud, 8 data bits, no parity, 1 stop bit
  MHZ19.begin(9600, SERIAL_8N1, MHZ19_RX, MHZ19_TX);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("Winsen MH-Z19B CO2 Test");
  Serial.println("==============================");
  Serial.println("Waiting for sensor...");
}

void loop() {

  // MH-Z19B read CO2 command
  byte command[9] = {
    0xFF,
    0x01,
    0x86,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x79
  };

  // Clear any old data
  while (MHZ19.available()) {
    MHZ19.read();
  }

  // Send command
  MHZ19.write(command, 9);

  // Give sensor time to respond
  delay(100);

  // We expect 9 bytes
  if (MHZ19.available() >= 9) {

    byte response[9];

    for (int i = 0; i < 9; i++) {
      response[i] = MHZ19.read();
    }

    // Check response header
    if (response[0] == 0xFF && response[1] == 0x86) {

      int co2 = (response[2] << 8) | response[3];

      Serial.print("CO2: ");
      Serial.print(co2);
      Serial.println(" ppm");

    }
    else {
      Serial.println("Invalid response from MH-Z19B");
    }

  }
  else {
    Serial.println("No response from MH-Z19B");
  }

  delay(2000);
}