#include <LiquidCrystal_I2C.h>

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <nRF24L01.h>
#include <RF24.h>
 
 LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); 
// sensor diletakkan di pin 2
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
RF24 radio(7, 8);
const byte address[6] = {0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL} ;
// berikan nama variabel,masukkan ke pustaka Dallas
DallasTemperature sensorSuhu(&oneWire);


float node1[5];
float val[10];
float rata_rata_voltage;
float teg;
float rata_rata_val;
float suhuAir; //change this value to calibrate
float voltagesal;
float voltage[10];
float sal;
float pHVol;
float pHValue = 0.0 ;

void setup() {
  sensorSuhu.begin();
  lcd.begin();
  lcd.backlight();
  Serial.begin(38400);
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address[0]);
 radio.stopListening();
}
 
void loop() {
 
 suhu();
 salinitas();
 ph();
 
  node1[0] = pHValue;
  node1[1] = sal;
  node1[2] = suhuAir;

 radio.write(&node1, sizeof(node1));
 delay (1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("node 1");
  lcd.setCursor(0,1);
  lcd.print("salinitas= ");
  lcd.print (sal);
  lcd.setCursor(0,2);
  lcd.print("ph=");
  lcd.print(pHValue);
  lcd.setCursor(0,3);
  lcd.print("suhu");
  lcd.print(suhuAir);
  
  
  Serial.print("ph = ");
  Serial.println(pHValue);
  Serial.print("konduktifitas = ");
  Serial.println(sal);
   Serial.println(rata_rata_val);
  Serial.print("suhu = "); 
  Serial.println(suhuAir);
  delay (1000); 




  
}
  
 void ph(){ 
  //menggunakan pin A0 untuk membaca output sensor pH
  for ( int i=0; i<10; i++){
  int value = analogRead(A1 );
  voltage[i] = value * (5.0/1023);
}
   rata_rata_voltage = ( voltage[0] +  voltage[1] +  voltage[2] +  voltage[3] +  voltage[4] +  voltage[5] +  voltage[6] +  voltage[7] +  voltage[8] +  voltage[9])/10 ;
  pHValue = -5.066 * rata_rata_voltage + 32.074 ;
 }

void salinitas() {
  for ( int i=0; i<10; i++){
   val[i] = analogRead(A0);
  rata_rata_val = (val[0] + val[1] + val[2] + val[3] + val[4] + val[5] + val[6] + val[7] + val[8] + val[9])/10 ;
  
}
  teg = rata_rata_val * (5.0/1023);
  sal = 112.93 * teg - 353.84 ; 
    

}
 
void suhu()
{
   sensorSuhu.requestTemperatures();
   suhuAir = sensorSuhu.getTempCByIndex(0);
   return suhu;   
}



  
