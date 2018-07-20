void firstGap(){
    bool atEdge = false;
    pwmWrite(left_mf, 0);
    pwmWrite(left_mb, slow_speed);
    pwmWrite(right_mf, 0);
    pwmWrite(right_mb, slow_speed);
    Serial1.println("At first gap");
    delay(50);
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
    Serial1.println("Far enough");
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
    Serial1.println("At first gap");
    delay(50);
    while(!atEdge){
        atEdge = firstGapAlign(1);
        //goForward();  //with encoders
        pwmWrite(left_mf, 0);
        pwmWrite(left_mb, 0);
        pwmWrite(right_mf, slow_speed+500);
        pwmWrite(right_mb, 0);
    }
        end_moving();
        pwmWrite(left_mf, 0);
        pwmWrite(left_mb, 0);
        pwmWrite(right_mf, 0);
        pwmWrite(right_mb, slow_speed);
        delay(50);
        end_moving();
        resetBothDist();
        while(right_pos < 25 && left_pos < 25){
            if(left_pos < 25){
                pwmWrite(left_mb, slow_speed);
            }
            else{
                pwmWrite(left_mb, 0);
                pwmWrite(left_mf, 1000);
            }
            if(right_pos < 25){
                pwmWrite(right_mb, slow_speed);
            }
            else{
                pwmWrite(right_mb, 0);
                pwmWrite(right_mf, 1000);
            }
        }
        end_moving();

        // pwmWrite(left_mf, 0);
        // pwmWrite(left_mb, slow_speed+500);
        // pwmWrite(right_mf, 0);
        // pwmWrite(right_mb, slow_speed+500);
        // delay(350);
        // end_moving();
}