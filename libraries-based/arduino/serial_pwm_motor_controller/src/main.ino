
/*
 * enter a number from serial monitor (0-10 end
 * with terminate char)
 * the motor will response (0-100% power)
 * Note: max input char: 3 incl. terminate char
 */

const int PIN = 3;
const int ANALOG_MIN = 0;
const int ANALOG_MAX = 255;
const int TERMINATE_CHAR = 'e';

char ibf[4];
int i;
bool isReady;

void setReady() {
  ibf[i]='\0';
  isReady=true;
}

void reset() {
  i=0;
  isReady=false;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.println("Start");
  analogWrite(PIN,
    map(0, 0, 100, ANALOG_MIN, ANALOG_MAX)); 
    
  reset();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {
    if (i<3) {
      int bf = Serial.read();
      Serial.print("RAW:");
      Serial.print(bf, HEX);
      Serial.print(", ");
      if (bf==TERMINATE_CHAR) { // match 'e'
        setReady();
      }
      else {
        ibf[i++]=bf;
      }
    }
    else {
      setReady();
    }
  }
  
  if (isReady) { 
    Serial.println("");
    Serial.println("bytes:");
    Serial.print(ibf[0], HEX);
    Serial.print(", ");
    Serial.print(ibf[1], HEX);
    Serial.print(", ");
    Serial.print(ibf[2], HEX);
    Serial.print(", ");
    Serial.println(ibf[3], HEX);
    
    int power = atoi(ibf) * 10;
    if (power<0 and power>100)
      power=0;
    int ana = map(power, 0, 100, ANALOG_MIN, ANALOG_MAX);
    
    Serial.println("I/O:");
    Serial.print(power, DEC);
    Serial.print(", ");
    Serial.println(ana, DEC);
    Serial.println("");
    analogWrite(PIN, ana);
    
    //reset the count
    reset();
  }
}

