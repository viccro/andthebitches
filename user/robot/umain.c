#include <joyos.h>
#include <math.h>

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

uint8_t team_number[2] = {1,0};
extern volatile uint8_t robot_id;

int usetup (void) {
	robot_id = 1;
    return 0;
}
int limitVelocity(int velocity) {
	int speed = abs(velocity);
	if(speed > 255 && velocity>0){ 
		return 255;}
	else if (speed>255 && velocity<0){
		return -255;}
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
	int error = desired_heading-actual_heading;
	float controller_output= (int)kp*error;
	
	motor_set_vel(1, limitVelocity(controller_output));
	return 0;
}
int umain (void) {
	
    while (1){
		
	}
    return 0;
}
