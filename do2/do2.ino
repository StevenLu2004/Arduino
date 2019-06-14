// Servo - Version: Latest
#include <Servo.h>
Servo left,right;
/*check your connection of sensor*/
int trigpin=11;
int echopin=12;
long duration;
int cm;
void stup(){
  /*Maybe change this??*/
  left.write(90);
  right.write(90);
}
void righ(){
  /*write your robot's value here*/
  left.write(？);
  right.write(？);
  delay(？);
  stup();
}

int wall(){
  digitalWrite(trigpin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  pinMode(echopin,INPUT);
  duration=pulseIn(echopin,HIGH);
  cm=duration*0.0343/2;
  Serial.println(cm);
  return cm;
}
void setup() {
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  /*same*/
  left.attach(3);
  right.attach(5);
}
int i=0;
void loop() {
  i++;
  if(i>=100){righ();i=0;}
  if(wall()<5){
    i=0;
    left.write(103);
    right.write(83);
    delay(400);
    left.write(85.5);
    right.write(99);
    delay(200);
    righ();
    delay(100);

    if(wall()+wall()<20){
      left.write(103);
      right.write(83);
      delay(400);
      left.write(85.5);
      right.write(99);
      delay(200);
      righ();
      stup();
      delay(100);
      righ();
      delay(100);
      if(wall()+wall()<20){
        left.write(103);
        right.write(83);
        delay(400);
        left.write(85.5);
        right.write(98);
        delay(200);
        /*靠墙的自己去调*/
        righ();
        delay(100);
        left.write(103);
        right.write(83);
        delay(400);
        left.write(85.5);
        right.write(98);
        delay(200);
        righ();
        delay(100);
        righ();
            left.write(83.5);
        right.write(100);

        delay(600);


      }else{left.write(83.5);
        right.write(100);

        delay(600);
      }
    }
  }
  /*write your robot's value here*/
  left.write(70);
  right.write(180);

  delay(20);
}
