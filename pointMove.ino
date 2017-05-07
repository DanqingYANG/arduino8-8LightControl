//2 to 9 = A to H, 10 to 13 = 0 to 3
// one button 
// one to control behavior of the symbol
// one 8*8 board  a little bit time taking

byte symbol[][2] = {{0,0}};
byte shapeInfo[4] = {0,0,1,1};// root_x,root_y, width, height
int count = 0;
int press = 1;
int xpotPin = 0;// ps2 
int ypotPin = 1;// ps2
int pressPin = 3;//analog button
boolean isActivated = true;

void Draw_point(int x,int y)//画点函数
{
  clear_();
  digitalWrite(x+10,HIGH);
  digitalWrite(y+2,LOW);
  delay(1);
}

void moveSymbol()
{
  byte dx = (byte)(0.0035*analogRead(xpotPin));
  byte dy = (byte)(0.007*analogRead(ypotPin));//  for dx and dy should between 0 to 8
  shapeInfo[0] = dx;
  shapeInfo[1] = dy;
}

void showHeart()
{
  int pt[2] = {0,0};
  /*Serial.print((short)shapeInfo[0]);
  Serial.print(",");
  Serial.print((short)shapeInfo[1]);
  Serial.print("\n");*/
  for(int i = 0; i< count; i++)
  {
    pt[0]= symbol[i][0]+shapeInfo[0];
    pt[1]= symbol[i][1]+shapeInfo[1];
    Draw_point(pt[0],pt[1]);
    //Serial.print("p\n");
//    delay(50);
  }
}

void setup(){ 
  //use Serial
  Serial.begin(9600);
  //initialize ps2 
  pinMode(14, INPUT);//x_coordinator
  pinMode(15, INPUT);//y_coordinator
  pinMode(16, INPUT);//press_button
  //initialize button
  pinMode(17,INPUT);
  //initialize 8*8  
  for(int i=2;i<14;i++) 
  { 
   pinMode(i, OUTPUT); 
  }
  //init count
  count = sizeof(symbol)/sizeof(*symbol);
  clear_();
}

void loop() {  
  do{
    //button pressed, analogRead()>0
    press = analogRead(pressPin);
    if(press > 0)
    {
      Serial.print("pressed\n");
      //printCurrentState(); 
      delay(200);
      isActivated = !isActivated;
      //Serial.print("\n I'm here~ 1\n");
    }
    if(isActivated && count > 0)
    {      
      moveSymbol();
      //Serial.print("I'm here~ 2\n");
      showHeart();
    }  
    else{
      clear_();
      delay(100);
    }
  }while(isActivated);
  clear_();  
}

void printCurrentState()
{
  int xval = analogRead(xpotPin);
  int yval = analogRead(ypotPin);  
  int press = analogRead(pressPin);
  Serial.print("\n x = ");
  Serial.print(xval);
  Serial.print(", y = ");
  Serial.print(yval);
  Serial.print(", p = ");
  Serial.print(press);
}

void printBoundary(void)
{
  for(int i = 0; i < 4; i++)
  {
    Serial.print((int)symbol[i]);
    Serial.print(", ");
  }
  Serial.print("\n");
}

void clear_(void)//清除屏幕
{
  for(int i=2;i<10;i++)
  digitalWrite(i, HIGH);
  for(int i=0;i<4;i++)
  digitalWrite(i+10, LOW);
}
