
void led_display(){

    if(!digitalRead(select_button)){
        new_screen = true;
        if(menu_level == 0 && var_selected == 0){
            load();
            int x = 0;
        }
        else if(var_selected == 0){
            menu_level = 0;
        }
        else if(menu_level == 0 && var_selected == 1){
            save();
            new_screen = true;
            int y = 0;
        }
        else if( menu_level == 0 && var_selected == 2){
            menu_level = 1;
        }
        else if(menu_level == 0 && var_selected == 3){
            display.clearDisplay();
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println("STEV-EEEEE");
            display.display();
            delay(1000);
            var_selected = 0;
            show_display = false;
            showing_display = false;
            new_screen = false;
        }
        else if (menu_level == 1){
            if (var_selected == 1){
                    changeVal(&Kp, "Kp", 0.5);
            }
            if(var_selected == 2){
                changeVal(&Ki, "Ki", 0.1);
            }
            if(var_selected == 3){
                changeVal(&Kd, "Kd", 0.5);
            }
            if(var_selected == 4){
                changeVal(&gain, "Gain", 0.2);
            }
            if(var_selected == 5){
                changeVal(&initial_motor_speed, "Speed", 100);
            }
            new_screen = true;
        }
        var_selected = var_selected;
        
        delay(50);
    }
    else if(!digitalRead(up_button)){
        Serial.println("hey");
        var_selected--;
        new_screen = true;
        delay(20);
    }
    else if(!digitalRead(down_button)){
        var_selected++;
        new_screen = true;
        delay(20);
    }
    if(var_selected < 0){
        var_selected = 0;
    }
    else if(var_selected >= num_menu_items)
        var_selected = num_menu_items - 1;
  if(new_screen){
    int cursor = 0;
    display.clearDisplay();

    switch(menu_level) {
        case 0:
        num_menu_items = 4;
         display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(6,0);
        display.println("Load");
        display.setCursor(6,10);
        display.println("Save");
        display.setCursor(6,20);
        display.println("Tape");
        display.setCursor(6,30);
        display.println("Resume");
        display.setCursor(6,40);
        cursor = var_selected*10;
        display.setCursor(0,cursor);
        display.println("*");
        display.display();
        break;

        case 1:
        num_menu_items = 6;
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(7,0);
        display.println("<- back");
        display.setCursor(6,10);
        display.print("Kp = ");
        display.println(Kp);
        display.setCursor(6,20);
        display.print("Ki = ");
        display.println(Ki);
        display.setCursor(6,30);
        display.print("Kd = ");
        display.println(Kd);
        display.setCursor(6,40);
        display.print("Gain = ");
        display.println(gain);
        display.setCursor(6,50);
        display.print("speed = ");
        display.println(initial_motor_speed);
        cursor = var_selected*10;
        display.setCursor(0,cursor);
        display.println("*");
        display.display();
        break;
        default:
        display.clearDisplay();
        break;
    }
   
    new_screen = false;
    // delay(500);
    // digitalWrite(LED_BUILTIN, HIGH);
}
}
void changeVal(float *val, char name[],float change){
    float thisVal = *val;
    Serial.println(thisVal);
    Serial.println(name);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(name);
    display.print(" = ");
    display.println(thisVal);
    display.display();
    delay(100);
    changing = true;
    while(changing){
        changing = digitalRead(select_button);
        if(!changing){
            delay(50);
        }
        if(!digitalRead(up_button)){
            thisVal = thisVal + change;
            new_screen = true;
            delay(10);
         }
        else if(!digitalRead(down_button)){
            thisVal =  thisVal - change;
            new_screen = true;
            delay(10);
        }
        if(new_screen){
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.print(name);
            display.print(" = ");
            display.println(thisVal);
            display.display();
            new_screen = false;
        }
    }
    delay(50);
    *val = thisVal;

}

void save(){
    if(EEPROM.read(0) != 65535 || true){
          display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("Replace old values?");
        num_menu_items = 2;
         display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(6,10);
        display.println("no");
        display.setCursor(6,20);
        display.println("yes");
        var_selected = 1;
        int cursor = var_selected*10;
        display.setCursor(0,cursor);
        display.println("*");
        display.display();
        delay(200);
        changing = true;
        
        while(changing){

            new_screen = false;
            changing = digitalRead(select_button);
             if(!changing){
                new_screen = false;
                if(var_selected == 1){
                     display.clearDisplay();
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0,0);
                display.println("Not saving..");
                display.display();

                }
                else if (var_selected == 2){
                    display.clearDisplay();
                    display.setTextSize(1);
                    display.setTextColor(WHITE);
                    display.setCursor(0,0);
                    display.println("Saving..");
                    display.display();
                }
                delay(1000);
            }
            else if(!digitalRead(up_button)){
                Serial.println("hey");
                var_selected--;
                new_screen = true;
                delay(20);
            }
            else if(!digitalRead(down_button)){
                    var_selected++;
                    new_screen = true;
                    delay(20);
            }
            if(var_selected < 1)
                var_selected = 1;
            else if(var_selected > 2)
                var_selected = 2;
            if(new_screen){
                 display.clearDisplay();
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0,0);
                display.println("Replace old values?");
                num_menu_items = 2;
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(6,10);
                display.println("no");
                display.setCursor(6,20);
                display.println("yes");
                cursor = var_selected*10;
                display.setCursor(0,cursor);
                display.println("*");
                display.display();
              }
        }

    }

}

void load(){
    if(EEPROM.read(0) == 65535){
          display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.print("Error: No values are saved.");
        display.display();
        changing = true;
        while(changing){
            changing = digitalRead(select_button);
            if(!changing){
                delay(50);
            }
        }

    }
    else{
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("Loading...");
        delay(100);
        // display.print("Ki = ");
        // display.println(Ki);
        // float pre = Ki *10;
        // int entry = pre;
        // display.print("entry = ");
        // display.println(entry);
        // float prered = entry;
        // float red = prered / 10;
        //  display.print("read = ");
        // display.println(red);
        display.display();
        float preKp = EEPROM.read(0);
        Kp = preKp/10;
        float preKd = EEPROM.read(1);
        Kd = preKd/10;
        float preKi = EEPROM.read(2);
        Ki = preKi/10;
        float pregain = EEPROM.read(3);
        gain = pregain/10;
        initial_motor_speed = EEPROM.read(4);
        delay(50);

    }
}
void led_init(){
            // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("STEV-EEEEE");
  display.display();
  delay(50);
new_screen = true;

}
// #define Total_eles

// int index = 0;
// void addVar(string var, int value){
//     vars.push_back(var);
// }