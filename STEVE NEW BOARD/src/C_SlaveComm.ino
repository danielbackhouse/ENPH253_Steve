// initiate slave trigs

const int plate_drop_trig = 14;
const int right_claw_pick_up_trig = 2;
const int ewok_2_pick_up_trig = 3;
const int left_claw_pick_up_trig = 4;
const int left_claw_lift_trig = 5;
const int bucket_trig = 6;
const int lift_left_claw_arch = 7;
const int ready_for_troopers = 8;
const int ready_for_third_ewok = 9;

const int reset_left = 11;
const int reset_right = 12;
const int reset_both = 13;

volatile int done = 0;
int wireTime;

//volatile bool done = false;

void readyForThirdEwok(){
  Wire.beginTransmission(4);
  Wire.write(ready_for_third_ewok);
  Wire.endTransmission();
  wireTime = millis();
  while (done != ready_for_third_ewok){
    sendAgain(ready_for_third_ewok, 200);
    delay(50);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = 0;
}


void readyForTroopers(){
  Wire.beginTransmission(4);
  Wire.write(ready_for_troopers);
  Wire.endTransmission();
  wireTime = millis();
  while (done != ready_for_troopers){
    delay(50);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      sendAgain(ready_for_troopers, 200);
      done = Wire.read();
    }
  }
  done = 0;

}

void dropPlate()
{
  Wire.beginTransmission(4);
  Wire.write(plate_drop_trig);
  Wire.endTransmission();
  Serial.println("sent info");
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  wireTime = millis();
  digitalWrite(LED_BUILTIN, HIGH);
  while (done != plate_drop_trig){
    sendAgain(plate_drop_trig, 200);
    delay(50);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = 0;
  Serial.println("dropped plate");
}
void rightClawGrab2(){
  Wire.beginTransmission(4);
  Wire.write(ewok_2_pick_up_trig);
  Wire.endTransmission();
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Picking up Ewok 2");

  wireTime = millis();
  while (done != ewok_2_pick_up_trig){
    sendAgain(ewok_2_pick_up_trig, 2000);
    delay(50);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = 0;
  Serial.println("Done");

}
void rightClawGrab(){
  Wire.beginTransmission(4);
  Wire.write(right_claw_pick_up_trig);
  Wire.endTransmission();
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Picking up thing");

  wireTime = millis();

  while (done != right_claw_pick_up_trig){
    sendAgain(right_claw_pick_up_trig, 3500);
    delay(50);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = 0;

}
void raiseLeftArm(){
  Wire.beginTransmission(4);
  Wire.write(lift_left_claw_arch);
  Wire.endTransmission();
  Serial.println("sent info");
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);
  wireTime = millis();
 // Serial.println("Picking up left arm");

  while (done != lift_left_claw_arch){
    sendAgain(lift_left_claw_arch, 1500);
    delay(100);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = 0;

}
void leftClawGrab(){
  Serial.println("grabbing 3rd ewok");
  Wire.beginTransmission(4);
  Wire.write(left_claw_pick_up_trig);
  Wire.endTransmission();
  Serial.println("sent to slave");
  delay(5);
  wireTime = millis();
  while (done != left_claw_pick_up_trig){
    sendAgain(left_claw_pick_up_trig, 4500);
    delay(100);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }

  Serial.println("done picking up");
  done = 0;

}

void bucketDump(){
  Wire.beginTransmission(4);
  Wire.write(bucket_trig);
  Wire.endTransmission();
  delay(5);
  wireTime = millis();

  while (done != bucket_trig){
    sendAgain(bucket_trig, 1200);
    delay(100);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = 0;
}

void getPos(){
  byte a, b, c, d, e, f, g, h;

  Wire.requestFrom(4, 8);
      a = Wire.read();
      b = Wire.read();
      c = Wire.read();
      d = Wire.read();
      e = Wire.read();
      f = Wire.read();
      g = Wire.read();
      h = Wire.read();
  left_pos = a;
  left_pos = (left_pos << 8) | b;
  left_pos = (left_pos << 8) | c;
  left_pos = (left_pos << 8) | d;

  right_pos = e;
  right_pos = (right_pos << 8) | f;
  right_pos = (right_pos << 8) | g;
  right_pos = (right_pos << 8) | h;
}

void resetRightDist(){
  Wire.beginTransmission(4);
  Wire.write(reset_right);
  Wire.endTransmission();
}

void resetLeftDist(){
  Wire.beginTransmission(4);
  Wire.write(reset_left);
  Wire.endTransmission();
}

void resetBothDist(){
  Wire.beginTransmission(4);
  Wire.write(reset_both);
  Wire.endTransmission();
}

void sendAgain(int trigger, int sendDelay) {
  if(millis() > (wireTime + sendDelay)){
  Serial.println("sending again");
  Wire.beginTransmission(4);
  Wire.write(trigger);
  Wire.endTransmission();
  wireTime = millis();
  }

}

void checkReceive(int trigger) {
  int receive = 0;
  while (receive == 0){
    Wire.beginTransmission(4);
    Wire.write(trigger);
    Wire.endTransmission();
    Wire.requestFrom(4, 1);
    delayMicroseconds(5);
    while (Wire.available()){
      receive = Wire.read();
    }
  }
}