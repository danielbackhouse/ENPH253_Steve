#include "Arduino.h"
#include "Servo.h"
#include "Wire_slave.h"
#include <ext_interrupts.h>

#define PLATE_DROP_SERVO PB1
#define LEFT_ARM_SERVO PA6
#define LEFT_CLAW_SERVO PB0
#define RIGHT_ARM_SERVO PA3
#define RIGHT_CLAW_SERVO PA2
#define BUCKET_SERVO PB7

// #define ENCODE_LEFT_WHEEL_A PB15
// #define ENCODE_LEFT_WHEEL_B PB14
#define ENCODE_RIGHT_WHEEL_A PB9
#define ENCODE_LEFT_WHEEL_A PB8

Servo plate_drop_servo;
Servo left_arm_servo;
Servo left_claw_servo;
Servo right_claw_servo;
Servo right_arm_servo;
Servo bucket_servo;

// Right Contact Pin, Right Claw Pin and Servo Angles
const int rightClawClose = 10;
const int rightClawOpen = 140; 

// Right Arm Pin and Servo Angles;
const int rightArmDown = 180;
const int rightArmUp = 30;

// Left Contact Pin, Left Claw Pin and Servo Angles
// int leftContact = PB13;
// int leftClawPin = PB7;
const int leftClawClose = 180;
const int leftClawOpen = 60;

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

const int get_pos = 10;
const int reset_left = 11;
const int reset_right = 12;
const int reset_both = 13;

// const int right = 0;
// const int left = 1;
// const int both = 3;

// #define PPM 18  //number of clicks per encoder rotation
// #define WHEEL_CIRCUMFERENCE 56

// double encodeGearRatio = 4/18; //encoder gear over rear wheel gear

//const double add_dist = 1/PPM*encodeGearRatio*WHEEL_CIRCUMFERENCE;

volatile double left_dist = 0;
volatile double right_dist = 0;
volatile u_int32_t left_pos = 0;
volatile u_int32_t right_pos = 0;
volatile u_int8_t right_count = 0;
volatile u_int8_t left_count = 0;


volatile u_int8_t trigger = 0;
volatile bool done = false;
volatile bool position = true;

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
//   left_claw_servo.attach(LEFT_CLAW_SERVO);
//   left_arm_servo.attach(LEFT_ARM_SERVO);
   right_claw_servo.attach(RIGHT_CLAW_SERVO);
   right_arm_servo.attach(RIGHT_ARM_SERVO);
//   bucket_servo.attach(BUCKET_SERVO);
  pinMode(ENCODE_LEFT_WHEEL_A, INPUT_PULLUP);
//   pinMode(ENCODE_LEFT_WHEEL_B, INPUT_PULLUP);
  pinMode(ENCODE_RIGHT_WHEEL_A, INPUT_PULLUP);
//   pinMode(ENCODE_RIGHT_WHEEL_B, INPUT_PULLUP);
  attachInterrupt(ENCODE_LEFT_WHEEL_A, left_interrupt, CHANGE);
  //attachInterrupt(ENCODE_LEFT_WHEEL_B, left_interrupt, CHANGE);
  //attachInterrupt(ENCODE_RIGHT_WHEEL_A, right_interrupt, CHANGE);
  attachInterrupt(ENCODE_RIGHT_WHEEL_A, right_interrupt, CHANGE);
  
  Wire1.begin(4);
  Wire1.onReceive(receiveEvent);
  Wire1.onRequest(requestEvent);
}

void requestEvent() {
  if (position == true){
    byte rightArray[4];
    byte leftArray[4];
    rightArray[0] = (right_pos >> 24) & 0xFF;
    rightArray[1] = (right_pos >> 16) & 0xFF;
    rightArray[2] = (right_pos>> 8) & 0xFF;
    rightArray[3] = right_pos & 0xFF;
    leftArray[0] = (left_pos >> 24) & 0xFF;
    leftArray[1] = (left_pos >> 16) & 0xFF;
    leftArray[2] = (left_pos>> 8) & 0xFF;
    leftArray[3] = left_pos & 0xFF;
    Wire1.write(leftArray, 4);
    Wire1.write(rightArray, 4);
  }
  else {   
      Wire1.write(done);
      if(done == true){
          position = true;
      }
  }

}
void receiveEvent(int howmany){
    trigger = Wire1.read();
    if (trigger == reset_right){
        right_pos = 0;
    }
    else if (trigger == reset_left){
        left_pos = 0;
    }
    else if (trigger == reset_both){
        right_pos = 0;
        left_pos = 0;
    }
    else {
        done = false;
        position = false;
    }
}

void loop()
{

    // Serial1.println(left_pos);
    // Serial1.println(right_pos);
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
        //clawLift(right);
        break;

        case left_claw_pick_up_trig:
        pickupLeft();
        break;

        case left_claw_lift_trig:
            raiseLeftArm();
            break;

        case bucket_trig:
        bucketDrop();
        break;

        case lift_both_claws:
        //clawLift(both);
        break;

    }
}

void dropPlate(){
    delay(1000);
   // Serial1.println("In loop");
    plate_drop_servo.write(180);
    delay(500);
    //Serial1.println("Servo moved!");
    trigger = 0;
    done = true;
}