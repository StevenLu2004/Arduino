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

int shiftC=2;

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<8;i++){
    pinMode(i+shiftC,OUTPUT);
  }
}

void LEDout(int val,int shf){
  byte tmp=1;
  for(int i=0;i<8;i++){
    if(PCode[val]&tmp){
      digitalWrite(i+shf,HIGH);
    }
    else{
      digitalWrite(i+shf,LOW);
    }
    tmp<<=1;
  }
}

int curId=0;
void loop() {
  // put your main code here, to run repeatedly:
  LEDout(curId++,shiftC);
  curId&=0xf;
  delay(1000);
}
