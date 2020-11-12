#include <ESP8266WiFi.h>
#define BLINK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D1
#define ECHOPIN D2

char auth[]="auth code";
char ssid[]="wifi ssid";
char pass[]="wifi pass";
char email_address[]="";
char email_subjects[]="";
char email_message[]="";


BlynkTimer timer;

void setup()
{
  

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
  
  if(distance <=20)
  {
    Blynk.email(email_address,email_subjects,email_message);
    
  }
  Blynk.virtualWrite(V0, distance);
  delay(1000);                       
}
