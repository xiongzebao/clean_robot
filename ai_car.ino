
int motorA1 = 17;
int motorA2 = 15;
int pwdA = 6;

int motorB1 = 16;
int motorB2 = 7;
int pwdB = 5;

int motorC1 = 8;
int motorC2 = 9;
int pwdC = 10;

int motorD1 = 12;
int motorD2 = 13;
int pwdD = 11;

int forward_avoid = 19;
int forward_left_avoid = 17; 
int forward_right_avoid = 18;  
int back_avoid = 16;                          

int speed = 3;
int turn_speed_rate=0.5;
int speed_max = 20;
String speed_mode = "speedup";
int rightCounter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  attachInterrupt(0,RightCount_CallBack, FALLING);
  //attachInterrupt(1,LeftCount_CallBack, FALLING);
  pinMode(motorA1,OUTPUT);
  pinMode(motorA2,OUTPUT);
  pinMode(pwdA,OUTPUT);

  pinMode(motorB1,OUTPUT);
  pinMode(motorB2,OUTPUT);
  pinMode(pwdB,OUTPUT);

  pinMode(motorC1,OUTPUT);
  pinMode(motorC2,OUTPUT);
  pinMode(pwdC,OUTPUT);

  pinMode(motorD1,OUTPUT);
  pinMode(motorD2,OUTPUT);
  pinMode(pwdD,OUTPUT);

//   pinMode(forward_avoid,INPUT);
//   pinMode(forward_left_avoid,INPUT);
//   pinMode(forward_right_avoid,INPUT);
//   pinMode(back_avoid,INPUT);

}

void RightCount_CallBack()
{
  rightCounter++;
  if(rightCounter%3000==0){
    Serial.print(rightCounter);
      Serial.print("\n");
  }
}



void forward(){
  int analogSpeed = map(speed,0,speed_max,0,255);
  analogWrite(pwdA,analogSpeed);
  analogWrite(pwdB,analogSpeed);
  analogWrite(pwdC,analogSpeed);
  analogWrite(pwdD,analogSpeed);
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);
  
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);
  
  digitalWrite(motorC1,HIGH);
  digitalWrite(motorC2,LOW);
  
  digitalWrite(motorD1,HIGH);
  digitalWrite(motorD2,LOW);
}

void turnLeft(){
  int analogSpeed = map(speed,0,speed_max,0,255);
  analogWrite(pwdA,analogSpeed);
  analogWrite(pwdB,analogSpeed*turn_speed_rate);
  analogWrite(pwdC,analogSpeed*turn_speed_rate);
  analogWrite(pwdD,analogSpeed);
  
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  
    digitalWrite(motorC1,HIGH);
  digitalWrite(motorC2,LOW);
    digitalWrite(motorD1,HIGH);
  digitalWrite(motorD2,LOW);
}

void turnRight(){
    int analogSpeed = map(speed,0,speed_max,0,255);
  analogWrite(pwdA,analogSpeed*turn_speed_rate);
  analogWrite(pwdB,analogSpeed);
  analogWrite(pwdC,analogSpeed);
  analogWrite(pwdD,analogSpeed*turn_speed_rate);
  digitalWrite(motorA1,LOW);
  digitalWrite(motorA2,HIGH);
  digitalWrite(motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  
  digitalWrite(motorC1,HIGH);
  digitalWrite(motorC2,LOW);
  digitalWrite(motorD1,HIGH);
  digitalWrite(motorD2,LOW);
}

void back(){
  int analogSpeed = map(speed,0,speed_max,0,255);
  analogWrite(pwdA,analogSpeed);
  analogWrite(pwdB,analogSpeed);
  analogWrite(pwdC,analogSpeed);
  analogWrite(pwdD,analogSpeed);
  digitalWrite(motorA1,HIGH);
  digitalWrite(motorA2,LOW);
  
  digitalWrite(motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  
  digitalWrite(motorC1,LOW);
  digitalWrite(motorC2,HIGH);
  digitalWrite(motorD1,LOW);
  digitalWrite(motorD2,HIGH);
}

void stop(){
      digitalWrite(pwdA,LOW);
      digitalWrite(pwdB,LOW);  
      digitalWrite(pwdC,LOW);  
      digitalWrite(pwdD,LOW);  
}

void speedup(){
  speed+=1;
  if(speed>speed_max){
    speed=speed_max;  
  }
  speed_mode = "speedup";
     Serial.print(speed);
}

void speeddown(){
    speed-=1;
  if(speed<0){
    speed=0;  
  }
  speed_mode = "speeddown";
}
String direction="";
 
void loop() {

//    delay(50);
//    int  forward_value =  digitalRead(forward_avoid);
//    int  foward_left =  digitalRead(forward_left_avoid);
//    int  foward_right =  digitalRead(forward_right_avoid);
//    int  back =  digitalRead(back_avoid);
//
//    if(forward_value==HIGH){
//       Serial.println("forward avoid");
//    }else if(foward_left==HIGH){
//         Serial.println("foward_left avoid");
//    }else if(foward_right==HIGH){
//         Serial.println("foward_right avoid");
//    } if(foward_right==HIGH){
//         Serial.println("back avoid");
//    }
//  
     if(Serial.available()>0) {
     String data = Serial.readStringUntil(',');
      Serial.print(data);
      int index = data.indexOf(':'); 
      String k="";
      String v="";
     if(index != -1){
         k = data.substring(0, index);
         v = data.substring(index + 1, data.length());
     }else{
      k = data;
     }
   
   if(k.compareTo("speedup")!=0&&k.compareTo("speeddown")!=0){
       direction = k;
   }else{
    Serial.print("changeSpeed");
        Serial.print(k);
    changeSpeed(k);
   }
     run();
  }
}

 
void startRun(){
  if(direction.compareTo("left")==0)
  {
    turnLeft();
     return; 
  }
   if(direction.compareTo("right")==0)
   {
      turnRight();
      return; 
   }
  if(direction.compareTo("forward")==0)
   {  
       forward();
       return; 
   }
   if(direction.compareTo("stop")==0)
   {  
       stop();
       return; 
   }
  if(direction.compareTo("back")==0)
   {  
       back();
       return; 
   }
}


void run(){
  if(speed<5&&speed_mode.compareTo("speedup")==0){
    int tmpspeed = speed;
    speed =speed+2;
    startRun();
    delay(500);
    speed =  tmpspeed;
 
  }
   startRun();
}

void changeSpeed(String speed_up_down){
    if(speed_up_down.compareTo("speedup")==0)
   {  
       speedup();
   }
   if(speed_up_down.compareTo("speeddown")==0)
   {  
      speeddown();
   }
}

 



 
