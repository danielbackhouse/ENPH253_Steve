#include "Arduino.h"
#include "Servo.h"
#include <C:\Users\johnv\.platformio\packages\framework-arduinoststm32\STM32F1\libraries\WireSlave\src\Wire_slave.h>

#define PLATE_DROP_SERVO PB6
#define LEFT_ARM_SERVO PB1
#define LEFT_CLAW_SERVO PB0
#define RIGHT_ARM_SERVO PA1
#define RIGHT_CLAW_SERVO PA2
#define BUCKET_SERVO PB7

Servo plate_drop_servo;
Servo left_arm_servo;
Servo left_claw_servo;
Servo right_claw_servo;
Servo right_arm_servo;
Servo bucket_servo;

// Right Contact Pin, Right Claw Pin and Servo Angles
const int rightClawClose = 10;
const int rightClawOpen = 150; 

// Right Arm Pin and Servo Angles;
const int rightArmDown = 180;
const int rightArmUp = 30;

// Left Contact Pin, Left Claw Pin and Servo Angles
// int leftContact = PB13;
// int leftClawPin = PB7;
const int leftClawClose = 180;
const int leftClawOpen = 40;

// Left Arm Pin and Servo Angles
// int leftArmPin = PB6;
const int leftArmDown = 0;
const int leftArmUp = 150;

// Lift delays
const int raiseArmDelay = 1000;
const int clawCloseDelay = 2000;

const int min_claw_close_pos = 0;
const int max_claw_close_pos = 180;
const int min_claw_lift_pos = 0;
const int max_claw_lift_pos = 180;
const int min_plate_drop_pos = 180;
const int max_plate_drop_pos = 180;
const int min_bucket_pos = 0;
const int max_bucket_pos = 180;

const int plate_drop_trig = 1;
const int right_claw_pick_up_trig = 2;
const int right_claw_lift_trig = 3;
const int left_claw_pick_up_trig = 4;
const int left_claw_lift_trig = 5;
const int bucket_trig = 6;
const int lift_both_claws = 7;

const int right = 0;
const int left = 1;
const int both = 3;

int plate_drop_pos = 0;
int left_claw_lift_pos = 0;
int left_claw_close_pos = 0;
int right_claw_lift_pos = 0;
int right_claw_close_pos = 0;
int bucket_pos = 0;

volatile u_int8_t trigger = 0;
volatile bool done = false;

void EwokPickUp (int side){}

void bucketDrop(){}

void clawLift(int side){}

void setup()
{
  Serial1.begin(9600);
  leftClawArmSetup();
  rightClawArmSetup();
  plate_drop_servo.attach(PLATE_DROP_SERVO);
  plate_drop_servo.write(0);
  left_claw_servo.attach(LEFT_CLAW_SERVO);
  left_arm_servo.attach(LEFT_ARM_SERVO);
  right_claw_servo.attach(RIGHT_CLAW_SERVO);
  right_arm_servo.attach(RIGHT_ARM_SERVO);
  bucket_servo.attach(BUCKET_SERVO);
  Wire1.begin(4);
  Wire1.onReceive(receiveEvent);
  Wire1.onRequest(requestEvent);
}

void requestEvent() {
  Wire1.write(done);
}

void receiveEvent(int howmany){
    trigger = Wire1.read();
    done = 0;
}

void loop()
{
    switch (trigger){

        case 0:
        break;

        case plate_drop_trig:
        dropPlate();
        break;

        case right_claw_pick_up_trig:
        pickupRight();
        break;

        case right_claw_lift_trig:
        clawLift(right);
        break;

        case left_claw_pick_up_trig:
        pickupLeft();
        break;

        case left_claw_lift_trig:
        clawLift(left);
        break;

        case bucket_trig:
        bucketDrop();
        break;

        case lift_both_claws:
        clawLift(both);
        break;

    }
}

void dropPlate(){
    plate_drop_servo.write(180);
    trigger = 0;
    done = true;
}