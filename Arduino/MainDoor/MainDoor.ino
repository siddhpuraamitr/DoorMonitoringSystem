#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecureBearSSL.h>

#define WIFI_SSID "YOUR_WIFI_SSID"//Change
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"//Change

ESP8266WiFiMulti WiFiMulti;
int switchRead=D1;
bool flag = true;
const char* url = "YOUR_FIREBASE_FUNCTION_URL";//Change
bool firstTime = true;
const int API_TIMEOUT = 10000;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);// This is just demo purpose
  connectWifi();
}

void connectWifi(){

  Serial.begin(115200);
  pinMode(switchRead,INPUT_PULLUP); 
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Setup method Complete");
}


void loop()
{ 
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    if(firstTime){
      delay(1000);
      callHttpURL("start");
      delay(1000);
      firstTime = false;
    }
    if (flag && digitalRead(switchRead) == HIGH){
       
      flag = false;
      callHttpURL("open");
    }
    else if (!flag && digitalRead(switchRead) == LOW){ 
      
      flag = true;
      callHttpURL("close"); 
    }
    
  }else{
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Trying to connect with WiFi...");
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  
}

String callHttpURL(String endPoint){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("callHttpURL Method called with endPoint -- "+endPoint);

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, url+endPoint)) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();
      
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
    digitalWrite(LED_BUILTIN, HIGH);
}
