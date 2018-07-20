// initiate slave trigs

const int plate_drop_trig = 1;
const int right_claw_pick_up_trig = 2;
const int right_claw_lift_trig = 3;
const int left_claw_pick_up_trig = 4;
const int left_claw_lift_trig = 5;
const int bucket_trig = 6;
const int lift_both_claws = 7;

const int reset_left = 11;
const int reset_right = 12;
const int reset_both = 13;

volatile bool done = false;

void dropPlate()
{
  Wire.beginTransmission(4);
  Wire.write(plate_drop_trig);
  Wire.endTransmission();
  while (done == false){
    delay(100);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = false;
}

void rightClawGrab(){
  Wire.beginTransmission(4);
  Wire.write(right_claw_pick_up_trig);

  Wire.endTransmission();
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
    digitalWrite(LED_BUILTIN, HIGH);

  Serial1.println("Picking up thing");

  while (done == false){
    delay(100);
    Wire.requestFrom(4, 1);
    while (Wire.available()){
      done = Wire.read();
    }
  }
  done = false;
  Serial1.println("Done");

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