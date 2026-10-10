#define TRIG_PIN 16
#define ECHO_PIN 17

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("AJ-SR04M Ultrasonic Test");
  Serial.println("================================");
}

void loop() {

  // Trigger ultrasonic measurement
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure ECHO pulse
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    Serial.println("No echo / Out of range");
  } 
  else {

    float distance_cm = duration * 0.0343 / 2.0;

    Serial.print("Echo = ");
    Serial.print(duration);
    Serial.print(" us    Distance = ");
    Serial.print(distance_cm, 2);
    Serial.println(" cm");
  }

  delay(500);
}