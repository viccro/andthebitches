#include <joyos.h>

uint8_t team_number[2] = {1,0};
extern volatile uint8_t robot_id; 

int usetup (void) {
	robot_id = 1;
    return 0;
}

int umain (void) {
	while(1) {
	copy_objects();  
	printf("X position is %d \t \t Y position is %d \n", game.coords[0].x, game.coords[0].y);
	servo_set_pos(0,225);
	servo_set_pos(1,475);
	pause(2000);
	servo_set_pos(0,500);
	servo_set_pos(1,200);
	pause(2000);
	}
	//servo_set_pos(0,256);
	//servo_set_pos(1,256);
	//pause(1000);
	//servo_set_pos(0,300);
	//servo_set_pos(1,300);
	//pause(1000);
	//servo_set_pos(0,256);
	//servo_set_pos(1,256);
	//pause(1000);
	return 0;
}
