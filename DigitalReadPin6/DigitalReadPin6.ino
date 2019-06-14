int ledPin=13;//LED pin
int readPin=6;//Pin of digital input
int pre=LOW;//Previous state on input pin

void setup() {
  // put your setup code here, to run once:
  //Set input & output pin
  pinMode(ledPin,OUTPUT);
  pinMode(readPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int cur=digitalRead(readPin);//Obtain current state on input pin
  if(cur!=pre)//If there is a change
  {
    digitalWrite(ledPin,cur);//Change with the change
    pre=cur;//Update recorded value
  }
}
