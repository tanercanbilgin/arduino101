#include <SoftwareSerial.h>
#include <DHT11.h>

String WifiName = "ssid";
String password = "pass";

int rxPin = 10;
int txPin = 11;
int dht11Pin = 2;

String ip = "184.106.153.149";
float Temperature, Humidity;

DHT11 dht11(dht11Pin);

SoftwareSerial esp(rxPin, txPin);
void setup() {  
  
  Serial.begin(9600);
  Serial.println("Started");
  esp.begin(115200);
  esp.println("AT");
  while(!esp.find("OK")){
    esp.println("AT");
    Serial.println("No ESP8266 Found.");
  }
  
  esp.println("AT+CWMODE=1");
  while(!esp.find("OK")){
    esp.println("AT+CWMODE=1");
    
  }
  Serial.println("Connecting Wifi...");
  esp.println("AT+CWJAP=\""+WifiName+"\",\""+password+"\"");
  while(!esp.find("OK"));
  Serial.println("Connected Wifi.");
  delay(1000);
}
void loop() {
  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");
  if(esp.find("Error")){
    Serial.println("AT+CIPSTART Error");
  }
  Temperature = (float)dht11.readTemperature();
  Humidity = (float)dht11.readHumidity();
  String data = "GET https://api.thingspeak.com/update?api_key=MYAPIKEY";                               
  data += "&field1=";
  data += String(Temperature);
  data += "&field2=";
  data += String(Humidity);
  data += "\r\n\r\n"; 
  esp.print("AT+CIPSEND=");
  esp.println(data.length()+2);
  delay(2000);
  if(esp.find(">")){
    esp.print(data);
    Serial.println(data);
    Serial.println("Data Sent.");
    delay(1000);
  }
  Serial.println("Connection closed.");
  esp.println("AT+CIPCLOSE");
  delay(1000);
}