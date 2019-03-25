#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  
  const char msgON[] = "ON";
  const char msgOFF[] = "OFF";
  radio.write(&msgON, sizeof(msgON));
  delay(1000);
  radio.write(&msgOFF, sizeof(msgOFF));
  delay(1000);
}
