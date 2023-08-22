#define ldr A0
#define led 3

int level;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  level = analogRead(ldr);
  Serial.println(level);
  delay(300);

  if (level > 800){
    digitalWrite(led, LOW);
  }

  else if (level < 750) {
    digitalWrite(led, HIGH);
  }
}
