// Board: Arduino Uno
#include <SoftwareSerial.h>

// SoftwareSerial Serial1 (10, 11, false);

void setup() {
 
  Serial.begin(9600);

  Serial1.begin(2400);
  Serial.print("Setup Complete\n");
}

void loop() {
  Serial.print("--Available?");
  if(Serial1.available()) //idle
  {
    Serial.println("--Yes!");
    startTalking();
    
  }else{
    Serial.println("--No...");
  }

  Serial.println();
  delay(1000);
}

void startTalking(){
  Serial.println(Serial1.peek());
  Serial1.write(123);
  // int ready = Serial1.readBytes();
  // Serial.println(ready, HEX );
  sendQpigs();
  
    int timeout = 10;
    while(!Serial1.available() && timeout > 0){
      Serial.println("waiting for steca...");
      delay(1000);
      timeout--;
    }
    while(Serial1.peek() != -1 && timeout > 0){
      String result = Serial1.readString();
      Serial.print(result);
    }
}

void sendQpigs(){
  Serial.print("Sending QPIGS request\n");
  Serial1.print("QPIGS");
  Serial1.print("CRC");
  Serial1.println();
}
