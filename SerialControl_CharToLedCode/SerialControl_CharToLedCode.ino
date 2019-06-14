int opin=13;//Output pin: 13 (LED)
byte clist[5]={'a','b','c','d','e'};//The byte data to compare with
int tlist[5]={100,300,700,1500,3100};//The corresponding time (in mm) to blink
int ltot=5;//The total number of registered byte signals

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//Set serial data transfer speed
  pinMode(opin,OUTPUT);//Set pin 13 (LED) to output pin
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){//If there is serial input in the buffer
    byte a=Serial.read();//Read a byte
    for(int i=0;i<ltot;i++){//Check all registered byte signals
      if(a==clist[i]){//If input matches the byte signal
        digitalWrite(opin,HIGH);//Turn on LED
        delay(tlist[i]);//Wait the time corresponding to the byte signal
        digitalWrite(opin,LOW);//Turn off LED
        delay(100);//Wait 0.1 seconds
        break;//End loop, procede with next check
      }
    }
  }
}
