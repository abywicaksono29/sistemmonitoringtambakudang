#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
SoftwareSerial s(5,6);
#include <ArduinoJson.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); 
//create an RF24 object
RF24 radio(7, 8);  // CE, CSN
float nilai;
float node1[5];
float node2[5];

//address through which two modules communicate.
const byte address[6] = {0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL} ;

void setup()
{   
  lcd.begin();
  lcd.backlight();
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  //set the address
  radio.openReadingPipe(0, address[0]);
  radio.openReadingPipe(1, address[1]);
  
  //Set module as receiver
  radio.startListening();
  Serial.begin(9600);
  s.begin(9600);
}

void loop() {
  
float  kondisi = 0 ;
  byte nomorPipa = 0;
if ( kondisi == 0 )
{
while(radio.available(&nomorPipa)){
      if(nomorPipa+1 == 1){
        radio.read(&node1, sizeof(node1));
        Serial.println ("node1");
        Serial.println (node1[0]);
        Serial.println (node1[1]);
        Serial.println (node1[2]);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("node 1");
        lcd.setCursor(0,1);
        lcd.print("salinitas= ");
        lcd.print (node1[1]);
        lcd.setCursor(0,2);
        lcd.print("ph=");
        lcd.print(node1[0]);
        lcd.setCursor(0,3);
        lcd.print("suhu=");
        lcd.print(node1[2]);
        }
         
         else if(nomorPipa+1 == 2){
        radio.read(&node2, sizeof(node2));
        Serial.println ("node2");
        Serial.println (node2[0]);
        Serial.println (node2[1]);
        Serial.println (node2[2]);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("node 2");
        lcd.setCursor(0,1);
        lcd.print("salinitas= ");
        lcd.print (node2[1]);
        lcd.setCursor(0,2);
        lcd.print("ph=");
        lcd.print(node2[0]);
        lcd.setCursor(0,3);
        lcd.print("suhu=");
        lcd.print(node2[2]);
         }
         
      else{
        Serial.println("Tetap Semangat, tetap semangat, uuuuu, tetap semangat");
      }
 delay (1000);
    

 StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
  root["suhu1"] = node1[2];
  root["ph1"] = node1[0];
  root["salinitas1"] = node1[1];
  root["suhu2"] = node2[0];
  root["ph2"] = node2[1];
  root["salinitas2"] = node2[2];
 root.printTo(s);
    }
  }
}
