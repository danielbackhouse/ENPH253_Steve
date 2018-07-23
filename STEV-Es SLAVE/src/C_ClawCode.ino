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
  trigger = 0;
  done = true;
}

// Purpose: Controls left claw speed
void openLeftClaw(){
  
  const int angleIncrementClaw = 1;
  const int incrementDelayClaw = 10;
    for (int angle = leftClawClose; angle >= leftClawOpen; angle -= angleIncrementClaw) { 
      left_claw_servo.write(angle);
      delay (incrementDelayClaw); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
    }
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

// Purpose: Controls left arm speed
void raiseLeftArm(){

  left_arm_servo.write(120);
  left_claw_servo.write(leftClawClose);

  trigger = 0;
  done = true;

  // const int angleIncrementArm = 1;
  // const int incrementDelayArm = 5;
  // trigger = 0;
  // done = true;

  //   for (int angle = leftArmDown; angle <= leftArmUp; angle += angleIncrementArm) { 
  //     left_arm_servo.write(angle);
  //     delay (incrementDelayArm); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 15 * (150-0) = 2.25 seconds
  //   }
  
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
  trigger = 0;
  done = true;
}


// Purpose: Controls left claw speed
void openRightClaw(){
  
  // const int angleIncrementClaw = 1;
  // const int incrementDelayClaw = 1;
  //   for (int angle = rightClawClose; angle <= rightClawOpen; angle += angleIncrementClaw) { 
  //     right_claw_servo.write(angle);
  //     delay (incrementDelayClaw); // incrementDelayArm * (ArmUpAngle - ArmDownAngle) = 10 * (150-0) = 1.5 seconds
  //   }
  right_claw_servo.write(150);
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