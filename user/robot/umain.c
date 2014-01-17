#include <joyos.h>
#include <math.h>

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

uint8_t team_number[2] = {1,0};
extern volatile uint8_t robot_id;


extern volatile uint8_t robot_id; 

// usetup is called during the calibration period. 

int usetup (void) {
	robot_id = 1;
    return 0;
}

int limitVelocity(int velocity) {
	int speed = abs(velocity);
	if(speed > 255) 
		return 255*(velocity/speed);
	else if (speed < 0)
		return 0;
	else
		return velocity;
}

int turn_to_heading(void){
	copy_objects();
	float kp= .11;
	float desired_heading=atan((game.coords[1].y-game.coords[0].y)/(game.coords[1].x-game.coords[0].x));
	if (game.coords[1].y>game.coords[0].y && desired_heading<0){//quadrant 2
		desired_heading+=PI;}
	else if (game.coords[1].y<game.coords[0].y && desired_heading>0){//quadrant 4
		desired_heading-=PI;}
	desired_heading*=ANGLE_FACTOR;
	int actual_heading=game.coords[0].theta;
	float error_angle = desired_heading-actual_heading;
	int controller_output= (int)kp*error_angle;
	
	motor_set_vel(1, limitVelocity(controller_output));
    return ((desired_heading - actual_heading) > 40);
}

int straight_to_heading(void){
	copy_objects();
	int kp = 0.01;
	float x_now = game.coords[0].x;
	float y_now = game.coords[0].y;
	float x_new = game.coords[1].x;
	float y_new = game.coords[1].y;
	float x_diff_squared = pow((x_new-x_now),2);
	float y_diff_squared = pow((y_new-y_now),2);
	float error_distance = sqrt(x_diff_squared + y_diff_squared);
	int error_velocity = (int) kp*error_distance;
		
	motor_set_vel(0,limitVelocity(error_velocity));
    return (error_distance < 10);
}

void reorient_and_drive(void){
    while (turn_to_heading()){      //Turn first
    }
	while(1) {                      //Then go straight, with corrections if necessary
    straight_to_heading();
    turn_to_heading();
	}
}


// Entry point to contestant code.
int umain (void) {

    while(1){
    reorient_and_drive();
    }

    // Will never return, but the compiler complains without a return
    // statement.
    return 0;
}
