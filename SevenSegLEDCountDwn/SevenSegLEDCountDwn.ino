byte PDEC=0x1,PRDW=0x2,PDWN=0x4,PLDW=0x8,PRUP=0x10,PTOP=0x20,PLUP=0x40,PMID=0x80;
byte PCode[16]={
  PRDW|PDWN|PLDW|PRUP|PTOP|PLUP,
  PRDW|PRUP,
  PDWN|PLDW|PRUP|PTOP|PMID,
  PRDW|PDWN|PRUP|PTOP|PMID,
  PRDW|PRUP|PLUP|PMID,
  PRDW|PDWN|PTOP|PLUP|PMID,
  PRDW|PDWN|PLDW|PTOP|PLUP|PMID,
  PRDW|PRUP|PTOP,
  PRDW|PDWN|PLDW|PRUP|PTOP|PLUP|PMID,
  PRDW|PDWN|PRUP|PTOP|PLUP|PMID,
  PRDW|PLDW|PRUP|PTOP|PLUP|PMID,
  PRDW|PDWN|PLDW|PLUP|PMID,
  PDWN|PLDW|PTOP|PLUP,
  PRDW|PDWN|PLDW|PRUP|PMID,
  PDWN|PLDW|PTOP|PLUP|PMID,
  PLDW|PTOP|PLUP|PMID
};

int Aligner[25]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A4,A5};

/*
int pstat[25];
int ppos=0,ppre=0,ptot=26;

void rotateFire(){
  if(pstat[ppos]==HIGH){
    digitalWrite(Aligner[ppre],LOW);
    digitalWrite(Aligner[ppos],HIGH);
    ppre=ppos;
  }
  ppos++;
}
*/

void LEDout(int val,int aln,bool fdec=false){
  byte tmpcode=PCode[val]|fdec;
  for(int i=0;i<8;i++){
    digitalWrite(Aligner[i+aln],(tmpcode>>i)&1);
  }
}

int t=0,slen=0;
long tme,disp=0;
char inc,s[105];
int timerOn=0;

void sread(){
  if(Serial.available()<=0){return;}
  inc=Serial.read();
  if(inc==10){
    for(int i=0;i<slen;i++){
      t=t*10+s[i]-'0';
    }
    Serial.println(s);
    slen=0;
    s[slen]='\0';
    timerOn=1;
    Serial.println(t);
    return;
  }
  s[slen++]=inc;
  s[slen]='\0';
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setup begin");
  // put your setup code here, to run once:
  for(int i=2;i<18;i++){
    pinMode(Aligner[i],OUTPUT);
  }
  LEDout(0,2,true);
  LEDout(0,10);
  Serial.println("Setup success");
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(timerOn){
    case 0:
      sread();
      break;
    case 1:
      tme=millis()+t;
      timerOn=2;
      break;
    case 2:
      if(disp!=tme-millis()){
        disp=tme-millis();
        if(disp<=0){
          disp=0;
          timerOn=3;
        }
        LEDout(disp/1000,2,true);
        LEDout((disp/100)%10,10);
      }
      break;
    case 3:
      Serial.println("Time's up!");
      t=0;
      timerOn=0;
      break;
  }
}
