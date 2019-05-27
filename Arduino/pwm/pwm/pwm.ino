#define LED     9

void setup() {
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
}

void loop() {
    for(int i = 0; i < 255; i += 2){
        analogWrite(LED, i);
        delay(20);
    }
    for(int i = 255; i > 0; i -= 2){
        analogWrite(LED, i);
        delay(20);
    }
}
