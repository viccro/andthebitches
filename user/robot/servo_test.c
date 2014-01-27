#include <joyos.h>

uint8_t team_number[2] = {1,0};

int usetup (void) {
    return 0;
}

int umain (void) {
	while(1) {
	servo_set_pos(0,100);
	pause(1000);
	servo_set_pos(0,256);
	pause(1000);
	servo_set_pos(0,400);
	pause(1000);
	servo_set_pos(0,256);
	pause(1000);
	}
	return 0;
}
