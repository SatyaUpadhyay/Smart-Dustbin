 #include "WiFi.h"
#include <HardwareSerial.h>
#include <HTTPClient.h>
#include <WiFi.h>

const int trigPin = 22;
const int echoPin = 23;
int count = 0;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
int suk2, suk3, len, rcvLen;
long duration;
float distanceCm;
float distanceInch;
String datainc, webdata = "", DeviceID = "", receivedChar, num, data, recivedData, EEPread;
float quant, depth;
int LEDwifi = 19, LEDgsm = 21;
const char* ssid = "Satya";
const char* password =  "Airtel@9999";
int i = 0;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  //WiFi.begin(ssid, password);
  DeviceID = WiFi.macAddress();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    i = i + 1;
    Serial.println(i);
    delay(1000);
    if (i >= 5) {
      break;
    }
  }
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(LEDwifi, OUTPUT);
  pinMode(LEDgsm, OUTPUT);
  digitalWrite(LEDwifi, LOW);
  digitalWrite(LEDgsm, LOW);
  //EEP();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    //Serial.println(depth);
    Serial2.begin(9600);
    GSMconnection();
  }
  else {
    HTTPClient http;
    digitalWrite(LEDgsm, LOW);
    digitalWrite(LEDwifi, HIGH);
    //Serial.println(EEPread);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculate the distance
    distanceCm = duration * SOUND_SPEED / 2;
    // Convert to inches
    distanceInch = distanceCm * CM_TO_INCH;
    //depth = distanceInch.toFloat();
    Serial.println(quant);
    //http.begin("http://15.207.162.5:3301/api/v1/requests?bykemobile=7428445885&bykelat="+a+"&bykelong="+o+"&byketime="+sp+"&bykedate="+ac+"&rfd="+rfd+"&volt="+String(volt)+"&rly="+rly+"");// setting);
    http.begin("http://sukarn.ml:3000/postdata?deviceid=" + String(DeviceID) + "&data=" + String(distanceInch)); // setting);
    //if (http.GET() == 200);
    Serial.println(http.GET());
  }
}

void GSMconnection()
{
  Serial2.begin(9600);
  digitalWrite(LEDwifi, LOW);
  digitalWrite(LEDgsm, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  //depth=1200;
  quant = depth - distanceInch;
  Serial.println(quant);
  Serial2.begin(9600);
Serial2.println("AT+CSQ"); // Signal quality check

  delay(100);
 
  ShowSerialData();
  // this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
 
 Serial2.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(100);
 
  ShowSerialData();
  
 Serial2.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();
 
 
 Serial2.println("AT+SAPBR=3,1,\"APN\",\"du\"");//setting the APN, Access point name string
  delay(2000);
 
  ShowSerialData();
  
 
 Serial2.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(1000);
 
  ShowSerialData();
  
  Serial2.println("AT+SAPBR=2,1");//setting the SAPBR
  delay(500);
 
  ShowSerialData();
  
 
 Serial2.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2500);
  ShowSerialData();
  
 Serial2.println("AT+HTTPPARA=\"URL\",\"http://sukarn.ml:3000/postdata?deviceid="+String(DeviceID)+"&data="+String(quant)+"\""); delay(1700);
 
  ShowSerialData();
  
 
 Serial2.println("AT+HTTPACTION=0");//submit the request
  delay(7000);
 
  ShowSerialData();

 
 Serial2.println("AT+HTTPREAD");// read the data from the website you access
 delay(300);
 relayaction();
 ShowSerialData();

 Serial2.println("AT+HTTPTERM");
 delay(1100);
 Serial2.println("");
  delay(2000);
   ESP.restart();
}
void relayaction()
{
  String webdata ="";
 while(Serial2.available())// String RelayState = webdata.substring();
 {  
   
    webdata = webdata + String(char(Serial2.read()));
    Serial.println(webdata);
 }

  }
void ShowSerialData()
{
  while (Serial2.available() != 0)
    Serial.write(Serial2.read());
}
