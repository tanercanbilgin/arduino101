int green = 9;
int red = 10;

void setup()
{
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'G')
    {
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
    }
    else if (c == 'R')
    {
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
    }
  }
}