void right_interrupt()
{ 
    right_count++;
    if (right_count == 4){
        right_pos++;
        right_count = 0;
    }
    // volatile static uint8_t r_state = 0;
    // r_state = (r_state << 2) & 0x0f;
    // r_state |= (digitalRead(ENCODE_RIGHT_WHEEL_A) << 1) | digitalRead(ENCODE_RIGHT_WHEEL_B);
    // switch (r_state)
    // {
    //     case 0x0d:
    //     right_pos++;
    //     break;
    //     case 0x0e:
    //     right_pos--;
    //     break;
    // }
 
    // rightArray[0] = (right_pos >> 24) & 0xFF;
    // rightArray[1] = (right_pos >> 16) & 0xFF;
    // rightArray[2] = (right_pos>> 8) & 0xFF;
    // rightArray[3] = right_pos & 0xFF;
}

void left_interrupt()
{

        left_count++;
    if (left_count == 4){
        left_pos++;
        left_count = 0;
    }
    // volatile static uint8_t l_state = 0;
    // l_state = (l_state << 2) & 0x0f;
    // l_state |= (digitalRead(ENCODE_LEFT_WHEEL_A) << 1) | digitalRead(ENCODE_LEFT_WHEEL_B);
    //     switch (l_state)
    //     {
    //         case 0x0d:
    //         left_pos++;
    //         break;
    //     case 0x0e:
    //     left_pos--;
    //     break;
    // }
    // leftArray[0] = (right_pos >> 24) & 0xFF;
    // leftArray[1] = (right_pos >> 16) & 0xFF;
    // leftArray[2] = (right_pos>> 8) & 0xFF;
    // leftArray[3] = right_pos & 0xFF;
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