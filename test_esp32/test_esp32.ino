#include <Adafruit_NeoPixel.h>

#define RGB_PIN 18   // Onboard RGB LED data pin
#define NUM_PIXELS 1

Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixel.begin();
  pixel.setBrightness(50);
  pixel.show();  // Turn off initially
}

void loop() {
  // RED
  pixel.setPixelColor(0, pixel.Color(255, 0, 0));
  pixel.show();
  delay(1000);

  // GREEN
  pixel.setPixelColor(0, pixel.Color(0, 255, 0));
  pixel.show();
  delay(1000);

  // BLUE
  pixel.setPixelColor(0, pixel.Color(0, 0, 255));
  pixel.show();
  delay(1000);

  // OFF
  pixel.clear();
  pixel.show();
  delay(1000);
}