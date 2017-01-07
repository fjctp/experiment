
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

RF24* r1;
RF24* r2;
byte addresses[][6] = {"1Node", "2Node"};
uint8_t sender = 2; // which radio is the sender

uint8_t ce1=22, cs1=4, ce2=23, cs2=10;

void setup() {
  Serial.begin(115200);
  Serial.println("RF24 Test");

  // Radio 1
  r1 = new RF24(ce1, cs1);
  r1->begin();
  r1->enableAckPayload();
  r1->enableDynamicPayloads();
  r1->openWritingPipe(addresses[0]);
  r1->openReadingPipe(1, addresses[1]);
  r1->startListening();

  // Radio 2
  r2 = new RF24(ce2, cs2);
  r2->begin();
  r2->enableAckPayload();
  r2->enableDynamicPayloads();
  r2->openWritingPipe(addresses[1]);
  r2->openReadingPipe(1, addresses[0]);
  r2->startListening();
  
}

void loop() {
  char bf[9];
  if (r1->available()) {
    r1->read(bf, 8);
    bf[8] = '\0';
    Serial.print("R1: ");
    Serial.println(bf);
  }
  else if (r2->available()) {
    r2->read(bf, 8);
    bf[3] = '\0';
    Serial.print("R2: ");
    Serial.println(bf);
  }
  else {
    if (sender == 1) {
      r1->stopListening();
      if (!(r1->write("R1SayHi;", 8)))
        Serial.println("Failed to send");
      r1->startListening();
    }
    else {
      r2->stopListening();
      if (!(r2->write("R2SayHi;", 8)))
        Serial.println("Failed to send");
      r2->startListening();
    }
  }
  
  delay(2*1000);
}
