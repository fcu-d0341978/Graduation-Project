#include "SoftwareSerial.h"
#include <Servo.h>
#include <IRremote.h>
#include <dht.h>
#define dht_dpin 4 
Servo myservoF;
Servo myservoL;
Servo myservoS;
Servo myservoLR;
SoftwareSerial esp(6, 7);
IRsend irsend;
int pos = 0;
int relayPin = 13;
int i = 0;
dht DHT;

void setup() 
{
  esp.begin(9600);
  Serial.begin(9600);
  myservoF.attach(8);
  myservoS.attach(9);
  myservoL.attach(12);
  myservoLR.attach(11);
  pinMode(relayPin, OUTPUT);
  delay(3000);
}
void loop () 
{
 myservoF.write(0);
 myservoS.write(0);
 myservoL.write(180);
 myservoLR.write(52);


  DHT.read11(dht_dpin); 
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("% ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C ");
  delay(1000);
  if(DHT.humidity>63.00||DHT.temperature>=30.00){
    air();
  }
 if (Serial.available() > 0) {
   i = Serial.read();
   switch(i){
    case '1':
      food();
      break;
    case '2':
      water();
      break;
    case '3':
      toysL();
      break;
    case '4':
      toysR();
      break;
    case '5':
      air();
      break;
    default:
      break;
   }
 }
  
 
String line=readLine();
 statemsgsreach(line);

}

void statemsgsreach(String msg)
{
  int msgint = msg.indexOf("carstate=")+9;
  if(msgint!=8)
    msg = msg.substring(msgint,msgint+1);
  carcontrol(msg);
}
void carcontrol(String meg)
{  
  if(meg.length()==1)
  {
    Serial.println(meg);
    if( meg=="f" )
      food();
    else if( meg=="w" )
      water();  
    else if(meg=="L")
      toysL(); 
    else if(meg=="R")
      toysR();     
    else if(meg=="a")
      air();  
   
  }       
}
String readLine(){
  String lineString="";
  int chartemp = 0;
  while(esp.available())
  {
    char inChar = esp.read();
    lineString=lineString+String(inChar);
    if(inChar=='\n')
    {
        break;
    }
  }
  return lineString;
}
void food()
{
  Serial.println("Food");
  for (pos = 0; pos <= 75; pos += 1){ 
    myservoF.write(pos);   //使用write，傳入角度，從0度到180度
    delay(30);          
  }
  delay(500);
  for (pos = 0; pos <= 75; pos += 1){ 
    myservoF.write(pos);   //使用write，傳入角度，從0度到180度
    delay(30);          
  }
  delay(500);   
 
}
void water()
{
  Serial.println("Water");
  digitalWrite(relayPin, HIGH);
  delay(1000);
  digitalWrite(relayPin, LOW);
  delay(500);
  digitalWrite(relayPin, HIGH);
  delay(1000);
  digitalWrite(relayPin, LOW);
  delay(500);
 
}
void toysL()
{
  
  Serial.println("ToysL");

  myservoLR.write(85);
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
  delay(500);
  
  
}
void toysR()
{
  
  Serial.println("ToysR");

  myservoLR.write(52);
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
  delay(500);
  
  
}
void air()
{
  Serial.println("Air");
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  unsigned int irSignal[] = {3350,3350, 450,1250, 450,400, 450,1250, 450,1250, 450,400, 450,400, 450,1250, 450,400, 450,1250, 450,400, 450,1250, 400,450, 450,1250, 400,1300, 400,1250, 450,400, 450,400, 450,1250, 450,400, 450,400, 450,1250, 450,1250, 450,400, 450,1250, 450,400, 450,1250, 450,400, 450,1250, 450,400, 450,400, 450,400, 450,1250, 450,1250, 450,1250, 450,1200, 450,1250, 450,400, 450,400, 450,400, 450,450, 450,400, 450,1250, 400,1250, 450,450, 400,450, 400,1250, 450,450, 400,450, 450,1200, 450,1250, 450,1250, 450,400, 450,400, 450,1250, 450,400, 450,400, 450,400, 450,400, 450,400, 450,450, 400,450, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,450, 400,400, 450,400, 450,400, 450,400, 450,400, 450,450, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,400, 450,450, 400,450, 400,450, 400,450, 400,1300, 400,450, 400,450, 450,400, 450,400, 450,1250, 450,400, 450,400, 450,1250, 450,1200, 450,450, 400,450, 400,450, 450}; //AnalysIR Batch Export (IRremote) - RAW
  
  irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); //Note the approach used to automatically calculate the size of the array.

  delay(1000);
  
}
