#include "EYFWebAPI.h"

const char *WEBAPI_RETURN_TYPE = "text/javascript";
const char *WEBAPI_RETURN_OK = "{ok:1}";
const char *WEBAPI_RETURN_ERR = "{error:501}";
const char *CONFIG_FILENAME = "/config";

char config_Wifi_SSID[31];
char config_Wifi_PSK[63];
char config_AP_SSID[31];
char config_AP_PSK[63];

EYFWebAPI::EYFWebAPI()
{
	
}

void EYFWebAPI::connectWifi(){
  
  _isReady = false;
  
  if(this->debug){
    Serial.print("WIFI-");
    Serial.print(config_Wifi_SSID);
    Serial.print("-");
    Serial.print(config_Wifi_PSK);
    Serial.println("-");
  }
  
  WiFi.begin((const char*)&config_Wifi_SSID, (const char*)&config_Wifi_PSK);
  
  int abrt = 60;
  int state = 0;
  
  while ( (state = WiFi.status()) != WL_CONNECTED && --abrt > 0) {
    delay ( 1000 );
    if(this->debug){
      Serial.print(".");
    }
  }
  if(this->debug){
  
    Serial.println("");
  
    if( WiFi.status() == WL_CONNECTED ){
      Serial.print("Connected to ");
      Serial.println(WiFi.SSID());
      Serial.print("IP address: ");
      Serial.println ( WiFi.localIP() );
    }else{
      Serial.println ( "No wifi");
    }  
    
  }
  
  _isReady = true;
}

bool EYFWebAPI::isReady()
{
  return this->_isReady;
}

ESP8266WebServer* EYFWebAPI::init(bool debug){

  this->debug = debug;

  SPIFFS.begin();
	
  this->readConfig();
	
	server = new ESP8266WebServer(80);
  if(this->debug){
	 Serial.println("Init Web API...");
  }
	
  this->setupAP();  
  this->connectWifi();

	server->on ( "/api/set-wifi", std::bind(&EYFWebAPI::handle_setWIFI, this) );
	server->on ( "/api/set-ap", std::bind(&EYFWebAPI::handle_setAP, this) );
	server->on ( "/api/status", std::bind(&EYFWebAPI::handle_status, this) );
	server->on ( "/api/reboot", std::bind(&EYFWebAPI::handle_reboot, this) );
  
	server->onNotFound ( std::bind(&EYFWebAPI::handle_404, this) );
  
	server->begin();
  
  return server;
}

void EYFWebAPI::setupAP(){
 	WiFi.mode(WIFI_AP_STA);
  if(this->debug){
    Serial.println(config_AP_SSID);
    Serial.println(config_AP_PSK);
  }
  if(!config_AP_SSID || config_AP_SSID[0] == 0){
     if(this->debug){
      Serial.println("Default");
     }
	   WiFi.softAP("WowSuchLED","qqqqqqqq");
  }else{
    WiFi.softAP((const char*)&config_AP_SSID, (const char*)&config_AP_PSK);
  }
}

void EYFWebAPI::readConfig(){
  
  File f = SPIFFS.open(CONFIG_FILENAME, "r");
  
  if (!f) {
      return;
  } else {
      String read;
      int r = 0;      
      while(f.available()){
        read = f.readStringUntil('\n');
        if(read){
          if(r == 0)        read.toCharArray(config_Wifi_SSID, read.length());
          else if(r == 1)   read.toCharArray(config_Wifi_PSK, read.length());    
          else if(r == 2)   read.toCharArray(config_AP_SSID, read.length());
          else if(r == 3)   read.toCharArray(config_AP_PSK, read.length());    
        }
        r++;
      }
      
      f.close();
   }
}
void EYFWebAPI::saveConfig(){

    File f = SPIFFS.open(CONFIG_FILENAME, "w");
    if (!f) {
      if(this->debug){
        Serial.println("file creation failed");
      }
      return;
    }
    
    f.println(config_Wifi_SSID);
    f.println(config_Wifi_PSK);
    f.println(config_AP_SSID);
    f.println(config_AP_PSK);
    
    f.close();    
}

