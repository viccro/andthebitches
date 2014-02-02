#include <joyos.h>
#include <math.h>

int usetup (void) {
	robot_id = 1;
    return 0;
}

// Entry point to contestant code.
int umain (void) {
while (1)
    {
	motor_set_vel(4, 10);	
    }
}
