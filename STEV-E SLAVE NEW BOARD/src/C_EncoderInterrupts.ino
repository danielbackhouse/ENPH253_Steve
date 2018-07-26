void right_interrupt()
{ 
    right_count++;
    if (right_count == 4){
        right_pos++;
        right_count = 0;
    }
}
void left_interrupt()
{

    left_count++;
    if (left_count == 4){
        left_pos++;
        left_count = 0;
    }
}

double getRightDistance() {
    return right_dist;
}

void resetRightDist() {
    right_pos = 0;
    right_dist = 0;
}

void resetLeftDist() {
    left_pos = 0;
    left_dist = 0;
}