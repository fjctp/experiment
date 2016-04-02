#include <Servo.h>

#define PIN 2
#define PULSEMIN 1
#define PULSEMAX 1

Servo s1;
char buffer[128];
int8_t i = 0;
uint8_t speed = 0;
bool ready = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  s1.attach(PIN, PULSEMIN, PULSEMAX);
  s1.write(90);
  
  Serial.println("Enter a number between 0 and 180");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0) {
    buffer[i] = Serial.read();
    if(buffer[i]==';') {
      buffer[i] = '\0'; // replace ';' with '\0'
      speed = atoi(buffer); // convert string to int

      // reset
      ready = true;
      i = -1;
    }
    i++;
  }

  if(ready) {
    Serial.print("Sending: ");
    Serial.println(speed, DEC);
    s1.write(speed);
    ready = false;
  }
}
