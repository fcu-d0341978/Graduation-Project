#define BLYNK_PRINT Serial
#include <Servo.h>
#include <DHT.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>
int relayPin = 13;
const char auth[] = "1c0025e3cc71417b86f35d97d35d822a";
const char ssid[] = "AndroidAPE05F";
const char pass[] = "12345678";
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial EspSerial(6, 7);
ESP8266 wifi(&EspSerial);
int pos = 0;
BlynkTimer timer;
Servo myservoD;
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
  EspSerial.begin(9600);
  
  pinMode(relayPin, OUTPUT);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
//  Blynk.begin(auth);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}
BLYNK_WRITE(V11) 
{
  myservoLR.attach(11);   // Attach Servo
  int SrvoPos = param.asInt();  // Get slider value
  myservoLR.write(SrvoPos);  // Move servo to value
  delay(500);  // Set minimum delay for servo to reach desired position, keep as low as possible.
  myservoLR.detach();   // Detach Servo - NOTE servo pin designation not required for detach
  /*myservoLR.attach(11);
  int SrvoPos = param.asInt(); // get slider value
  myservoLR.write(SrvoPos); // move servo to value
  myservoLR.detach();*/
}
BLYNK_WRITE(V8) 
{
  int buttonValF = param.asInt(); 
  myservoF.attach(8);
if(buttonValF == 1) {
for (pos = 0; pos <= 60; pos += 1){ 
    myservoF.write(pos);  
    delay(15);         
  }
 myservoF.write(0);
  delay(5000);
  
}
myservoF.detach();
}
BLYNK_WRITE(V9) 
{
  int buttonValT = param.asInt(); 
  
  
if(buttonValT == 1) {
 
   myservoS.attach(9);
    myservoL.attach(12);
   myservoS.write(0);
   myservoL.write(180);
  delay(100);
  for (pos = 0; pos <= 180; pos += 1){ 
    myservoS.write(pos);   //使用write，傳入角度，從0度到180度
    delay(20);          
  }
  myservoL.write(90);
  delay(500); 
  
  for (pos = 180; pos >= 10; pos -= 1){ 
    myservoS.write(pos);   //使用write，傳入角度，從0度到180度
    delay(20);          
  } 
  myservoS.detach();
  myservoL.detach();
   myservoLR.attach(11);
  myservoLR.write(95);
  delay(500);
  myservoLR.detach();
   myservoD.attach(10);  
delay(20);   
myservoD.write(17);
delay(335);
myservoD.write(5);
delay(500);
myservoD.detach();
}

 


}
BLYNK_WRITE(V13) 
{
  int buttonValS = param.asInt(); 
if(buttonValS == 1) {

 digitalWrite(relayPin, HIGH);
 delay(1000);
 digitalWrite(relayPin, LOW);
 delay(500);
}
}
void loop()
{
  
 myservoF.write(0);
 myservoS.write(0);
 myservoL.write(180);
 myservoLR.write(0);
 myservoD.write(0);
  Blynk.run();
  timer.run();
}


