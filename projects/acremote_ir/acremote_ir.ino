#include <IRremote.hpp>

const int recvPin = 2;
const int irLEDPin = 3;

IRsend irsend;

void setup()
{
    Serial.begin(9600);
    IrReceiver.begin(recvPin, ENABLE_LED_FEEDBACK); // Start the receiver
    pinMode(irLEDPin, OUTPUT);
    digitalWrite(irLEDPin, LOW);
    delay(2000);
}

void readIR()
{
    if (IrReceiver.decode())
    {
        uint32_t convertedRawData = IrReceiver.decodedIRData.decodedRawData;

        Serial.print("Received IR code: ");
        Serial.println(convertedRawData);

        IrReceiver.resume();
    }
}

void sendIR()
{
    irsend.sendNEC(0x6C55CF7B, 32);
    delay(1000);
}

void loop()
{
    readIR();
    sendIR();
}