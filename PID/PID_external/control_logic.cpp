#define MIN_LENGTH (5)
int is_heading_to_home = 0;
int collision_finished = 0;

bool is_collision_finished(int length) {
    if (length <= minlength) return true;
    else return false;
}

void loop(){
    int message = get_message_from_openmv();
    int length = sonar.distanceCM();

    if (collision_finished == true && is_heading_to_home == true) return;
    else if (collision_finished == true && is_heading_to_home == false) {
        // control car to move backward();
        //连续运行control_car_to_back_off一段时间
    }

    switch(message) {
        case 1001:
            // control car to spin
            break;
        case 1002:
            is_heading_to_home = 1;
            // control car to spin();
            break;
        default:
            get_expected_velocity(mesasge, length);
            OnTime();
            break;
    }
}