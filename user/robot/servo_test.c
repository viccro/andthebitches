#include <joyos.h>

uint8_t team_number[2] = {1,0};

int usetup (void) {
    return 0;
}

int umain (void) {
	while(1) {
	servo_set_pos(0,200);
	servo_set_pos(1,200);
	pause(1000);
	servo_set_pos(0,256);
	servo_set_pos(1,256);
	pause(1000);
	servo_set_pos(0,300);
	servo_set_pos(1,300);
	pause(1000);
	servo_set_pos(0,256);
	servo_set_pos(1,256);
	pause(1000);
	}
	return 0;
}
