#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial XBee(2, 3);

Servo servoBase;
Servo servoBottomLeft;
Servo servoBottomRight;
Servo servoGrab;

int SB = 130;
int SG = 50;
int SBL = 180;
int SBR = 35;

int STBY = 10; //standby
int PWMA = 3; //Speed control 
int PWMB = 5; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void moveTheMotors(char reading);
void moveTheClaw(char reading);

void setup(){
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  Serial.begin(9600);
  XBee.begin(9600); 
  
  servoBase.attach(13); 
  servoBottomLeft.attach(4);
  servoBottomRight.attach(6);
  servoGrab.attach(7);
}

void move(int motor, int speed, int direction){
  digitalWrite(STBY, HIGH); //disable standby
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;
  
  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  
  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
  digitalWrite(STBY, LOW); 
}

void loop(){
  servoGrab.write(SG);
  servoBase.write(SB);
  servoBottomLeft.write(SBL);
  servoBottomRight.write(SBR);
  
  char reading = XBee.read();
  Serial.println(reading);
  
  if (reading == 'F' || reading == 'B' || reading == 'L' ||reading == 'R') {
    moveTheMotors(reading);
  }
  else if (reading == 'Z'|| reading == 'Y' || reading == 'U' ||reading == 'D' || reading == 'O' || reading == 'C' ||reading == 'J' || reading == 'K'){
    moveTheClaw(reading);
  }
  else{
    stop();
  }

delay(25);
}

void moveTheMotors (char reading){
  if(reading == 'F'){
    move(1, 255, 1); 
    move(2, 255, 1); 
  }
  else if (reading=='R'){
    move(2, 255, 1);
  }
  else if (reading == 'L'){
    move(1, 255, 1);
  }
  else if(reading =='B'){
    move(1, 255, 0);
    move(2, 255, 0);
  }
}

void moveTheClaw (char reading){
  if (reading == 'Z' && SBR <= 180){
    SBR += 5;
  }
  else if (reading == 'Y' && SBR >= 35){
    SBR -= 5;
  }
  else if (reading == 'U' && SBL <= 180){
    SBL += 5;
  }
  else if (reading == 'D' && SBL >= 100){
    SBL -= 5;
  }
  else if (reading == 'O' && SG <= 180){
    SG += 5;
  }
  else if (reading == 'C' && SG >= 50){
    SG -= 5;
  }
  else if (reading == 'K' && SB >= 50){
    SB -= 5;
  }
  else if (reading == 'J' && SB <= 180) {
    SB += 5;
  }
}

