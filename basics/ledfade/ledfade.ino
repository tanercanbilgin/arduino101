int brightness = 0;
int ledPin = 10;

void setup()
{
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    for (brightness = 0; brightness <= 255; brightness += 5)
    {
        analogWrite(ledPin, brightness);
        delay(50);
    }
    for (brightness = 255; brightness >= 0; brightness -= 5)
    {
        analogWrite(ledPin, brightness);
        delay(50);
    }
}