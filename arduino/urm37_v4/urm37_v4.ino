#define URECHO_PIN 41
#define URTRIG_PIN 31

#define ACTIVE LOW
#define INACTIVE HIGH

unsigned int distance = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(URECHO_PIN, INPUT);
  pinMode(URTRIG_PIN, OUTPUT);
  //digitalWrite(URTRIG_PIN, INACTIVE);
  digitalWrite(URTRIG_PIN, ACTIVE);
  delay(500);
  Serial.println("Init the sersor"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  pwm_mode();
  delay(100);
}

void pwm_mode()
{
  //digitalWrite(URTRIG_PIN, ACTIVE);
  //digitalWrite(URTRIG_PIN, INACTIVE);
  
  unsigned long LowLevelTime = pulseIn(URECHO_PIN, LOW);
  if (LowLevelTime <= 25000)
  {
    distance = LowLevelTime / 50;
    Serial.print("distance = ");
    Serial.print(distance, DEC);
    Serial.print("cm, ");
    Serial.println(LowLevelTime, DEC);
  }
  else
    Serial.println("Invalid distance");
  
}
