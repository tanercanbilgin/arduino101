#define Led 10
#define But 8

int state = 0;


void setup() {
  pinMode(Led, OUTPUT);
  pinMode(But, INPUT);
  Serial.begin(9600);
}

void loop() {
  state = digitalRead(But);
  Serial.println(state);
  delay(500);

  if (state == 1) {
    digitalWrite(Led, HIGH);
  } else {
    digitalWrite(Led, LOW);
  }
}
