int ipin[10]={4,5,6,7,8,9,10,11},icnt=10;
int opin=13;
int stat,pre=0;

int readPins() {
  for(int i=0;i<icnt;i++){
    if(digitalRead(ipin[i])){
      return ipin[i];
    }
  }
  return 0;
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<icnt;i++){
    pinMode(ipin[i],INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  stat=readPins();
  if(stat!=pre){
    digitalWrite(opin,stat>0);
    Serial.println(stat);
    pre=stat;
  }
  delay(20);
}
