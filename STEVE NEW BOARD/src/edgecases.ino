void firstGap(){
    bool atEdge = false;
    pwmWrite(left_mf, 0);
    pwmWrite(left_mb, slow_speed);
    pwmWrite(right_mf, 0);
    pwmWrite(right_mb, slow_speed);
    Serial.println("At first gap");
    delay(50);
    end_moving();
    while(!atEdge){
        atEdge = firstGapAlign(1);
        //goForward();  //with encoders
        pwmWrite(left_mf, 0);
        pwmWrite(left_mb, 0);
        pwmWrite(right_mf, slow_speed);
        pwmWrite(right_mb, 0);
    }
        end_moving();
    pwmWrite(left_mf, 0);
    pwmWrite(left_mb, 0);
    pwmWrite(right_mf, 0);
    pwmWrite(right_mb, slow_speed);
    delay(50);
    end_moving();

    Serial.println("Far enough");
    atEdge = false;
    while(!atEdge){
        atEdge = firstGapAlign(2);
        pwmWrite(left_mb, slow_speed+500);
        pwmWrite(left_mf, 0);
        pwmWrite(right_mf, 0);
        pwmWrite(right_mb, 0);
    }
    end_moving();
    pwmWrite(left_mf, slow_speed);
    
    atEdge = false;
    Serial.println("At first gap");
    delay(50);
    // while(!atEdge){
    //     atEdge = firstGapAlign(1);
    //     //goForward();  //with encoders
    //     pwmWrite(left_mf, 0);
    //     pwmWrite(left_mb, 0);
    //     pwmWrite(right_mf, slow_speed+500);
    //     pwmWrite(right_mb, 0);
    // }
    //     end_moving();
    //     pwmWrite(left_mf, 0);
    //     pwmWrite(left_mb, 0);
    //     pwmWrite(right_mf, 0);
    //     pwmWrite(right_mb, 0);
    //     delay(50);
        end_moving();
        resetBothDist();
        getPos();
        while(right_pos < 10 && left_pos < 10){
            getPos();

            if(left_pos < 10){
                pwmWrite(left_mb, slow_speed);
            }
            else{
                pwmWrite(left_mb, 0);
                pwmWrite(left_mf, 1000);
            }
            if(right_pos < 10){
                pwmWrite(right_mb, slow_speed);
            }
            else{
                pwmWrite(right_mb, 0);
                pwmWrite(right_mf, 1000);
            }
        }
        
        Serial.println("stop movement");
        end_moving();
        delay(100);


}

void crossFirstBridge(States stat){
    Serial.println("crossing first gap");
    resetBothDist();
    lastTime = millis();
    getPos();
    while(right_pos < 50 && left_pos < 60){
        sensors(JustTape);
        pid();
        Serial.println("Daniel!");
        timeIs = millis();
        if(timeIs > (lastTime + 100)){
            lastTime = millis();
            getPos();
        }

        
    }
    Serial.println("Jeremy!");
    end_moving();
    //delay(1000);
    lastTime = millis();
    
    resetBothDist();
    getPos();
    while(right_pos < 30 || left_pos < 40){
        if(left_pos< 40){
            pwmWrite(left_mf, slow_speed);
            pwmWrite(left_mb, 0);
        }
        else{
            pwmWrite(left_mb, 1000);
            pwmWrite(left_mf, 0);
        }
        if(right_pos< 30){
            pwmWrite(right_mf, slow_speed);
            pwmWrite(right_mb, 0);
        }
        else{
            pwmWrite(right_mb, 1000);
            pwmWrite(right_mf, 0);
        }

        timeIs = millis();
        if(timeIs > (lastTime + 50)){
            lastTime = millis();
            getPos();
        }
    }
    
    end_moving();
    delay(50);
    state = SecondEwok;
    
    Serial.println("jeremy wiens1");
    //stat = state;
    bool skipSearch = false;
    lastTime = millis();
    resetBothDist();
     getPos();
    int initialTime = millis();
    timeIs = millis();
    while(!skipSearch && right_pos < 30 && (timeIs < (initialTime + 2000)) ){
        skipSearch = isTape(SecondEwok);
        pwmWrite(left_mf, 0);
        pwmWrite(left_mb, slow_speed);
        pwmWrite(right_mf,slow_speed);
        pwmWrite(right_mb, 0);
        timeIs = millis();
        if(timeIs > (lastTime + 50)){
                display.clearDisplay();
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.setCursor(0,0);
                display.println("HELOOOOOOO");
                display.display();
                //delay(1000);
            lastTime = millis();
            getPos();
        }
    }

    end_moving();
   // delay(1000);
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(WHITE);
            display.setCursor(0,0);
            display.println(skipSearch);
            display.display();
    end_moving();
    //delay(1000);
    lastTime = millis();
    resetBothDist();
    getPos();
    while(!skipSearch && left_pos < 75){
        skipSearch = isTape(SecondEwok);
        pwmWrite(left_mf, slow_speed);
        pwmWrite(left_mb, 0);
        pwmWrite(right_mf,0);
        pwmWrite(right_mb, slow_speed);
        timeIs = millis();
        if(timeIs > (lastTime + 50)){
            lastTime = millis();
            getPos();
        }
    }
    
    
    end_moving();
    //delay(1000);
}

