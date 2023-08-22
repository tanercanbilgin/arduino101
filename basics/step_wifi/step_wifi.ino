String NetworkName = "ssid";
String NetworkPassword = "pass";
int motorPin1 = 3, motorPin2 = 4, motorPin3 = 5, motorPin4 = 6;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(115200);
  Serial.println("AT");
  while (!Serial.find("OK")) {
    Serial.println("AT");
  }
  delay(1000);
  Serial.println("AT+RST");
  delay(1000);
  while (!Serial.find("ready"))
    delay(1000);
  Serial.println("AT+CWMODE=1");
  while (!Serial.find("OK"))
    ;
  Serial.println("AT+CWJAP=\"" + NetworkName + "\",\"" + NetworkPassword + "\"");
  while (!Serial.find("OK"))
    ;
  Serial.print("AT+CIFSR\r\n");
  Serial.print(espRead(1000));
  serialCleans(2000);
  Serial.print("AT+CIPMUX=1\r\n");
  serialCleans(2000);
  Serial.print("AT+CIPSERVER=1,80\r\n");
  serialCleans(2000);
}
void loop() {
  if (Serial.available()) {
    if (Serial.find("+IPD,")) {
      delay(200);
      int connectionId = Serial.read() - 48;
      String command = espRead(1000);
      if (command.indexOf("step=forward") != -1) {
        for (int pace = 0; pace < 5; pace++) {
          stepForward(50);
        }
      } else if (command.indexOf("step=backward") != -1) {
        for (int pace = 0; pace < 5; pace++) {
          stepBackward(50);
        }
      }
      String page = "<h1>Step Motor Control</h1><br>";
      page += "<br><a href=\"?step=forward\"><button><h1>forward</h1></button></a>";
      page += "<br><br><a href=\"?step=backward\"><button><h1>backward</h1></button></a>";
      command = "AT+CIPSEND=";
      command += connectionId;
      command += ",";
      command += page.length();
      command += "\r\n";
      Serial.print(command);
      delay(1000);
      Serial.print(page);
      delay(1000);
      command = "AT+CIPCLOSE=";
      command += connectionId;
      command += "\r\n";
      Serial.print(command);
    }
  }
}
String espRead(long int timeOut) {
  long int initial = millis();
  String incoming;
  while (millis() - initial < timeOut) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      incoming += c;
    }
  }
  incoming.replace("AT+", "");
  return incoming;
}
void serialCleans(long int timeOut) {
  long int initial = millis();
  while (millis() - initial < timeOut) {
    if (Serial.available() > 0) {
      Serial.read();
    }
  }
}
void stepForward(int cooldownTime) {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(cooldownTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(cooldownTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(cooldownTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(cooldownTime);
}
void stepBackward(int cooldownTime) {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(cooldownTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(cooldownTime);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(cooldownTime);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(cooldownTime);
}