#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>


#define left_mb PB0 //define motor inputs
#define left_mf PB1
#define right_mb PA7
#define right_mf PA6

#define RIGHT_QRD PA8
#define LEFT_QRD PA9

#define max_PWM 65535

int left_qrd = 0;
int right_qrd = 0;
int previous = 0;
int selected = 0;
int counter = 0;


#define QRD_TRHESHOLD_TAPE 300  //analog readings above 300 if line detected 

//adjustable constants for PID-tape
float Kp = 30 , Ki = 0.5, Kd = 67, gain = 1;
float initial_motor_speed =  50000;
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
#define select_button PA2
#define up_button PA4
#define down_button PA3
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
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(left_mb, PWM);
    pinMode(left_mf, PWM);
    pinMode(right_mb, PWM);
    pinMode(right_mf, PWM);
    pinMode(LEFT_QRD, INPUT);
    pinMode(RIGHT_QRD, INPUT);
  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(select_button, INPUT_PULLUP);
    led_init();
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    pid();
     if(!showing_display){
         show_display = !digitalRead(select_button);
         if(show_display)
            delay(200);
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
        pwmWrite(left_mf, 0);
    
        pwmWrite(right_mb, 0);
        pwmWrite(right_mf, 0);
}
