#ifndef EYFAPI_h
#define EYFAPI_h

#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// A class to make it easier to handle and pass around IP addresses

class EYFWebAPI {
  
private:
    ESP8266WebServer* server;
    bool debug;
    bool _isReady;
    void readConfig();
    void saveConfig();
    void connectWifi();
    void setupAP();
    void handle_status();
    void handle_setWIFI();
    void handle_setAP();
    void handle_reboot();
    void handle_404(); 
    void send(int code, const char* content_type, const String& content);
    
public:
    // Constructors
    EYFWebAPI();
    ESP8266WebServer* init(bool debug);
    void handleClient();
    bool isReady();
};

#endif

