//Lab 5
//Change iapin to 3 for Lab 4
int iapin=5,opin=13,rvoltg=0;//Input analog pin, Output pin, Raw voltage
float voltg=0,prev=0;//Voltage, Previous voltage

float getV(int rawV){
  // to convert an analogRead() voltage value (which is between 1 and 1024) to an actual float value voltage (from 0.0V to 5.0V)
  return float(rawV)*5.0/1023.0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(opin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  rvoltg=analogRead(iapin);//Obtain raw voltage value
  voltg=getV(rvoltg);//Obtain processed float voltage value
  if(abs(voltg-prev)>0.1){//If the current voltage is 0.1V higher / lower than that recorded last time
    Serial.print(rvoltg);//Print raw analog input value
    Serial.print(" ");//Print a space in between
    Serial.print(voltg);//Print processed value
    Serial.println("V");//Print SI unit
    digitalWrite(opin,(voltg>3.7));//If voltage is higher than 3.7V, turn on the LED. Otherwise, turn off.
    prev=voltg;//Update recorded previous value
  }
}