bool secondRaise = false;
void claws(){
    if((right_pos > 65 || left_pos > 60 ) && firstRaise){
        firstRaise = false;
        end_moving();
        readyForTroopers();
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("through gap");
        display.display();
        secondRaise = true;
    }
    else if((right_pos > 250 || left_pos > 250) && secondRaise){
        secondRaise = false;
        end_moving();
        readyForThirdEwok();
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("overstorm  troopers");
        display.display();

    }
    
}

void reposition() {
    int rightTurnDist = 30;
    int leftTurnDist = 20;
    int backUpDist = 5;
    resetBothDist();
    while(right_pos < backUpDist && left_pos < backUpDist){   //check reverse distances here!
            getPos();

            if(left_pos < backUpDist){
                pwmWrite(left_mb, slow_speed);
            }
            else{
                pwmWrite(left_mb, 0);
                pwmWrite(left_mf, 1000);
            }
            if(right_pos < backUpDist){
                pwmWrite(right_mb, slow_speed);
            }
            else{
                pwmWrite(right_mb, 0);
                pwmWrite(right_mf, 1000);
            }
        }

    resetBothDist();
    while(right_pos < rightTurnDist || left_pos < leftTurnDist){

        if(left_pos < leftTurnDist){
            pwmWrite(left_mf, slow_speed/2);
            pwmWrite(left_mb, 0);
        }
        else{
            pwmWrite(left_mb, 1000);
            pwmWrite(left_mf, 0);
        }
        if(right_pos < rightTurnDist){
            pwmWrite(right_mb, slow_speed);
            pwmWrite(right_mf, 0);
        }
        else{
            pwmWrite(right_mb, 0);
            pwmWrite(right_mf, 1000);
        }
    }

    while (!digitalRead(RIGHT_BUMPER) && !digitalRead(LEFT_BUMPER)){
        pwmWrite(right_mb, slow_speed);
        pwmWrite(right_mf, 0);
        pwmWrite(left_mb, slow_speed);
        pwmWrite(left_mf, 0);

        if (!digitalRead(RIGHT_BUMPER)){
            pwmWrite(left_mb, slow_speed);
            pwmWrite(left_mf, 0);
            pwmWrite(right_mb, 0);
            pwmWrite(right_mf, 1000);
        }

        if (!digitalRead(LEFT_BUMPER)){
            pwmWrite(left_mb, 0);
            pwmWrite(left_mf, 1000);
            pwmWrite(right_mb, slow_speed);
            pwmWrite(right_mf, 0);
        }
    }

}