#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>



#define FIREBASE_HOST "arduinoesp8266-9c87c.firebaseio.com"
#define FIREBASE_AUTH "SQDrCJYohN0ND7RyLNHTDe1yxK7NtPwUD4gZR5lv"
#define WIFI_SSID "ANUGERAH"
#define WIFI_PASSWORD "08127904595"
 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  s.begin(9600);
  while (!Serial) continue;
 
}
 
void loop() {


StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
 
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  
  float suhu1=root["suhu1"];
  Serial.println(suhu1);
   Firebase.setFloat("wsn1/suhu1", suhu1);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /suhu failed:");
      Serial.println(Firebase.error());
       return;  
     
  }
  


   float ph1=root["ph1"];
   Serial.println(ph1);
   Firebase.setFloat("wsn1/ph1", ph1);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /ph1 failed:");
      Serial.println(Firebase.error()); 
       return; 
      
  }
  

   float salinitas1=root["salinitas1"];
   Serial.println(salinitas1);
   Firebase.setFloat("wsn1/salinitas1", salinitas1);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /salinitas1 failed:");
      Serial.println(Firebase.error());  
       return;
      }
    
  



  //------- wsn2 -------------


}
