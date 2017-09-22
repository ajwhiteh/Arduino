#define RedButton 12
#define GreenButton 13
#define UpButton 9
#define DownButton 11
#define LeftButton 10
#define RightButton 8

short up=4; //u
short down=3; //d
short left=5; //l
short right=6; //r
short leftClick=1; //LDown
short leftUnclick=0; //LUp
short rightClick=2; //RDown
short rightUnclick=7; //RUp
bool Ready=false;

void setup(){
  
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
 
 Serial.begin(115200,SERIAL_8N1);
 delay(100);
}

//Function that checks if connection is working
/*bool state(){
  Serial.write("Controller Ready");
  if (Serial.available() < 0){
    delay(500);
    state();
  }
  else{
    return true;
  }
}
*/

void loop() {
  /*
  while (Ready==false){
    Ready=state();
  }
  */
  
  Serial.write("Controller Ready");
  
  if (digitalRead(RedButton)==0){
    Serial.write(leftClick);
  }
  if (digitalRead(RedButton)==1){
    Serial.write(leftUnclick);
  }
  
  if(digitalRead(GreenButton)==0){
    Serial.write(rightClick);
  }
  if(digitalRead(GreenButton)==1){
    Serial.write(rightUnclick);
  }
  
  if(digitalRead(UpButton)==0){
    Serial.write(up);
  }
  
  if(digitalRead(DownButton)==0){
    Serial.write(down);
  }
  
  if(digitalRead(LeftButton)==0){
    Serial.write(left);
  }
  
  if(digitalRead(RightButton)==0){
    Serial.write(right);
  }
  
  delay(50);
  
}
