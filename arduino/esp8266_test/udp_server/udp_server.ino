
/*
 * 
 * This program switch ESP8266 into AP mode and listen to 8080/UDP
 * for any connection.
 * If a message is received from a remote host, the program prints 
 * the sender's IPAddress, port number, and message to Serial.
 * It will response to the sender with message received.
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#define DEBUG 0

const char SSID[] = "ESP8266";
const char KEY[] = "12345678A";
const uint16_t UPD_PORT = 8080;
const uint8_t MAX_PACKET_SIZE = 255;

WiFiUDP udp;
char packetBuffer[MAX_PACKET_SIZE+1]; // add one for null char

//*********** Log functions
void info_log(int msg) {
  Serial.print(String(msg));
}
void info_log(String msg) {
  Serial.print(msg);
}

void debug_log(int msg) {
#if DEBUG
  Serial.print(String(msg));
#endif
}
void debug_log(String msg) {
#if DEBUG
  Serial.print(msg);
#endif
}
//*********** End

//*********** Support functions
void setup_ap(const char* ssid, const char* key ) {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, key);
  info_log("**STA: " + format_ip_address(WiFi.localIP()) + "\n");
  info_log("**AP: " + format_ip_address(WiFi.softAPIP()) + "\n");
}

void start_udp_server(uint16_t port) {
  if(udp.begin(port)) {
    info_log("**Listening to port ");
    info_log(port);
    info_log("\n");
  }
  else {
    info_log("E: Cannot open the port: ");
    info_log(port);
    info_log("\n");
  }
}

String format_ip_address(IPAddress address) {
  return String(address[0]) + "." + 
         String(address[1]) + "." + 
         String(address[2]) + "." + 
         String(address[3]);
}
//*********** End

//*********** Main Function
void setup() {
  Serial.begin(9600);
  
  info_log("\n");
  debug_log("**Starting AP\n");
  setup_ap(SSID, KEY);
  
  debug_log("**Starting UDP server\n");
  start_udp_server(UPD_PORT);
}

void loop() {
  uint8_t packetSize = udp.parsePacket();
  if(packetSize) {
    info_log("**From: "+ format_ip_address(udp.remoteIP()) + 
             ":" + String(udp.remotePort()) + "\n");
    uint8_t len = udp.read(packetBuffer, MAX_PACKET_SIZE);
    // if the packet size is less than 255
    // packetSize and len should match
    if(len>0 && len<MAX_PACKET_SIZE) {
      packetBuffer[len]='\0';
      info_log("Content: " + String(packetBuffer) + "\n");
    }
    
    info_log("**Response to request\n");
    if(udp.beginPacket(udp.remoteIP(), udp.remotePort())) {
      udp.write(packetBuffer, len);
      udp.endPacket();
    }
    else
      info_log("E: Failed to response\n");
  }
}
//*********** End