#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif
RH_ASK driver(2000,4,2,0);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,INPUT);
if (!driver.init())
         Serial.println("init failed");
  
}

void loop() {
  // put your main code here, to run repeatedly:
const char *msg = "ON";
const char *msg1 = "OF";
if (analogRead(A0)>=900){
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
    Serial.println("on");}
else{
  driver.send((uint8_t *)msg1, strlen(msg1));
    driver.waitPacketSent();
    delay(1000);
    Serial.println("off");}
    
    
}
