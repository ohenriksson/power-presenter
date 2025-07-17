// Board: Arduino Uno
#include <SoftwareSerial.h>

const byte txPin = 13; //yellow
const byte rxPin = 12; //orange

SoftwareSerial stecaSerial (rxPin, txPin);
SoftwareSerial serialMonitor (0 , 1);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  stecaSerial.begin(2400);
  serialMonitor.begin(9600);

  serialMonitor.print("Setup Complete\n");
}

void loop() {
  sendQpigs();
  if (stecaSerial.available() > 0) {
    serialMonitor.print("Serial Available\n");
      stecaSerial.read();
  }else{
    serialMonitor.print("Serial Not Available\n");
  }
  delay(5000);
}


void sendQpigs(){
  serialMonitor.print("Sending QPIGS request\n");
  stecaSerial.print("QPIGS");
  stecaSerial.print("CRC");
  stecaSerial.println();
}
