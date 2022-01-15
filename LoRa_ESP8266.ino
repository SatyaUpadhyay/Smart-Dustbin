#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<SoftwareSerial.h>
SoftwareSerial LoRaRecv(13,5);
/* Set these to your desired credentials. */
const char *ssid = "SETech_airtel";  //ENTER YOUR WIFI SETTINGS
const char *password = "Airtel@9999";
String incoming="",incom="";
//char incom;
void setup() {
 //delay(1000);
  Serial.begin(9600);
  LoRaRecv.begin(9600);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {  
 
 WiFiClient Client;


  if(LoRaRecv.available()){
    incom= LoRaRecv.readString();
    //incom=""; 
     
  
  Serial.print(incom);

       incoming=String(incom);      
      
         //Declare object of class HTTPClient   
  HTTPClient http; 
  http.begin(Client,"http://65.0.176.24:3000/postdata?deviceid=" + String("LOR0001") + "&data=" + String(incom));              //Specify request destination
  //http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 // incom="";
  http.GET();   //Send the request
  }
}
