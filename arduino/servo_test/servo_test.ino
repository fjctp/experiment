#include <Servo.h>

Servo s1;
int PWMPIN = 2;
bool toggle = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  s1.attach(PWMPIN, 1, 2);
  s1.write(0);
  
  Serial.println("start");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("live");
  if (toggle)
  {
    s1.write(90);
    toggle = false;
  }
  else
  {
    s1.write(0);
    toggle = true;
  }
  delay(3 * 1000);
}
