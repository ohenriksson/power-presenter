// Board: Arduino Uno
#include <SoftwareSerial.h>

SoftwareSerial stecaSerial (10, 11, false);

void setup() {
 
  Serial.begin(9600);
  stecaSerial.begin(9600);

  Serial.print("Setup Complete\n");
}

void loop() {
  Serial.print("--Available?");
  Serial.println(stecaSerial.available());
  if(stecaSerial.available()) //idle
  {
    Serial.println("--Yes!");
    Serial.println("steca available");
    int ready = stecaSerial.read();
    Serial.println(ready, HEX );
    //SEND DATA HERE
    sendQpigs();
  
    while(!stecaSerial.available()){
      Serial.println("waiting for steca...");
      delay(1000);
    }
    while(stecaSerial.peek() != -1){
      String result = stecaSerial.readString();
      Serial.print(result);
    }
  }else{
    Serial.println("--No..");
  }

  Serial.println();
  delay(1000);
}


void sendQpigs(){
  Serial.print("Sending QPIGS request\n");
  stecaSerial.print("QPIGS");
  stecaSerial.print("CRC");
  stecaSerial.println();
}
