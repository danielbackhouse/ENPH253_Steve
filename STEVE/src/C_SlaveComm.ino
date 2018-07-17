// initiate slave trigs

const int plate_drop_trig = 1;
const int right_claw_pick_up_trig = 2;
const int right_claw_lift_trig = 3;
const int left_claw_pick_up_trig = 4;
const int left_claw_lift_trig = 5;
const int bucket_trig = 6;
const int lift_both_claws = 7;

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