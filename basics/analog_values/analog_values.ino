#define pot A0
#define led 3

long level;
long led_level;

void setup() {
  pinMode(pot, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  level = analogRead(pot);
  led_level = map(level, 0, 1023, 0, 255);
  analogWrite(led, led_level);
}
