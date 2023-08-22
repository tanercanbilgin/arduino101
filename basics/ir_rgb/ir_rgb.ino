#define recvPin 2
#define red 9
#define green 10
#define blue 11

#include <IRremote.hpp>

#define BUTTON1 0xBA45FF00
#define BUTTON2 0xB946FF00
#define BUTTON3 0xB847FF00
#define BUTTON4 0xBB44FF00
#define BUTTON5 0xBF40FF00
#define BUTTON6 0xBC43FF00
#define BUTTON7 0xF807FF00
#define BUTTON8 0xEA15FF00
#define BUTTON9 0xF609FF00
#define ASTERISK 0xE916FF00
#define BUTTON0 0xE619FF00
#define HASHKEY 0xF20DFF00
#define UPARROW 0xE718FF00
#define LEFTARROW 0xF708FF00
#define OKBUTTON 0xE31CFF00
#define RIGHTARROW 0xA55AFF00
#define DOWNARROW 0xAD52FF00

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
  IrReceiver.begin(recvPin, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t convertedRawData = IrReceiver.decodedIRData.decodedRawData;
    
    if (convertedRawData == BUTTON1) {
      toggleLed(red);
    } else if (convertedRawData == BUTTON2) {
      toggleLed(green);
    } else if (convertedRawData == BUTTON3) {
      toggleLed(blue);
    } else if (convertedRawData == ASTERISK) {
      turnOffAllLeds();
      Serial.println("All LED's OFF");
    } else if (convertedRawData == HASHKEY) {
      turnOnAllLeds();
      Serial.println("All LED's ON");
    }

    IrReceiver.resume(); // Enable receiving of the next value
  }
}

void toggleLed(const char* ledName) {
  digitalWrite(ledName, !digitalRead(ledName));
  if (digitalRead(ledName) == HIGH) {
    Serial.println(" ON");
  } else {
    Serial.println(" OFF");
  }
}

void turnOffAllLeds() {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}

void turnOnAllLeds() {
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
}


