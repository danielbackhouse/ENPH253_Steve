// #include <Arduino.h>
// #include <Tape.h>

// PID::PID()
// {
//     int x = 0;
// }
// int PID::high(pin){
//     digitalWrite(String pin, HIGH);
// }

// int PID::low(String pin){
//     digitalWrite(pin, LOW);
// }

void pid(){
    calculate_pid();
    motor_control();
}


  void calculate_pid() {

  P = error;
  I = I + error;
  D = error - previous_error;

//  Serial.print(P);
//  Serial.print("\t");
//  Serial.print(Kp);
//  Serial.print("\t");
//  Serial.print(D);
//  Serial.print("\t");
//  Serial.print(Kd);
//  Serial.print("\n");
//  Serial.print(PID_value);

  PID_value = gain*((Kp * P) + (Ki * I) + (Kd * D));

  previous_error = error;
}

void motor_control() {

  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed + PID_value;
  int right_motor_speed = initial_motor_speed - PID_value;
  bool l_forward = true;
  bool r_forward = true; 
  
 // Serial1.println(left_motor_speed);
    //Serial1.println(left_motor_speed);
  if(left_motor_speed < 0){
      left_motor_speed = -left_motor_speed;
      l_forward = false;
  }
  if (left_motor_speed > max_PWM){
    left_motor_speed = max_PWM;
  }
  if(right_motor_speed < 0){
    right_motor_speed = -right_motor_speed;
    r_forward = false;
  }
  if (right_motor_speed > max_PWM){
    right_motor_speed = max_PWM;
  }
    testVal = right_motor_speed;
  
 // delay(100);
  //give motor its speed
    if(l_forward == true){
        pwmWrite(left_mf, left_motor_speed);
        pwmWrite(left_mb, 0);
        // Serial1.print(left_motor_speed);
        // Serial1.println(" left");
    }
    else{
        pwmWrite(left_mb, left_motor_speed);
        pwmWrite(left_mf, 0);
        
    }
    if(r_forward == true){
        pwmWrite(right_mf, right_motor_speed);
        pwmWrite(right_mb, 0);
        //Serial1.print(right_motor_speed);
        // Serial1.println(" right");
    }
    else{
        //Serial1.print(right_motor_speed);

        pwmWrite(right_mb, right_motor_speed);
        pwmWrite(right_mf, 0);
        
    }
}