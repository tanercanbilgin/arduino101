#include <SPI.h>
#include <RFID.h>

int pirPin = 8;
int buzzerPin = 7;

RFID rfid(10,9);

byte card[5] = {0x53,0x88,0xB2,0x34,0x5D};
boolean cardStatus = false;
boolean pirTriggered = false;
boolean state = false;
int status;

void readCard() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      for (int i = 0; i < 5; i++) {
        if (rfid.serNum[i] == card[i]) {
          cardStatus = true;
          if (i == 4)
          Serial.println("Doğru Kart");
        } else {
          if (i == 4)
          Serial.println("Yanlış Kart");
        }
      }
    }
    rfid.halt();
  }
}

void checkPir() {
  status = digitalRead(pirPin);
  if(status == HIGH) {
    pirTriggered = true;
    Serial.println("Hareket Algılandı");
  } else {
    pirTriggered = false;
  }
}

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  if (cardStatus == false) {
  delay(3000);
  checkPir();
  delay(1000);
  readCard();
  }
  if (pirTriggered == true && cardStatus == false){
    tone(buzzerPin, 440);
    }
  else{
    noTone(buzzerPin);
  }
}