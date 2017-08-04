#include <SoftwareSerial.h>

int flexSensorPin = A0; //analog pin 0
int flexSensorPin1 = A1; //analog pin 1
int flexSensorPin2 = A2; //analog pin 2
int flexSensorPin3 = A3; //analog pin 3
int flexSensorPin4 = A4; //analog pin 4

SoftwareSerial XBee(2, 3);

void sendInfo (int flex0to100, int flex0to1001, int flex0to1002, int flex0to1003, int flex0to1004);

void setup(){
  Serial.begin(9600);
  XBee.begin(9600);
}

char forward = 'F';
char back = 'B';
char right = 'R';
char left = 'L';
char servorightforward = 'Z';
char servorightback = 'Y';
char up = 'U';
char down = 'D';
char openClaw = 'O';
char closeClaw = 'C';
char servoLeft= 'J';
char servoRight = 'K';

void loop(){
  int flexSensorReading = analogRead(flexSensorPin); 
  int flexSensorReading1 = analogRead(flexSensorPin1); 
  int flexSensorReading2 = analogRead(flexSensorPin2); 
  int flexSensorReading3 = analogRead(flexSensorPin3); 
  int flexSensorReading4 = analogRead(flexSensorPin4); 
  
  int flex0to100 = map(flexSensorReading, 400, 720, 0, 100);
  Serial.println(flex0to100);

  int flex0to1001 = map(flexSensorReading1, 400, 720, 0, 100);
  Serial.println(flex0to1001);

  int flex0to1002 = map(flexSensorReading2, 400, 720, 0, 100);
  Serial.println(flex0to1002);
  
    int flex0to1003 = map(flexSensorReading3, 400, 720, 0, 100);
  Serial.println(flex0to1003);
  
    int flex0to1004 = map(flexSensorReading4, 400, 720, 0, 100);
  Serial.println(flex0to1004);

  delay(1);
  sendInfo(flex0to100, flex0to1001, flex0to1002, flex0to1003, flex0to1004);
}

void sendInfo (int flex0to100, int flex0to1001, int flex0to1002, int flex0to1003, int flex0to1004){
   if (flex0to100 < 10 && flex0to1001 < 10 && flex0to1002 < 10 && flex0to1003 < 10 && flex0to1004 < -5){//drive forward
    XBee.write(forward);
  }
  else if (flex0to1001 < 10 && flex0to1002 < 10 && flex0to1003 < 10 && flex0to1004 < -5){//open claw
    XBee.write(openClaw);
  }
  else if (flex0to100 < 10 && flex0to1001 < 10 && flex0to1002 < 10 && flex0to1003 < 10){//close claw
    XBee.write(closeClaw);
  }
  else if (flex0to1001 < 10 && flex0to1002 < 10 && flex0to1003 < 10){//drive back
    XBee.write(back);
  }
  else if (flex0to1002 < 10 && flex0to1003 < 10 && flex0to1004 < -5){//turn right
    XBee.write(right);
  }
  else if (flex0to100 < 10 && flex0to1001 < 10 && flex0to1002 < 10){//turn left
    XBee.write(left);
  }
  else if (flex0to100<10 && flex0to1003<10 && flex0to1004<-5){//turn claw right
    XBee.write(servoRight);
  }
  else if (flex0to100<10 && flex0to1001 < 10 && flex0to1004<-5){//turn claw left
    XBee.write(servoLeft);
  }
  else if (flex0to1001 < 10 && flex0to1003 < 10){//claw
    XBee.write(up);
  }
  else if (flex0to1003<10 && flex0to1004<-5){//claw forward
    XBee.write(servorightforward);
  }
  else if (flex0to100<10 && flex0to1001<10){//claw back
    XBee.write(servorightback);
  }
  else if (flex0to1002 < 10){//claw down
    XBee.write(down);
  }
}
