#include <UF_uArm.h>




UF_uArm uarm;           // initialize the uArm library 

byte incomingByte;
int data;

void setup() {
  uarm.init();
  uarm.setServoSpeed(SERVO_R, 20);  // 0=full speed, 1-255 slower to faster
  uarm.setServoSpeed(SERVO_L, 20);  // 0=full speed, 1-255 slower to faster
  uarm.setServoSpeed(SERVO_ROT, 100); // 0=full speed, 1-255 slower to faster
  delay(500);
  attachInterrupt(digitalPinToInterrupt(LIMIT_SW), stopMovement, RISING);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void stopMovement() {
  uarm.stop();
}
void armDown(){
   uarm.setHeight(110.00, -60.00);
   delay(100);
}

void armUp(){
   uarm.setHeight(50.00, 250.00);
   delay(1000);
}

void rotateArmTo(float angle){
  uarm.rotateArmTo(angle);
  delay(1000);
}

void rotateHandTo(float angle){
  uarm.rotateHandTo(angle);
  delay(1000);
}

void pickUp(){
  uarm.valveOff();
  uarm.pumpOn();
  delay(1000);
}

void drop(){
  uarm.valveOn();
  uarm.pumpOff();
  delay(1000);
}

void alert(){
   uarm.alert(2, 200, 100);
}

void start(){
  while(digitalRead(4) == HIGH){}
  uarm.alert(2, 100, 100);
  delay(1000);
}

void loop() {
 if (Serial.available() > 0) {
   incomingByte = Serial.read();
   switch(incomingByte){
    case 'a':
      data = Serial.parseInt();
      rotateArmTo((float) data);
      break;

    case 'w': //wake
      uarm.setPosition(50.00, 250.00, 0, 0);
      uarm.alert(3, 100, 100);
      break;

    case 'c': // connect
      Serial.println("Arm Online");
      uarm.alert(5, 100, 100);
      break;
      
    case 's': // sleep
      uarm.pumpOff();
      uarm.setPosition(100.00, 30.00, 0, 0);
      uarm.alert(2, 100, 100);
      
      break; 
      
    case 'h': //h
      data = Serial.parseInt();
      rotateHandTo((float) data);

      break;
    case 'u': //u
      armUp();
      break;
    case 'd': //d
      armDown();
  
      break;
    case 'p': //p 
      pickUp();
      break;
    case 'o': //o
      drop();
      break;
    default:
      alert();
   }
 }


}


