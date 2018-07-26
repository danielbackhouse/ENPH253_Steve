void rightClawArmSetup(){
  right_claw_servo.attach(RIGHT_CLAW_SERVO);
  right_arm_servo.attach(RIGHT_ARM_SERVO);
  //pinMode(rightContact,INPUT_PULLDOWN);
  right_claw_servo.write(rightClawOpen);
  right_arm_servo.write(rightArmDown);
}

// Left side setup
void leftClawArmSetup() {
  left_claw_servo.attach(LEFT_CLAW_SERVO);
  left_arm_servo.attach(LEFT_ARM_SERVO);
  //pinMode(leftContact,INPUT_PULLDOWN);  
  left_claw_servo.write(leftClawOpen);
  left_arm_servo.write(leftArmDown);
}

// Purpose: Commands left side to follow pickup sequence
void pickupLeft(){
  
  left_claw_servo.write(leftClawClose);
  delay(clawCloseDelay);
  raiseLeftArm();
  delay(raiseArmDelay);
  openLeftClaw();
  lowerLeftArm();
}

// Purpose: Controls left claw speed
void openLeftClaw(){
  
  // const int angleIncrementClaw = 1;
  // const int incrementDelayClaw = 10;
  //   for (int angle = leftClawClose; angle >= leftClawOpen; angle -= angleIncrementClaw) { 
  //     left_claw_servo.write(angle);
  //     delay (incrementDelayClaw); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
  //   }
  left_claw_servo.write(leftClawOpen);
}

// Purpose: Controls left arm speed
void lowerLeftArm(){
  
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = leftArmUp; angle >= leftArmDown; angle -= angleIncrementArm) { 
      left_arm_servo.write(angle);
      delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
}

void lowerLeftArmMid(){
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = leftArmArch; angle >= leftArmMid; angle -= angleIncrementArm) { 
      left_arm_servo.write(angle);
      delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
}

void lowerLeftArmMidGround(){
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = leftArmMid; angle >= leftArmDown; angle -= angleIncrementArm) { 
      left_arm_servo.write(angle);
      //delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
}

// Purpose: Controls left arm speed
void raiseLeftArm(){

  left_arm_servo.write(120);
  left_claw_servo.write(leftClawClose);
  
}
void raiseLeftArmPlate(){
  left_arm_servo.write(120);
  delay(100);

  left_claw_servo.write(leftClawClose);
  delay(5000);
}

void raiseLeftArmArch(){
  left_arm_servo.write(leftArmArch);
}

// Purpose: Commands left side to follow pickup sequence
void pickupRight(){
    //Serial1.println("Picking up thing");

  right_claw_servo.write(rightClawClose);
  delay(clawCloseDelay);
  raiseRightArm();
  delay(raiseArmDelay);
  openRightClaw();
  lowerRightArm();
}

void pickupEwok2(){
  right_claw_servo.write(rightClawClose);
  delay(clawCloseDelay);
  raiseRightArm();
  delay(raiseArmDelay);
  openRightClaw();
  lowerRightArmArch();
  raiseLeftArmArch();
}

void readyForTroopers(){
  left_arm_servo.write(leftArmMid);
  right_arm_servo.write(rightArmMid);
}


// Purpose: Controls left claw speed
void openRightClaw(){
  right_claw_servo.write(rightClawOpen);
}

// Purpose: Controls left arm speed
void lowerRightArm(){
  
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = rightArmUp; angle <= rightArmDown; angle += angleIncrementArm) { 
      right_arm_servo.write(angle);
      delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
}

// Purpose: Controls left arm speed
void raiseRightArm(){
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = rightArmDown; angle >= rightArmUp; angle -= angleIncrementArm) { 
      right_arm_servo.write(angle);
      delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
  
}

void lowerRightArmArch(){
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = rightArmUp; angle <= rightArmArch; angle += angleIncrementArm) { 
      right_arm_servo.write(angle);
      //delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
  
}

void lowerRightArmMid(){
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = rightArmArch; angle <= rightArmMid; angle += angleIncrementArm) { 
      right_arm_servo.write(angle);
      //delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
}

void lowerRightArmMidGround(){
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = rightArmMid; angle <= rightArmDown; angle += angleIncrementArm) { 
      right_arm_servo.write(angle);
      delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
}

void dropEwok2(){
  const int angleIncrementArm = 1;
  const int incrementDelayArm = 15;
    for (int angle = rightArmMid; angle >= rightArmUp; angle -= angleIncrementArm) { 
      right_arm_servo.write(angle);
      delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
  delay(500);
  openRightClaw();
}

void readyForThirdEwok(){
    right_arm_servo.write(rightArmDown);
    left_arm_servo.write(leftArmDown);
    openRightClaw();
    openLeftClaw();
}