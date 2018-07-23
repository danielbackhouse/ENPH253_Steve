void sensors(States stat){
    switch(stat){
        case FirstEwok:
            tape_sensors(stat);
            stop_sensors(stat);
            break;

        case FirstGap:
            tape_sensors(stat);
            stop_sensors(stat);
            break;
        case ThirdEwok:
            tape_sensors(stat);
            break;

        case SecondEwok:
          stop_sensors(stat);
          tape_sensors(stat);
          break;
        default:
          break;

    }

}

void stop_sensors(States stat){
    switch(stat){
        case FirstEwok:

          if(!digitalRead(RIGHT_CLAW)){
              end_moving();
              rightClawGrab();
              delay(10);
              resetBothDist();
              state = FirstGap;
              //resetSlave();
              Serial1.println("Grabbed ewok");
          }
           else if((analogRead(EDGE_DETECT) > EDGE_THRESHOLD) && (analogRead(MIDDLE_LEFT_QRD) > EDGE_THRESHOLD) ){
              end_moving();
              firstGap();
              dropPlate();
              //resetSlave();
              //   pwmWrite(left_mf, slow_speed+500);
              // pwmWrite(left_mb, 0);
              // pwmWrite(right_mf, slow_speed+500);
              // pwmWrite(right_mb, 0);
              // delay(5000);


              state = Stop;
              Serial1.println("Stopping!!");
          }
                break;
            // Serial1.println("starting");
             //Serial1.println("ending");
             //state = SecondEwok;
          case FirstGap:
            Serial1.println("First gap");
              if(analogRead(EDGE_DETECT) > EDGE_THRESHOLD ){
              end_moving();
              firstGap();
              Serial1.println("Gapping");
              delay(500);

              dropPlate();

              raiseLeftArm();

              //Serial1.println("Dropping duh plate");
              //resetSlave();
              pwmWrite(left_mf, slow_speed);
              pwmWrite(left_mb, 0);
              pwmWrite(right_mf, slow_speed);
              pwmWrite(right_mb, 0);
              delay(200);
              // pwmWrite(left_mf, slow_speed+500);
              // pwmWrite(left_mb, 0);
              // pwmWrite(right_mf, 0);
              // pwmWrite(right_mb, 0);
              // delay(1000);
              // end_moving();
              bool foundTape = false;
              bool once = false;
              while(!foundTape){
                if(!once){
                once = isTape(stat);

                }
                else{
                  foundTape = isTape(stat);
                }
              
                delay(10);
              }

              //end_moving();
              state = SecondEwok;
              initial_motor_speed = s_initial_motor_speed;
               reset_error();

              }
              
               break;
            case SecondEwok:
                if(!digitalRead(RIGHT_CLAW)){
                    end_moving();
                    rightClawGrab();
                    delay(10);
                    resetBothDist();
                    state = FirstGap;
                    //resetSlave();
                    Serial1.println("Grabbed ewok");
                    state = Stop;
                }
                
                break;
            default:
              end_moving();
              break;
                    }
    }

bool isTape(States stat){
  int digitalLeft = 1;
  int digitalRight = 1;
  if(stat != 99){
    left_qrd = analogRead(INITIAL_LEFT_QRD);
    right_qrd = analogRead(INITIAL_RIGHT_QRD);
  }
    if(left_qrd > QRD_TRHESHOLD_TAPE){
      return true;
  }
  if(right_qrd > QRD_TRHESHOLD_TAPE){
return true;  
}

return false;
}

void tape_sensors(States stat) {


  //negative PID_value <-- left motor speed increase, right motor speed decrease
  //positive PID_value <-- right motor speed increase, left motor speed decrease

  int digitalLeft = 1;
  int digitalRight = 1;
  if(stat != ThirdEwok){
    left_qrd = analogRead(INITIAL_LEFT_QRD);
    right_qrd = analogRead(INITIAL_RIGHT_QRD);
  }
  else{
    left_qrd = analogRead(MIDDLE_LEFT_QRD);
    right_qrd = analogRead(MIDDLE_RIGHT_QRD);
  }

  if(left_qrd < QRD_TRHESHOLD_TAPE){
    digitalLeft = 0;
  }
  if(right_qrd < QRD_TRHESHOLD_TAPE){
    digitalRight = 0;
  }


  //concating sensor readings together
  int readings = digitalLeft * 10 + digitalRight;
  if (readings != 0)
    previous = readings;
  
  switch (readings) {

    case 1:
      error = 1;
      break;
    case 11:
      error = 0;
      break;

    case 10:
      error = -1;
      break;    
      case 0:
      if (previous == 1) 
        error = 2;
      else if (previous == 10)
        error = -2;
      else
        error = 0;
       break;
  }
 }


bool firstGapAlign(int scenario){
  if(scenario == 1){
    int digitalLeft = 1;
    int digitalRight = 1;
    bool atEdge = false;

    left_qrd = analogRead(MIDDLE_LEFT_QRD);
    right_qrd = analogRead(MIDDLE_RIGHT_QRD);

    if(left_qrd < EDGE_THRESHOLD){
      digitalLeft = 0;
    }
    if(right_qrd < EDGE_THRESHOLD){
      digitalRight = 0;
    }

    if(digitalLeft && digitalRight){
        atEdge = true;
    }
      return atEdge;
    }

    else if(scenario == 2){
       if(analogRead(EDGE_DETECT) < EDGE_THRESHOLD){
         return true;
     }
      return false;

}
}