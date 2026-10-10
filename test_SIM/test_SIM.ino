#include <HardwareSerial.h>

// ==========================================
// SIM7670G UART
// ==========================================

HardwareSerial SIM7670(1);

// ESP32-S2-DevKitC-1
#define MODEM_TX 17   // ESP32-S2 GPIO17 -> SIM7670G RXD
#define MODEM_RX 18   // ESP32-S2 GPIO18 <- SIM7670G TXD

#define MODEM_BAUD 115200


void setup()
{
    // USB Serial Monitor
    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("====================================");
    Serial.println(" ESP32-S2 + SIM7670G UART TEST");
    Serial.println("====================================");

    // Start UART1
    SIM7670.begin(
        MODEM_BAUD,
        SERIAL_8N1,
        MODEM_RX,
        MODEM_TX
    );

    delay(2000);

    Serial.println("Sending AT command...");

    SIM7670.println("AT");

    delay(1000);

    while (SIM7670.available())
    {
        Serial.write(SIM7670.read());
    }

    Serial.println();
    Serial.println("Type AT commands below:");
}


void loop()
{
    // ==========================================
    // ESP32-S2 -> SIM7670G
    // ==========================================

    while (Serial.available())
    {
        char c = Serial.read();
        SIM7670.write(c);
    }


    // ==========================================
    // SIM7670G -> ESP32-S2 -> PC
    // ==========================================

    while (SIM7670.available())
    {
        char c = SIM7670.read();
        Serial.write(c);
    }
}