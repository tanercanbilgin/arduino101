#include <SPI.h>
#include <RFID.h>

RFID rfid(10,9);

void setup() {
  SPI.begin();
  rfid.init();
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

byte kartim[5] = {0x53,0x88,0xB2,0x34,0x5D}; 
void loop() {
  boolean gecerlikart = true;
  if(rfid.isCard())
  {
    if(rfid.readCardSerial())
    {
      Serial.print("Kart ID: ");
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.println(rfid.serNum[4],HEX);
    }
    for(int i=0; i<5; i++)
    {
      if(rfid.serNum[i] != kartim[i])
      {
        gecerlikart = false;
      }
    }
    if(gecerlikart==true)
    {
      digitalWrite(2, HIGH);
      delay(2000);
      digitalWrite(2, LOW);
    }
    else
    {
      digitalWrite(3, HIGH);
      delay(2000);
      digitalWrite(3, LOW);
    }
    rfid.halt();
  }
}