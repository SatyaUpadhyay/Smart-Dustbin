 
#include <SPI.h>
#include <LoRa.h>




void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
    
    

 
}
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    //Serial.println("Received packet:");
     String a = "";
    // read packet
    while (LoRa.available()) {
     a  += (char)LoRa.read();

     
    
    delay(100);
    }
    Serial.println(a); 
  // Serial.println(LoRa.packetRssi());
    
  
  } 
    //lcd.print((LoRa.packetRssi()));
    //delay(1000);
   
  
}
