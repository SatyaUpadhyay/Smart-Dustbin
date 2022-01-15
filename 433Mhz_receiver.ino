#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <WiFi.h>
#include <HTTPClient.h>
int i=0;
const char* ssid = "SETe";
const char* password = "Airtel@9999";
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(2000,4,14,0);
String a;
String Reciever_id="Rc-2345";
void setup()
{
    Serial.begin(9600);  // Debugging only
    SerialBT.begin("Entry Gate");
//  WiFi.begin(ssid, password);
//   Serial.print("Connecting");
//   while (WiFi.status() != WL_CONNECTED) {
// 
//   delay(1000);
//   Serial.print("..");
// 
//  }
  Serial.println("connected");
    if (!driver.init()){
         Serial.println("init failed");
}}

void loop()
{   
  
    uint8_t buf[10];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      
      i=i+1;
      SerialBT.print("Message: ");
      //Serial.println((char*)buf); 
      a= String((char*)buf); 
      SerialBT.println(a);
   
     
      HTTPClient http;
    
     http.begin("http://15.207.162.5:3301/api/v1/addReceiverBike?receiver_id="+Reciever_id+"&bike_no="+a); 
     int httpCode = http.GET();
      if (httpCode > 0) { //Check the returning code
 
     String payload = http.getString();   //Get the request response payload
     Serial.println(payload);}   
         
    
      }}
