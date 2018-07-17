// #include <Arduino.h>
// #include <Servo.h>

// Servo leftClaw;
// Servo leftArm;
// Servo rightClaw;
// Servo rightArm;

// // Right Contact Pin, Right Claw Pin and Servo Angles
// int rightContact = PB12;
// int rightClawPin = PB8;
// int rightClawClose = 10;
// int rightClawOpen = 150; 

// // Right Arm Pin and Servo Angles;
// int rightArmPin = PB9;
// int rightArmDown = 180;
// int rightArmUp = 30;

// // Left Contact Pin, Left Claw Pin and Servo Angles
// int leftContact = PB13;
// int leftClawPin = PB7;
// int leftClawClose = 180;
// int leftClawOpen = 40;

// // Left Arm Pin and Servo Angles
// int leftArmPin = PB6;
// int leftArmDown = 0;
// int leftArmUp = 150;

// // Lift delays
// int raiseArmDelay = 1000;
// int clawCloseDelay = 2000;

// // Purpose: Setup function
// void setup() {
//   leftClawArmSetup();
//   rightClawArmSetup();
//   Serial1.begin(9600);
// }

// // Purpose: Loop function
// void loop() {
//   Serial1.println(digitalRead(10));
//   if(digitalRead(leftContact)){
//     pickupLeft();
//     Serial1.println("Left contact initiated");
    
//   }
//   if(digitalRead(rightContact)){
//     Serial1.println("Right contact inititiated");
//     pickupRight();
    
//   }
// }

// void rightClawArmSetup(){
//   rightClaw.attach(rightClawPin);
//   rightArm.attach(rightArmPin);
//   //pinMode(rightContact,INPUT_PULLDOWN);
//   rightClaw.write(rightClawOpen);
//   rightArm.write(rightArmDown);
// }

// // Purpose: Commands left side to follow pickup sequence
// void pickupRight(){
  
//   rightClaw.write(rightClawClose);
//   delay(clawCloseDelay);
//   raiseRightArm();
//   delay(raiseArmDelay);
//   openRightClaw();
//   lowerRightArm();
// }


// // Purpose: Controls left claw speed
// void openRightClaw(){
  
//   const int angleIncrementClaw = 1;
//   const int incrementDelayClaw = 10;
//     for (int angle = rightClawClose; angle <= rightClawOpen; angle += angleIncrementClaw) { 
//       rightClaw.write(angle);
//       delay (incrementDelayClaw); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
//     }
// }

// // Purpose: Controls left arm speed
// void lowerRightArm(){
  
//   const int angleIncrementArm = 1;
//   const int incrementDelayArm = 15;
//     for (int angle = rightArmUp; angle <= rightArmDown; angle += angleIncrementArm) { 
//       rightArm.write(angle);
//       delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
//     }
// }

// // Purpose: Controls left arm speed
// void raiseRightArm(){
//   const int angleIncrementArm = 1;
//   const int incrementDelayArm = 15;
//     for (int angle = rightArmDown; angle >= rightArmUp; angle -= angleIncrementArm) { 
//       rightArm.write(angle);
//       delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
//     }
  
// }

// // Left side setup
// //
// void leftClawArmSetup() {
//   leftClaw.attach(leftClawPin);
//   leftArm.attach(leftArmPin);
//   pinMode(leftContact,INPUT_PULLDOWN);  
//   leftClaw.write(leftClawOpen);
//   leftArm.write(leftArmDown);
// }

// // Purpose: Commands left side to follow pickup sequence
// void pickupLeft(){
  
//   leftClaw.write(leftClawClose);
//   delay(clawCloseDelay);
//   raiseLeftArm();
//   delay(raiseArmDelay);
//   openLeftClaw();
//   lowerLeftArm();
// }

// // Purpose: Controls left claw speed
// void openLeftClaw(){
  
//   const int angleIncrementClaw = 1;
//   const int incrementDelayClaw = 10;
//     for (int angle = leftClawClose; angle >= leftClawOpen; angle -= angleIncrementClaw) { 
//       leftClaw.write(angle);
//       delay (incrementDelayClaw); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
//     }
// }

// // Purpose: Controls left arm speed
// void lowerLeftArm(){
  
//   const int angleIncrementArm = 1;
//   const int incrementDelayArm = 15;
//     for (int angle = leftArmUp; angle >= leftArmDown; angle -= angleIncrementArm) { 
//       leftArm.write(angle);
//       delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
//     }
// }

// // Purpose: Controls left arm speed
// void raiseLeftArm(){
//   const int angleIncrementArm = 1;
//   const int incrementDelayArm = 15;
//     for (int angle = leftArmDown; angle <= leftArmUp; angle += angleIncrementArm) { 
//       leftArm.write(angle);
//       delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
//     }
  
// }