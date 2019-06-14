int ledPin=13;//Output pin: 13 (LED)

void morseS() {
  // short morse code
  digitalWrite(ledPin,HIGH);
  delay(150);
  digitalWrite(ledPin,LOW);
  delay(100);
}

void morseL() {
  // long morse code
  digitalWrite(ledPin,HIGH);
  delay(400);
  digitalWrite(ledPin,LOW);
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //S=***
  morseS();
  morseS();
  morseS();
  //O= - - -
  morseL();
  morseL();
  morseL();
  //S=***
  morseS();
  morseS();
  morseS();
  delay(1000);
}
