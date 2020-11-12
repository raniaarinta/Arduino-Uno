#include <ESP8266WiFi.h>
#define BLINK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D1
#define ECHOPIN D2
int led1=13,led2=12,led3=14;
char auth[]="auth code";
char ssid[]="wifi ssid";
char pass[]="wifi pass";



BlynkTimer timer;

void setup()
{ 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3003L, sendSensor);

}
void loop()
{
 Blynk.run();
 timer.run();
  
}

void sendSensor()
{
  digitalWrite(TRIGGERPIN, LOW);   
  delayMicroseconds(3);       

  digitalWrite(TRIGGERPIN, HIGH);  
  delayMicroseconds(12);      
  digitalWrite(TRIGGERPIN, LOW);
  
  long duration,distance;   

  duration = pulseIn(ECHOPIN, HIGH);   
  distance = duration * 0.034 / 2;   

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);
  
  if(distance <=5)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  else if(distance < 10 && distance < 20)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
   else if(distance >40)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  Blynk.virtualWrite(V0, distance);
  delay(1000);                       
}
