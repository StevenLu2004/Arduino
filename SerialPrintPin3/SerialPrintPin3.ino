int ipin=3,opin=13;//Define input / output pins
int stat=LOW,pre=LOW;//Define status and previous status

void setup() {
  // put your setup code here, to run once:
  pinMode(ipin,INPUT);//Set input pin
  pinMode(opin,OUTPUT);//Set output pin
  Serial.begin(9600);//Connect the serial port with speed 9600
}

void loop() {
  // put your main code here, to run repeatedly:
  stat=digitalRead(ipin);//Read current status on input pin
  if(pre!=stat){//If the status has changed
    pre=stat;//Update recorded status
    digitalWrite(opin,pre);//Turn on / off LED according to the current status on input pin
    Serial.println(pre);//Print status in serial
  }
}