void EYFWebAPI::handleClient(){
	server->handleClient();
}

void EYFWebAPI::handle_status(){
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  IPAddress localIPApp = WiFi.localIP();
  IPAddress softAPIPAdd = WiFi.softAPIP();

  snprintf ( temp, 400,
"{\
 uptime: \"%02d:%02d:%02d\",\
 freespace:%d,\
 sketchsize:%d,\
 size:%d,\
 vcc:%d,\
 freeheap:%d,\
 chipid:\"%d\",\
 sdk:\"%s\",\
 bootver:%d,\
 wifi:{\
  status : %d,\
  ssid: \"%s\",\
  ip: \"%d.%d.%d.%d\",\
  mac: \"%s\"\
 },\
 ap:{\
  ssid: \"%s\",\
  ip: \"%d.%d.%d.%d\",\
  mac: \"%s\"\
 }\
}"
  ,hr, min % 60, sec % 60,
  ESP.getFreeSketchSpace(),
  ESP.getSketchSize(),
  ESP.getFlashChipRealSize(),
  ESP.getVcc(),
  ESP.getFreeHeap(),
  ESP.getChipId(),
  ESP.getSdkVersion(),
  ESP.getBootVersion(),
  WiFi.status(),
  WiFi.SSID(),
  localIPApp[0],localIPApp[1],localIPApp[2],localIPApp[3],
  WiFi.macAddress().c_str(), 
  config_AP_SSID,
  softAPIPAdd[0],softAPIPAdd[1],softAPIPAdd[2],softAPIPAdd[3],
  WiFi.softAPmacAddress().c_str());
  this->send ( 200, WEBAPI_RETURN_TYPE, temp );
}

void EYFWebAPI::handle_reboot(){
  this->send ( 200, WEBAPI_RETURN_TYPE, WEBAPI_RETURN_OK );
  ESP.restart(); 
}
void EYFWebAPI::handle_setAP(){
  String ssid;
  String psk;
  
  for ( uint8_t i = 0; i < server->args(); i++ ) {
    if(server->argName(i) == "ssid"){
      ssid = server->arg(i);
    }else if(server->argName(i) == "psk"){
      psk = server->arg(i);
    }
  }
  
  if(ssid && psk){

    ssid.toCharArray(config_AP_SSID, ssid.length()+1);
    psk.toCharArray(config_AP_PSK, psk.length()+1);
        
    this->saveConfig();
    this->send( 200, WEBAPI_RETURN_TYPE, WEBAPI_RETURN_OK);
    
    this->setupAP();
    
  }else{
    this->send( 501, WEBAPI_RETURN_TYPE, WEBAPI_RETURN_ERR);
  }
}

void EYFWebAPI::handle_setWIFI(){
  String ssid;
  String psk;
  
  for ( uint8_t i = 0; i < server->args(); i++ ) {
    if(server->argName(i) == "ssid"){
      ssid = server->arg(i);
    }else if(server->argName(i) == "psk"){
      psk = server->arg(i);
    }
  }
  
  if(ssid && psk){

    ssid.toCharArray(config_Wifi_SSID, ssid.length()+1);
    psk.toCharArray(config_Wifi_PSK, psk.length()+1);
    
    this->saveConfig();
    this->send( 200, WEBAPI_RETURN_TYPE, WEBAPI_RETURN_OK);
    
    this->connectWifi();
    
  }else{
    this->send( 501, WEBAPI_RETURN_TYPE, WEBAPI_RETURN_ERR);
  }
}

void EYFWebAPI::handle_404() {
  this->send(404, WEBAPI_RETURN_TYPE, "{error:404}");
}


void EYFWebAPI::send(int code, const char* content_type, const String& content){
  String rid;
  
  for ( uint8_t i = 0; i < server->args(); i++ ) {
    if(server->argName(i) == "rid"){
      rid = server->arg(i);
      break;
    }
  }

  server->send(code, content_type, "jsonp(" + content + "," + rid + ");");
}