// Include headers from OS
#include <joyos.h>

extern volatile uint8_t robot_id; 

// usetup is called during the calibration period. 
int usetup (void) {
	robot_id = 1;
    return 0;
}

int limitVelocity(int velocity) {

	int speed = abs(velocity);
	if(speed > 255) 
		return 255*(velocity/speed)
	else if (speed < 0)
		return 0;
	else
		return velocity;

}

int straight_to_heading(void){
	copy_objects();
	int kp = 0.01
	float x_now = game.coords[0].x;
	float y_now = game.coords[0].y;
	float x_new = game.coords[1].x;
	float y_new = game.coords[1].y;
	float x_diff_squared = pow((x_new-x_now),2);
	float y_diff_squared = pow((y_new-y_now),2);
	float error_distance = sqrt(x_diff_squared + y_diff_squared);
	int error_velocity = (int) kp*error_distance
		
	motor_set_vel(0,limitVelocity(error_velocity))
}

// Entry point to contestant code.
int umain (void) {
	while(1) {

	}

    // Will never return, but the compiler complains without a return
    // statement.
    return 0;
}
