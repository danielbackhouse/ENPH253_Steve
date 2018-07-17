void sensors(States stat){
    switch(stat){
        case FirstEwok:
            tape_sensors(stat);
            stop_sensors(stat);
            break;
        case ThirdEwok:
            tape_sensors(stat);
            break;
        default:
          break;

    }

}

void stop_sensors(States stat){
    switch(stat){
        case FirstEwok:
        if(digitalRead(RIGHT_CLAW)){

            end_moving();
            //right_claw_grab();
            delay(1000);
            state = FirstGap;
        }
         if(analogRead(EDGE_DETECT) > EDGE_THRESHOLD){
             end_moving();
             state = Stop;
             //drop_plate();
             //state = SecondEwok;
             break;
         }
    }
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
