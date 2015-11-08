
#ifndef APIServer_h
#define APIServer_h
#include <Esp.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#define CMD_CLEAR             1
#define CMD_SET_COLOR_RED     2
#define CMD_SET_COLOR_GREEN   3
#define CMD_SET_COLOR_ORANGE  4
#define CMD_SET_COLOR_BLINK_RED     5
#define CMD_SET_COLOR_BLINK_GREEN   6
#define CMD_SET_COLOR_BLINK_ORANGE  7
#define CMD_ALIGN_LEFT 8
#define CMD_ALIGN_CENTER 11
#define CMD_ALIGN_RIGHT 12

// A class to make it easier to handle and pass around IP addresses

class APIServer {
private:
    ESP8266WebServer* server;
  
public:
    APIServer();
    void init(ESP8266WebServer* server);
    void handle_setColor();
    void handle_print();
    void handle_clear();  
    void handle_align();  
};

#endif





