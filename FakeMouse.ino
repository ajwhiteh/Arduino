#define RedButton 12
#define GreenButton 13
#define UpButton 9
#define DownButton 11
#define LeftButton 10
#define RightButton 8

#define SpeedMax 32

short sensorValueX=0;
short sensorValueY=0;
short vx=0;
short vy=0;
byte LastLB=0;
byte LB=0;
byte LastRB=0;
byte RB=0;
int LR=0;
int UD=0;
bool doSend;

void setup() {
  pinMode(RedButton,INPUT);
  digitalWrite(RedButton,HIGH);
  pinMode(GreenButton,INPUT);
  digitalWrite(GreenButton,HIGH);
  pinMode(UpButton,INPUT);
  digitalWrite(UpButton,HIGH);
  pinMode(DownButton,INPUT);
  digitalWrite(DownButton,HIGH);
  pinMode(LeftButton,INPUT);
  digitalWrite(LeftButton,HIGH);
  pinMode(RightButton,INPUT);
  digitalWrite(RightButton,HIGH);
  
  Serial.begin(1200,SERIAL_7N1);
  Serial.write('M');
  delay(100);

  doSend=false;
  /*Serial.begin(9600);
  Serial.print("Start");*/
}

void loop() {
  doSend=false;
  if (digitalRead(RedButton)==0)  {RB=1; doSend=true; }
  else {
    RB=0;
    if (LastRB==1) doSend=true; // send one button up
  }
  if (digitalRead(GreenButton)==0) {LB=1; doSend=true; }
  else {
    LB=0;
    if (LastLB==1) doSend=true; // send one button up
  }

  if (digitalRead(UpButton)==0) {
    sensorValueY+=vy/4; 
    vy-=1;
    if (sensorValueY<-SpeedMax) sensorValueY=-SpeedMax; 
    doSend=true; 
  }
  else if (digitalRead(DownButton)==0) {
    sensorValueY+=vy/4; 
    if (sensorValueY>SpeedMax) sensorValueY=SpeedMax; 
    vy+=1; 
    doSend=true;
  } 
  else {sensorValueY=0; vy=0; }

  if (digitalRead(LeftButton)==0) {
    sensorValueX+=vx/4; 
    vx-=1; 
    if (sensorValueX<-SpeedMax) sensorValueX=-SpeedMax; 
    doSend=true; 
   }
  else if (digitalRead(RightButton)==0) {
    sensorValueX+=vx/4; 
    vx+=1; 
    if (sensorValueX>SpeedMax) sensorValueX=SpeedMax; 
    doSend=true; 
  }
  else {sensorValueX=0; vx=0;}
/*
  if (digitalRead(RedButton)==0) Serial.println ("Red");
  if (digitalRead(GreenButton)==0) Serial.println("Green");
  if (digitalRead(UpButton)==0) Serial.println("Up");
  if (digitalRead(DownButton)==0) Serial.println("Down");
  if (digitalRead(LeftButton)==0) Serial.println("Left");
  if (digitalRead(RightButton)==0) Serial.println("Right");
*/

  if (doSend) {
    byte mouse[3];
    byte YPart=((sensorValueY >>6) <<2) & 0b1100;
    byte XPart=(sensorValueX  >>6) & 0b0011;
    mouse[0]=64 | (LB << 5) | (RB << 4) | YPart | XPart;
    mouse[1]=sensorValueX & 0b0111111;
    mouse[2]=sensorValueY & 0b0111111;
    Serial.write(mouse,3);
  
    delay(25);        // delay in between reads for stability
  }
  LastLB=LB;
  LastRB=RB;
}
