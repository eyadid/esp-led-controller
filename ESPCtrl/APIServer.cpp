#include "APIServer.h"

const char *API_RETURN_TYPE = "text/javascript";
const char *API_RETURN_OK = "jsonp({ok:1});";
const char *API_RETURN_ERR = "jsonp({error:501});";


char tempHTTPUrlA[1024];
char tempHTTPUrlB[1024];

void urldecode2(char *dst, const char *src)
{
  char a, b;
  while (*src) {
    if ((*src == '%') &&
      ((a = src[1]) && (b = src[2])) &&
      (isxdigit(a) && isxdigit(b))) {
      if (a >= 'a')
        a -= 'a'-'A';
      if (a >= 'A')
        a -= ('A' - 10);
      else
        a -= '0';
      if (b >= 'a')
        b -= 'a'-'A';
      if (b >= 'A')
        b -= ('A' - 10);
      else
        b -= '0';
      *dst++ = 16*a+b;
      src+=3;
    } 
    else {
      *dst++ = *src++;
    }
  }
  *dst++ = '\0';
}

APIServer::APIServer()
{
}

void APIServer::init(ESP8266WebServer* server){
  this->server = server;
  server->on ( "/led/set-color", std::bind(&APIServer::handle_setColor, this) );
  server->on ( "/led/clear", std::bind(&APIServer::handle_clear, this) );
  server->on ( "/led/print", std::bind(&APIServer::handle_print, this) );
  server->on ( "/led/align", std::bind(&APIServer::handle_align, this) );
}

void APIServer::handle_clear(){
  Serial.write(CMD_CLEAR);
  this->server->send ( 200, API_RETURN_TYPE, API_RETURN_OK );
}

void APIServer::handle_print(){
  String text;
  for ( uint8_t i = 0; i < server->args(); i++ ) {
    if(server->argName(i) == "text"){
      text = server->arg(i);      
      if(text){
        text.toCharArray(tempHTTPUrlA, text.length()+1);
        urldecode2(tempHTTPUrlB,tempHTTPUrlA);
        Serial.print(tempHTTPUrlB);   
        this->server->send ( 200, API_RETURN_TYPE, API_RETURN_OK );
        return; 
      }
    }
  }
  this->server->send( 501, API_RETURN_TYPE, API_RETURN_ERR);
}

void APIServer::handle_align(){
  for ( uint8_t i = 0; i < server->args(); i++ ) {
    if(server->argName(i) == "direction"){
      if(server->arg(i) == "left"){
        Serial.write(CMD_ALIGN_LEFT);
      }else if(server->arg(i) == "right"){
        Serial.write(CMD_ALIGN_RIGHT);
      }else if(server->arg(i) == "center"){
        Serial.write(CMD_ALIGN_CENTER);
      }else{
        this->server->send( 501, API_RETURN_TYPE, API_RETURN_ERR);
        return;
      }
      this->server->send ( 200, API_RETURN_TYPE, API_RETURN_OK );
      return;
    }  
  }
}

void APIServer::handle_setColor(){
  for ( uint8_t i = 0; i < server->args(); i++ ) {
    if(server->argName(i) == "color"){
      if(server->arg(i) == "green"){
        Serial.write(CMD_SET_COLOR_GREEN);
      }else if(server->arg(i) == "orange"){
        Serial.write(CMD_SET_COLOR_ORANGE);
      }else if(server->arg(i) == "red"){
        Serial.write(CMD_SET_COLOR_RED);
      }else if(server->arg(i) == "blink_orange"){
        Serial.write(CMD_SET_COLOR_BLINK_ORANGE);
      }else if(server->arg(i) == "blink_green"){
        Serial.write(CMD_SET_COLOR_BLINK_GREEN);
      }else if(server->arg(i) == "blink_red"){
        Serial.write(CMD_SET_COLOR_BLINK_RED);
      }else{
        this->server->send( 501, API_RETURN_TYPE, API_RETURN_ERR);
        return;
      }
      this->server->send ( 200, API_RETURN_TYPE, API_RETURN_OK );
      return;
    }  
  }
}




