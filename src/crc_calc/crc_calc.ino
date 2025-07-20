String QPIGS = "QPIGS";
String stringOne;

//variables for Inverter CRC added
  uint16_t vgCrcCheck;
    char vgHexOne;
      char vgHexTwo;
        int vRequestLen = 0;

void setup() {
  Serial.begin(9600);
    Serial2.begin(2400);
      Serial2.setTimeout(10000);
        vRequestLen = QPIGS.length();
}

void loop() {
  // Shifting QPIGS to Character Array
  char vRequestArray[vRequestLen]; //Arrary define
    QPIGS.toCharArray(vRequestArray, vRequestLen + 1);
  
  //Calculating CRC
  vgCrcCheck = calc_crc(vRequestArray,vRequestLen);

  // CRC returns two characters - these need to be separated and send as HEX to Inverter
    String vgCrcCheckString = String(vgCrcCheck, HEX);
      String vCrcCorrect = vgCrcCheckString.substring(0,2) + " " + vgCrcCheckString.substring(2,4);
        
  //CRC are returned as B7A9 - need to separate them and change from ASCII to HEX
  char s[6];
    vCrcCorrect.toCharArray(s, 6);
      int xx; 
        int yy;
          sscanf(s, "%x %x", &xx, &yy);  
            vgHexOne = xx;
              vgHexTwo = yy;   

  //Sending Request to inverter
  Serial.println("sending QPIGS");
  Serial2.print(QPIGS);
  Serial2.print(vgHexOne); //CRC One
  Serial2.print(vgHexTwo);  //CRC Two
  Serial2.print("\r");
  
  while(Serial2.available()){
    Serial.println (Serial2.read());
  }

  stringOne = Serial2.readStringUntil('\r');
  // stringOne = Serial2.readString();
  Serial.println (stringOne);
  delay(100);
  stringOne = "";
}

// CRC Functions
uint16_t calc_crc(char *msg,int n)
{
// See bottom of this page: http://www.nongnu.org/avr-libc/user-manual/group__util__crc.html
  // Polynomial: x^16 + x^12 + x^5 + 1 (0x1021)
    // Initial value. xmodem uses 0xFFFF but this example
      // requires an initial value of zero.
  uint16_t x = 0;
    while(n--) {
      x = crc_xmodem_update(x, (uint16_t)*msg++);
    }
      return(x);
}
//
uint16_t crc_xmodem_update (uint16_t crc, uint8_t data)
{
  int i;
    crc = crc ^ ((uint16_t)data << 8);
      for (i=0; i<8; i++) {
        if (crc & 0x8000)
          crc = (crc << 1) ^ 0x1021; //(polynomial = 0x1021)
        else
          crc <<= 1;
        }
          return crc;
}