#include <Servo.h>

Servo motor;

int value;
int degree;

void setup() {
  motor.attach(3);

}

void loop() {

  value = analogRead(A0);
  degree = map(value, 0,1023,0,180);
  motor.write(degree);

}