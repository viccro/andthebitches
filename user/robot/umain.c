#include <joyos.h>
#include <math.h>
#include "vector_math.h"
#include "spare_parts.h"

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

//Preset Globals
uint8_t team_number[2] = {1,0};
<<<<<<< HEAD
int min_speed = 50; // ??????????????????????

=======
>>>>>>> 65fa036d13420ffef99d8948faf8d33b22f7eed8
extern volatile uint8_t robot_id; 
uint8_t next_point_x;
uint8_t next_point_y;

//Our Global Variables////////////
int is_nav_challenge = 1;
float kp_fwd=.05;
float kp_turn=.12;
//////////////////////////////////

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
	else if (speed < min_speed && speed > 0)
		return min_speed;
	else
		return velocity;
}

int turn_to_heading(void){
	
	copy_objects();
	float desired_heading=atan((game.coords[1].y-game.coords[0].y)/(game.coords[1].x-game.coords[0].x));
	if (game.coords[1].y>game.coords[0].y && desired_heading<0){	//quadrant 2
		desired_heading+=PI;
	}
	else if (game.coords[1].y<game.coords[0].y && desired_heading>0){	//quadrant 3
		desired_heading-=PI;
	}
	desired_heading*=ANGLE_FACTOR;
	//printf("desired heading %.3f\n", desired_heading);
	int actual_heading=game.coords[0].theta;
	//printf("actual heading %d\n", actual_heading);
	float error_angle = desired_heading-actual_heading;	
	//printf("error_angle %.3f\n",error_angle);
	int controller_output;
	if (abs(error_angle)<10){
		controller_output=0;}
	else controller_output= (int)(kp_turn*error_angle);
	//printf("controller_output: %d\n",controller_output);
	motor_set_vel(5, limitVelocity(controller_output));	
    return ((desired_heading - actual_heading) > 20);
}

int straight_to_heading(void){
	copy_objects();
	float x_now = game.coords[0].x;
	float y_now = game.coords[0].y;
	float x_new = game.coords[1].x;
	float y_new = game.coords[1].y;
	float x_diff_squared = pow((x_new-x_now),2);
	float y_diff_squared = pow((y_new-y_now),2);
	float error_distance = sqrt(x_diff_squared + y_diff_squared);
	int error_velocity = (int) (kp_fwd*error_distance);
	//printf("error_velocity: %d\n",error_velocity);
	motor_set_vel(4,limitVelocity(error_velocity));
    return (error_distance < 10);
}

void reorient_and_drive(void){
	copy_objects();
	//printf("%d is x_new, %d is y_new, %d is x_goal, %d is y_goal, %d is current_heading",game.coords[0].x,game.coords[0].y,game.coords[1].x,game.coords[1].y,game.coords[0].theta);
	
    while (turn_to_heading()){      //Turn first
    }
	//printf("%d is x_new, %d is y_new, %d is x_goal, %d is y_goal, %d is current_heading",game.coords[0].x,game.coords[0].y,game.coords[1].x,game.coords[1].y,game.coords[0].theta);
	while(1) {                      //Then go straight, with corrections if necessary
    straight_to_heading();
    turn_to_heading();
	}
}

void pick_next_point(void)
{
if (is_nav_challenge == 1)
    {
    next_point_x = game.coords[1].x;
    next_point_y = game.coords[1].y;
    }
else
    {
    next_point_x = 1;       //FIX THIS
    next_point_y = 1;       //FIX THIS
    }
}


void vector_driving(void)
{
    pick_next_point();
    vector curr = {cos(game.coords[0].theta), sin(game.coords[0].theta), 0};
    vector error = {(next_point_x - game.coords[0].x),(next_point_y - game.coords[0].y),0};
    float error_mag = fmaxf(error.i,error.j);
    vector error_norm = {error.i / error_mag, error.j / error_mag, 0};
    int v_fwd = (int) (dotProduct(curr, error) * kp_fwd);
    int v_turn = 0;         // avoid divide-by-zero
    if (error_mag > 1) 
        v_turn = (int) (crossProduct(curr, error_norm).k * kp_turn);

    motor_set_vel(4,limitVelocity(v_fwd));         //Straight motor
	printf("v_fwd: %i\n",v_fwd);
    motor_set_vel(5,limitVelocity(v_turn));         //Turn motor
	printf("v_turn: %i\n",v_turn);

//    sleep(.01);
}



// Entry point to contestant code.
void umain (void) {

    while(1){
    vector_driving();
    delay(10);
    }
    // Will never return, but the compiler complains without a return
    // statement.
//    return 0;
}
