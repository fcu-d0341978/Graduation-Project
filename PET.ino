#define BLYNK_PRINT Serial
#define dht_dpin 4 
#include <Servo.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>
int relayPin = 13;
char auth[] = "1c0025e3cc71417b86f35d97d35d822a";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
#define EspSerial Serial1
//#include <SoftwareSerial.h>
#define ESP8266_BAUD 3600
ESP8266 wifi(&EspSerial);     
#define dht_dpin 4 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
Servo myservoF;
Servo myservoL;
Servo myservoS;
Servo myservoLR;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  myservoF.attach(8);
  myservoS.attach(9);
  myservoL.attach(12);
  myservoLR.attach(11);
  pinMode(relayPin, OUTPUT);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}
BLYNK_WRITE(V11) 
{
  int SrvoPos = param.asInt(); // get slider value
  myservoLR.write(SrvoPos); // move servo to value
}
void loop()
{
  Blynk.run();
  timer.run();
}


