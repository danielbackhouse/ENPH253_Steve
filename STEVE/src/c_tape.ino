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
    read_sensor_values();
    calculate_pid();
    motor_control();
}

void read_sensor_values() {


  //negative PID_value <-- left motor speed increase, right motor speed decrease
  //positive PID_value <-- right motor speed increase, left motor speed decrease

  int digitalLeft = 1;
  int digitalRight = 1;
  int left_qrd = analogRead(LEFT_QRD);
  int right_qrd = analogRead(RIGHT_QRD);
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
        error = 4;
      else if (previous == 10)
        error = -4;
      else
        error = 0;
       break;
  }
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
  

  if(left_motor_speed < 0){
      left_motor_speed = -left_motor_speed;
      l_forward = false;
  }
  if (left_motor_speed > max_PWM){
    left_motor_speed = max_PWM;
  }
  if(left_motor_speed < 0){
    right_motor_speed = -right_motor_speed;
    r_forward = false;
  }
  if (right_motor_speed > max_PWM){
    right_motor_speed = max_PWM;
  }

  
  //give motor its speed
    if(l_forward == true){
        pwmWrite(left_mf, left_motor_speed);
        pwmWrite(left_mb, 0);
    }
    else{
        pwmWrite(left_mb, left_motor_speed);
        pwmWrite(left_mf, 0);
    }
    if(r_forward == true){
        pwmWrite(right_mf, right_motor_speed);
        pwmWrite(right_mb, 0);
    }
    else{
        pwmWrite(right_mb, right_motor_speed);
        pwmWrite(right_mf, 0);
    }
}