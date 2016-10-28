int IN1=8; //Connect on Arduino, Pin 8
int IN2=9; //Connect on Arduino, Pin 9
int IN3=10; //Connect on Arduino, Pin 10
int IN4=11; //Connect on Arduino, Pin 11
int servoPin = 5; //Connect on Arduino, servo motor pin num 5

int txPin = 13;
int rxPin = 12;
#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;
SoftwareSerial ultraSonicSensor(rxPin, txPin); // RX, TX
int pos = 0;

String inString = "";
const int numberOfPieces = 4;
String pieces[numberOfPieces];
int counter = 0;
int lastIndex = 0;

void step1(){
  digitalWrite(IN1,HIGH);
     digitalWrite(IN2,HIGH);  
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,LOW);
     delay(2);
}

void step2(){
  digitalWrite(IN1,LOW);
     digitalWrite(IN2,HIGH);  
     digitalWrite(IN3,HIGH);
     digitalWrite(IN4,LOW);
     delay(2);
}

void step3(){
  digitalWrite(IN1,LOW);
     digitalWrite(IN2,LOW);  
     digitalWrite(IN3,HIGH);
     digitalWrite(IN4,HIGH);
     delay(2);
}

void step4(){
  digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);  
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,HIGH);
     delay(2);
}
void step5(){
  digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);  
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,HIGH);
     delay(2);
}
void step6(){
  digitalWrite(IN1,LOW);
     digitalWrite(IN2,LOW);  
     digitalWrite(IN3,HIGH);
     digitalWrite(IN4,HIGH);
     delay(2);
}
void step7(){
  digitalWrite(IN1,LOW);
     digitalWrite(IN2,LOW);  
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,HIGH);
     delay(2);
}

void step8(){
  digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);  
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,HIGH);
     delay(2);
}

void sleep(){
  digitalWrite(IN1,LOW);
     digitalWrite(IN2,LOW);  
     digitalWrite(IN3,LOW);
     digitalWrite(IN4,LOW);
     delay(2);
}

void clockwiserotate()
{
     step1();
     step2();
     step3();
     step4();
}

void counterclockwiserotate()
{
     step1();
     step4();
     step3();
     step2();
}

void setup() {
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 servo.attach(servoPin);
 Serial.begin(38400);
 ultraSonicSensor.begin(38400);
 
}

void loop(){
  if (ultraSonicSensor.available()) {
    Serial.write(ultraSonicSensor.read());
  }
  if (Serial.available()) {
    ultraSonicSensor.write(Serial.read());
  }

}
