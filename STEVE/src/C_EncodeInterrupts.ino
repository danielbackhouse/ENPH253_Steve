// #include "Arduino.h"
// #include <ext_interrupts.h>


// #define ENCODE_LEFT_WHEEL_A PB12
// #define ENCODE_LEFT_WHEEL_B PB13
// #define ENCODE_RIGHT_WHEEL_A PB14
// #define ENCODE_RIGHT_WHEEL_B PB15

// #define PPM 18  //number of clicks per encoder rotation
// #define WHEEL_CIRCUMFERENCE 56

// double encodeGearRatio = 4/18; //encoder gear over rear wheel gear

// const double add_dist = 1/PPM*encodeGearRatio*WHEEL_CIRCUMFERENCE;

// volatile double left_dist = 0;
// volatile double right_dist = 0;
// volatile int32_t left_pos = 0;
// volatile int32_t right_pos = 0;


// void setup() {
//     pinMode(ENCODE_LEFT_WHEEL_A, INPUT_PULLUP);
//     pinMode(ENCODE_LEFT_WHEEL_B, INPUT_PULLUP);
//     pinMode(ENCODE_RIGHT_WHEEL_A, INPUT_PULLUP);
//     pinMode(ENCODE_RIGHT_WHEEL_B, INPUT_PULLUP);
//     attachInterrupt(ENCODE_LEFT_WHEEL_A, left_interrupt, CHANGE);
//     attachInterrupt(ENCODE_LEFT_WHEEL_B, left_interrupt, CHANGE);
//     attachInterrupt(ENCODE_RIGHT_WHEEL_A, right_interrupt, CHANGE);
//     attachInterrupt(ENCODE_RIGHT_WHEEL_B, right_interrupt, CHANGE);
//     Serial1.begin(9600);
// }

// void loop() {
//     Serial1.println(left_pos);
//     Serial1.println(right_pos);
//     delay(500);
// }

// void right_interrupt()
// {
//     volatile static uint8_t r_state = 0;
//     r_state = (r_state << 2) & 0x0f;
//     r_state |= (digitalRead(ENCODE_RIGHT_WHEEL_A) << 1) | digitalRead(ENCODE_RIGHT_WHEEL_B);
//     switch (r_state)
//     {
//         case 0x0d:
//         right_pos++;
//         break;
//         case 0x0e:
//         right_pos--;
//         break;
//     }
//     right_dist+= add_dist; //need to double check this formula and make as own var
// }

// void left_interrupt()
// {
//     volatile static uint8_t l_state = 0;
//     l_state = (l_state << 2) & 0x0f;
//     l_state |= (digitalRead(ENCODE_LEFT_WHEEL_A) << 1) | digitalRead(ENCODE_LEFT_WHEEL_B);
//     switch (l_state)
//     {
//         case 0x0d:
//         left_pos++;
//         break;
//         case 0x0e:
//         left_pos--;
//         break;
//     }
//     left_dist+= 1/PPM*encodeGearRatio*WHEEL_CIRCUMFERENCE; //need to double check this formula and make own var
// }

// double getRightDistance() {
//     return right_dist;
// }

// void resetRightDist() {
//     right_pos = 0;
//     right_dist = 0;
// }

// void resetLeftDist() {
//     left_pos = 0;
//     left_dist = 0;
// }