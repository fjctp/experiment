/*
 *
 * This program acts as a middle man for UDP and serial port. 
 * Any message received from UDP/8080is forwarded to serial port.
 * Any message received from serial port is forwarded to UDP/8080.
 * 
 * Reference: https://github.com/esp8266/Arduino
 *
 * PS: tried to use uint8_t[] for remoteIP (for UDP read/write functions), 
 *     but it did not work. looks like any uintXX_t will not work, 
 *     except for unsigned int.
 */



#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#define DEBUG 0

const char SSID[] = "ESP8266"; // AP SSID
const char KEY[] = "12345678A"; // AP password
const uint16_t UPD_PORT = 8080;
const uint8_t MAX_PACKET_SIZE = 255;

WiFiUDP udp;

//*********** Setup and misc. functions
IPAddress setup_ap(const char* ssid, const char* key ) {
  debug_log("Starting AP\n");
  WiFi.mode(WIFI_AP); // options: WIFI_AP, WIFI_STA, WIFI_AP_STA or WIFI_OFF
  WiFi.softAP(ssid, key);
  return WiFi.softAPIP();
}

uint16_t start_udp_server(uint16_t port) {
  debug_log("Starting UDP server\n");
  if (udp.begin(port)) {
    return port;
  }
  else {
    debug_log("Failed to start UDP server on port " + String(port) + "\n");
    return 0;
  }
}

String IPAddressToString(const IPAddress address) {
  return String(address[0]) + "." + 
         String(address[1]) + "." + 
         String(address[2]) + "." + 
         String(address[3]);
}
String IPAddressToString(const unsigned int address[]) {
  return String(address[0]) + "." + 
         String(address[1]) + "." + 
         String(address[2]) + "." + 
         String(address[3]);
}
//*********** End


//*********** UDP functions
uint8_t udp_write(const unsigned int remoteIP[], const uint16_t remotePort, const char* message) {
  if(udp.beginPacket(IPAddress(
      remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3]
      ), remotePort)) {
    udp.write(message, strlen(message));
    udp.endPacket();
    return 1;
  }
  else
    return 0;
}
uint8_t udp_read(unsigned int remoteIP[], uint16_t& remotePort, char* packetBuffer, uint8_t max_len) {
  uint8_t packetSize = udp.parsePacket(); // parse the packet before doing anything else
  if(packetSize) {
    remotePort = udp.remotePort();
    for(int i=0; i<4; i++) {
      remoteIP[i] = (udp.remoteIP())[i];
    }

    uint8_t len = udp.read(packetBuffer, max_len-1); // if the packet size is less than 255
                                                     // packetSize and len should match
    if(len>0 && len<max_len) {
      for(int i=0;i<len;i++) {
        if (packetBuffer[i]=='\n')
          packetBuffer[i]='\0';
      }
      packetBuffer[len]='\0';
      debug_log(String(strlen(packetBuffer)) + 
                ": " + 
                IPAddressToString(remoteIP) + 
                ":" + 
                String(remotePort) +
                "\n");
      return len;
    }
    else
      return packetSize;
  }
  else
    return packetSize;
}
//*********** End


//*********** Serial functions
//*********** Log functions
// used to format the string for serial comm
void info_log(String msg) {
  serial_raw_write("I," + msg);
}
void info_log(int msg) {
  info_log(String(msg));
}

void debug_log(String msg) {
#if DEBUG
  serial_raw_write("D," + msg);
#endif
}
void debug_log(int msg) {
#if DEBUG
  debug_log(String(msg));
#endif
}
//*********** End Log functions

void serial_flush_input(uint8_t len) {
  // flush the input buffer
  while(Serial.available()>0 && len-->0) 
    Serial.read();
}
void serial_raw_write(const String message) {
  Serial.print(message);
}
void serial_raw_write(const char *message) {
  Serial.print(message);
}
uint8_t serial_raw_read (char packetBuffer[], uint8_t max_len) {
  uint8_t packetSize = Serial.available();
  if(packetSize) {
    if(packetSize<(max_len-1)) {
      Serial.readBytes(packetBuffer, packetSize);
      packetBuffer[packetSize+1]='\0';
    }
    else {
      Serial.readBytes(packetBuffer, max_len-1);
      packetBuffer[max_len]='\0';
      packetSize = max_len;
    }
  }
  else {
    serial_flush_input(packetSize);
  }
  return packetSize;
}
//*********** End

//*********** Main Function
unsigned int remoteIP[4];
uint16_t remotePort;

void setup() {
  Serial.begin(9600);
  
  info_log("\nready\n");
  info_log("APIP:" + IPAddressToString(setup_ap(SSID, KEY)) + "\n");
  info_log("listening to " + String(start_udp_server(UPD_PORT)) + "\n");
  
}

void loop() {
  char packetBuffer[MAX_PACKET_SIZE];

  // check UDP
  if(udp_read(remoteIP, remotePort, packetBuffer, MAX_PACKET_SIZE)) {
    serial_raw_write(packetBuffer);
  }

  // check Serial
  if(serial_raw_read(packetBuffer, MAX_PACKET_SIZE)) {
    debug_log(String(strlen(packetBuffer)) + 
              ": " + 
              IPAddressToString(remoteIP) + 
              ":" + 
              String(remotePort) +
              "\n");
    if (remoteIP != 0 and remotePort != 0)
      udp_write(remoteIP, remotePort, packetBuffer);
  }

#if DEBUG
  delay(1000);
#endif
}
//*********** End
