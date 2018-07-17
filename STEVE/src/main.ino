#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

//Wire Stuff for now placed here
TwoWire WIRE2 (2,I2C_FAST_MODE);
#define Wire WIRE2

#define left_mb PA3 //define motor inputs
#define left_mf PA2
#define right_mb PA1
#define right_mf PA0

#define INITIAL_RIGHT_QRD PB0
#define INITIAL_LEFT_QRD PB1
#define MIDDLE_RIGHT_QRD PA6
#define MIDDLE_LEFT_QRD PA7
#define EDGE_DETECT PA5 //A4 sucks

#define RIGHT_CLAW PB8
#define LEFT_CLAW PB9

enum States{
  Check, FirstEwok, FirstGap, SecondEwok, IR, ThirdEwok, Dump, Stop, TestInitial, TestSecond
  };

int state = Check;

#define max_PWM 65500

int left_qrd = 0;
int right_qrd = 0;
int previous = 0;
int selected = 0;
int counter = 0;


#define QRD_TRHESHOLD_TAPE 1000  //analog readings below 1000 if line detected 
#define EDGE_THRESHOLD 2200

//adjustable constants for PID-tape
float Kp = 0 , Ki = 0, Kd = 0, gain = 0;
float initial_motor_speed =  0;

//Adjustable constants for the initial tape following
float i_Kp = 150, i_Ki = 0, i_Kd = 50, i_gain = 100;
float i_initial_motor_speed = 25000;

//Adjustable constants for the secondary tape following
float s_Kp = 100, s_Ki = 0, s_Kd = 0, s_gain = 100;
float s_initial_motor_speed = 25000;
//Global variables for PID-Tape
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

//PID functions
void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


bool changing = false;
bool show_display = false;
bool showing_display  = false;
bool new_screen = false;
int var_selected = 0;
int menu_level = 0;
int num_menu_items = 1;
#define select_button PB5
#define up_button PB3
#define down_button PB4
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup() {
    EEPROM.init();
    EEPROM.PageBase0 = 0x801F000;
    EEPROM.PageBase1 = 0x801F800;
    EEPROM.PageSize  = 0x400;
    Serial1.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(left_mb, PWM);
    pinMode(left_mf, PWM);
    pinMode(right_mb, PWM);
    pinMode(right_mf, PWM);
    pinMode(INITIAL_LEFT_QRD, INPUT);
    pinMode(INITIAL_RIGHT_QRD, INPUT);
    pinMode(MIDDLE_RIGHT_QRD, INPUT);
    pinMode(MIDDLE_LEFT_QRD, INPUT);
    pinMode(EDGE_DETECT, INPUT);
    pinMode(RIGHT_CLAW, INPUT_PULLDOWN);
    pinMode(LEFT_CLAW, INPUT_PULLDOWN);

  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(select_button, INPUT_PULLUP);
  digitalWrite(LED_BUILTIN, LOW);
  led_init();
   // digitalWrite(LED_BUILTIN, HIGH);
  // Serial1.println("JAfd");
}

void loop() {

    switch (state){
      case Check:
        check();
        delay(1000);
        digitalWrite(LED_BUILTIN, HIGH);
        break;
      case FirstEwok:
        sensors(FirstEwok);
        pid();
        break;
      case Stop:
        end_moving();
        break;
      case TestInitial:
        test_initial();
        break;
      case TestSecond:
        test_second();
        break;
      default:
        end_moving();
        break;


    }
     if(!showing_display){
         show_display = !digitalRead(select_button);
         if(show_display)
            delay(100);
     }
     if(show_display || showing_display){
       showing_display = true;
         end_moving();
         new_screen = true;
        led_display();
    }
}

void end_moving(){
        pwmWrite(left_mf, 0);
        pwmWrite(left_mb, 0);
    
        pwmWrite(right_mb, 0);
        pwmWrite(right_mf, 0);
}

void check(){
  state = FirstEwok;
  Kp = i_Kp, Kd = i_Kd, Ki = i_Ki, gain = i_gain;
  initial_motor_speed = i_initial_motor_speed;
}