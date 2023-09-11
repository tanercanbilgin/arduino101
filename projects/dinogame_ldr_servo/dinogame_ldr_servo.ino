#include <Servo.h>

#define ldrPin A0
#define servoPin 3

int releaseAngle = 90;
int pressAngle = 0;
int threshold = 650;
int ldrData;

Servo motor;

void getData()
{
    ldrData = analogRead(ldrPin);
    Serial.println(ldrData);
}

void moveServo()
{
    if (ldrData > threshold)
    {
        motor.write(pressAngle);
        motor.write(releaseAngle);
    }
}

void setup()
{
    Serial.begin(9600);
    motor.attach(servoPin);
    motor.write(releaseAngle);
}

void loop()
{
    getData();
    moveServo();
}
