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
  /*
  if (ultraSonicSensor.available()) {
    Serial.write(ultraSonicSensor.read());
  }
  if (Serial.available()) {
    ultraSonicSensor.write(Serial.read());
  }
  */

/*
  //separate mode
  if (Serial.available())
  {
    int modeChar = Serial.read();

    //set mode
    if(modeChar==0){
      
    }
  }
*/

   while (Serial.available() > 0) {
    int inChar = Serial.read();
    inString += (char)inChar;
    
    if (inChar == '\n') {      
      for (int i = 0; i < inString.length(); i++) {
        if (inString.substring(i, i+1) == ",") {
          pieces[counter] = inString.substring(lastIndex, i);
          lastIndex = i + 1;
          counter++;
        }

        if (i == inString.length() - 1) {
          pieces[counter] = inString.substring(lastIndex);
        }
      }
      counter = 0;
      lastIndex = 0;

      //set step
      if(pieces[0].toInt()){
          for (int i=0;i<pieces[1].toInt();i++){
          clockwiserotate();
        }
      }
      else{
        for (int i=0;i<pieces[1].toInt();i++){
          counterclockwiserotate();
        }
      }

      //set servo
      servo.write(pieces[2].toInt());

      //get dist from ultra sonic sensor
      for(int i=0;i<pieces[4].toInt();i++){
        ultraSonicSensor.print(pieces[3]);
        delay(1);
        String tempStr = "";
        unsigned long time = millis();
        
        while(true){
          int tempChar;
          if(ultraSonicSensor.available())
          {
            tempChar = ultraSonicSensor.read();
          tempStr += (char)tempChar;
          /*
          if(tempChar==3){
            break;
          }
          */
          }
          if((millis()-time)>100){
            break;
          }
        }
        Serial.println(tempStr);
      }
      //Serial.println("#EOM");
      inString = "";
    }
   }
  
  /*
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for(int i=0;i<100;i++){
    clockwiserotate();
  }
  //clockwiserotate();
  delay(100);
  */
}