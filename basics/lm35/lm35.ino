#define lm35 A0
#define led 8
#define buzzer 9

int lm35_value = 0;
int time = 100;
float temperature_voltage = 0;
float temperature = 0;


void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  lm35_value = analogRead(lm35);
  temperature_voltage = (5000.0/1023.0) * lm35_value;
  temperature = temperature_voltage / 10.0;
  Serial.println(temperature);
  delay(time);

  if(temperature >= 29) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(time);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(time);
    } else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(time);
  }

}
