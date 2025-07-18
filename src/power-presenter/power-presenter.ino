// Board: Arduino Uno
#include <SoftwareSerial.h>

// SoftwareSerial Serial1 (10, 11, false);

String QPIGS = "\x51\x50\x49\x47\x53\xB7\xB7\xA9\x0D"; //
String resultString;

void setup() {
  Serial.begin(9600);

  Serial1.begin(2400, SERIAL_8N1);
  Serial1.setTimeout(10); //wait for serial to begin
  Serial.println("Setup Complete\n");
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
  delay(5000);
}

void startTalking(){
  Serial.print("bytes in buffer");
  Serial.println(Serial1.available());

  sendQpigs();
  delay(50);
  resultString = Serial1.readStringUntil('\r');
  Serial.print(resultString);
  delay(100);
}

void sendQpigs(){
  Serial.print("Sending QPIGS \n");
  Serial1.println("QPIGS");
  // Serial1.println(QPIGS);
  // Serial1.print("CRC");
  // Serial1.println();
}

void sendQPI(){
  Serial.print("Sending QPI CRC \n");
  Serial1.print("QPI");
  // Serial1.print("CRC");
  Serial1.println();
}



