/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
const unsigned int _DELAY = 500;
const unsigned int _LED_PIN = 3;

bool toggle;
unsigned long ptime;

void toggle_led() {
  if(toggle) {
    Serial.println("Setting LED to HIGH");
    digitalWrite(_LED_PIN, HIGH);
    toggle = false;
  }
  else {
    Serial.println("Setting LED to LOW");
    digitalWrite(_LED_PIN, LOW);
    toggle = true;
  }
}

void setup() {
  pinMode(_LED_PIN, OUTPUT); 
  Serial.begin(9600);
  
  Serial.println("This is a test!");
  ptime = millis();
  toggle = true;
}

void loop() {
  if(millis()-ptime>=_DELAY) {
    toggle_led();
    ptime = millis();
  }
}

