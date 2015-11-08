#include <FS.h>
#include <Esp.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EYFWebAPI.h>
#include "APIServer.h"

EYFWebAPI webApi;
APIServer apiServer;

bool initiated = false;

void setup() {
  Serial.begin ( 115200 );

  delay(150);

  Serial.write(CMD_CLEAR);
  Serial.write(CMD_SET_COLOR_GREEN);
  Serial.write( "Starting...");
  
  
  ESP8266WebServer* server = webApi.init(false);
  apiServer.init(server);

  while(!webApi.isReady())
    yield();

  char temp[400];

  IPAddress localIPApp = WiFi.localIP();
  IPAddress softAPIPAdd = WiFi.softAPIP();
  Serial.write(CMD_CLEAR);
  Serial.write(CMD_SET_COLOR_RED);
  Serial.write( "Wifi: "); 
 
  snprintf ( temp, 400, "%s\n", WiFi.SSID());
  Serial.write(CMD_SET_COLOR_GREEN);
  Serial.write(temp); 
 
  Serial.write(CMD_SET_COLOR_RED);
  Serial.write( "MAC: "); 
  snprintf ( temp, 400, "%s\n",WiFi.macAddress().c_str());
  Serial.write(CMD_SET_COLOR_GREEN);
  Serial.write(temp); 

  Serial.write(CMD_SET_COLOR_RED);
  Serial.write( "IP: "); 
  snprintf ( temp, 400, "%d.%d.%d.%d", localIPApp[0],localIPApp[1],localIPApp[2],localIPApp[3]);
  Serial.write(CMD_SET_COLOR_GREEN);
  Serial.write(temp); 
}

void loop() {
  wdt_reset();
  webApi.handleClient();
}


