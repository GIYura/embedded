#define LED_PIN     8

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {

  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  delay(250);
}
