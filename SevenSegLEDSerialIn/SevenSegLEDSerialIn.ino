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

void LEDout(int val,int aln){
  for(int i=0;i<8;i++){
    digitalWrite(Aligner[i+aln],(PCode[val]>>i)&1);
  }
}

int curId=0,pre=0;
void setup() {
  Serial.println("Setup begin");
  // put your setup code here, to run once:
  for(int i=2;i<18;i++){
    pinMode(Aligner[2],OUTPUT);
  }
  Serial.begin(9600);
  LEDout(curId,10);
  Serial.println("Setup success");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    byte msg=Serial.read();
    if(!(msg<='9' && msg>='0')){return;}
    curId=msg-'0';
    if(curId==pre){return;}
    LEDout(curId,10);
    Serial.println(curId);
    pre=curId;
  }
}
