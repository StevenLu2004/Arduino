int opin=13;//Output pin: 13 (LED)

void setup() {
  // put your setup code here, to run once:
  pinMode(opin,OUTPUT);//Set pin 13 (LED) to output
  randomSeed(analogRead(0));//As analog read is never very accurate, I can actually use the readings from a disconnected analog pin as random seed
  Serial.begin(9600);//Connect serial, speed=9600
}

void loop() {
  // put your main code here, to run repeatedly:
  //Randomly wait 1.000 to 2.999 sec (inclusive)
  int tme=random(5000,15000);
  delay(tme);
  //Clean up serial buffer before signaling the player, to prevent cheating.
  while(Serial.available()>0){
    Serial.read();
  }
  //Turn on LED to signal the start of the game
  digitalWrite(opin,HIGH);
  //Time the response
  unsigned long t=millis();
  while(Serial.available()<=0){
    continue;
  }
  //As soon as receives data, stop timing and immediately send time
  Serial.print(float(millis()-t)/1000.0);
  //Then turn off LED
  digitalWrite(opin,LOW);
  //Then "complete the sentence\n"
  Serial.print(" seconds");
  Serial.println();
}
