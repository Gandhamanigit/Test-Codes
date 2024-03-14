#include<Arduino.h>
int msensor = 1;// moisture sensor is connected with the analog pin A1 of the Arduino
int msvalue = 0; // moisture sensor value 
int led = 13; 
boolean flag = false; 
void setup() {
  Serial.begin(9600);
  pinMode(msensor, INPUT);
  pinMode(led, OUTPUT);  
}

void loop() {
  msvalue = analogRead(msensor);
  Serial.println(msvalue);
  
  if ( (msvalue >= 500  ) && ( flag == false ) )
{
  digitalWrite(led, HIGH); 
  flag = true; 
  delay(1000); 
}

  if ( (msvalue <= 300  ) && ( flag == true ) )
{
  digitalWrite(led, LOW); 
  flag = false; 
  delay(1000); 
}

  delay(1000);      
}