#include "Arduino.h"
#include "Servo.h"
#include "Wire_slave.h"
#include <ext_interrupts.h>

#define PLATE_DROP_SERVO PA1 //BLACK
#define LEFT_ARM_SERVO PB1
#define LEFT_CLAW_SERVO PB0
#define RIGHT_ARM_SERVO PA3 //RED
#define RIGHT_CLAW_SERVO PA2 //WHITE
#define BUCKET_SERVO PA0 //Green

//PA7

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
const int rightClawClose = 0;
const int rightClawOpen = 120; 

// Right Arm Pin and Servo Angles;
const int rightArmDown = 180;
const int rightArmUp = 10;
const int rightArmMid = 110;
const int rightArmArch = 40;

// Left Contact Pin, Left Claw Pin and Servo Angles
// int leftContact = PB13;
// int leftClawPin = PB7;
const int leftClawClose = 180;
const int leftClawOpen = 40;

// Left Arm Pin and Servo Angles
// int leftArmPin = PB6;
const int leftArmDown = 0;
const int leftArmUp = 160;
const int leftArmMid = 80;
const int leftArmPlate = 95;
const int leftArmArch = 140;

// Lift delays
const int raiseArmDelay = 500;
const int clawCloseDelay = 1000;

const int min_plate_drop_pos = 180;
const int max_plate_drop_pos = 180;
const int bucket_up = 170;
const int bucket_down = 45;

const int plate_drop_trig = 14;
const int right_claw_pick_up_trig = 2;
const int ewok_2_pick_up_trig = 3;
const int left_claw_pick_up_trig = 4;
const int left_claw_lift_trig = 5;
const int bucket_trig = 6;
const int lift_left_claw_arch = 7;
const int ready_for_troopers = 8;
const int ready_for_third_ewok = 9;

const int get_pos = 10;
const int reset_left = 11;
const int reset_right = 12;
const int reset_both = 13;


volatile u_int32_t left_pos = 0;
volatile u_int32_t right_pos = 0;
volatile u_int8_t right_count = 0;
volatile u_int8_t left_count = 0;


volatile u_int8_t trigger = 0;
volatile int send = 0;
volatile bool position = true;
volatile bool received = false;


void setup()
{
  Serial.begin(115200);
  leftClawArmSetup();
  rightClawArmSetup();
  plate_drop_servo.attach(PLATE_DROP_SERVO);
  plate_drop_servo.write(0);
  bucket_servo.attach(BUCKET_SERVO);
  bucket_servo.write(bucket_up);
  pinMode(ENCODE_LEFT_WHEEL_A, INPUT_PULLUP);
  pinMode(ENCODE_RIGHT_WHEEL_A, INPUT_PULLUP);
  attachInterrupt(ENCODE_LEFT_WHEEL_A, left_interrupt, CHANGE);
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
  else if (received == false){
      Wire1.write(trigger);
      received = true;
  }
  else {   
      Wire1.write(send);
      if(send != 0){
          position = true;
          received = false;
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
        send = 0;
        position = false;
    }
}

void loop(){
    switch (trigger){
        case 0:
        resetTrig();
        break;

        case plate_drop_trig:
        dropPlate();
        send = plate_drop_trig;
        trigger = 0;
        break;

        case right_claw_pick_up_trig:
        pickupRight();
        send = right_claw_pick_up_trig;
        trigger = 0;
        break;

        case ewok_2_pick_up_trig:
        pickupEwok2();
        send = ewok_2_pick_up_trig;
        trigger = 0;
        break;

        case left_claw_pick_up_trig:
        Serial.println("picking up ewok");
        pickupLeft();
        send = left_claw_pick_up_trig;
        trigger = 0;
        Serial.println("picked up 3rd ewok");
        break;

        case left_claw_lift_trig:
        raiseLeftArm();
        resetTrig();
        break;

        case bucket_trig:
        bucketDrop();
        send = bucket_trig;
        trigger = 0;
        break;

        case lift_left_claw_arch:
        //.println("raising left arm");
        raiseLeftArmPlate();
        send = lift_left_claw_arch;
        trigger = 0;
        //.println("left arm lifted");
        break;

        case ready_for_troopers:
        readyForTroopers();
        send = ready_for_troopers;
        trigger = 0;
        break;

        case ready_for_third_ewok:
        //.println("ready for ewoks");
        readyForThirdEwok();
        send = ready_for_third_ewok;
        trigger = 0;
        //.println("done getting read");
        break;

        default:
        resetTrig();
        break;

    }
}

void dropPlate(){
    //delay(1000);
   // //1.println("In loop");
    plate_drop_servo.write(180);
    delay(500);
    ////1.println("Servo moved!");
}

void bucketDrop(){
    for (int angle = bucket_up; angle >= bucket_down; angle--) { 
      bucket_servo.write(angle);
      delay (5);
    }
    delay(500);
    for (int angle = bucket_down; angle <= bucket_up; angle++) { 
      bucket_servo.write(angle);
      delay (2);
    }
}

void resetTrig(){
    trigger = 0;
}