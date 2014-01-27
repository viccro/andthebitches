#include <joyos.h>
#include <math.h>
#include "vector_math.h"
#include "spare_parts.h"

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

//Preset Globals
uint8_t team_number[2] = {1,0};
extern volatile uint8_t robot_id; 


//Our Global Variables////////////
int is_nav_challenge = 0;
float kp_fwd=.05;
float kp_turn=.12;

int next_point_x = 0;
int next_point_y = 0;
int x_list[8] = { 1024,  2050, 1024,    0, -1024, -2050, -1024,     0};
int y_list[8] = {-1024,     0, 1024, 2050,  1024,     0, -1024, -2050};

//int red_goal_far[2]   = {x,y};
//int red_goal_near[2]  = {x,y};
//int blue_goal_far[2]  = {x,y};
//int blue_goal_near[2] = {x,y};
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
	else
		return velocity;
}
/*
int turn_to_heading(void){
	
	copy_objects();
	float desired_heading=atan((game.coords[1].y-game.coords[0].y)/(game.coords[1].x-game.coords[0].x));
	if (game.coords[1].y>game.coords[0].y && desired_heading<0){//quadrant 2
		desired_heading+=PI;}
	else if (game.coords[1].y<game.coords[0].y && desired_heading>0){//quadrant 3
		desired_heading-=PI;}
	desired_heading*=ANGLE_FACTOR;
	//printf("desired heading %.3f\n", desired_heading);
	uint8_t actual_heading=game.coords[0].theta;
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
	uint8_t error_velocity = (uint8_t) (kp_fwd*error_distance);
	//printf("error_velocity: %d\n",error_velocity);
	motor_set_vel(4,limitVelocity(error_velocity));
    return (error_distance < 10);
}

void reorient_and_drive(void){
	copy_objects();
	printf("%d is x_new, %d is y_new, %d is x_goal, %d is y_goal, %d is current_heading",game.coords[0].x,game.coords[0].y,game.coords[1].x,game.coords[1].y,game.coords[0].theta);
	
    while (turn_to_heading()){      //Turn first
    }
	printf("%d is x_new, %d is y_new, %d is x_goal, %d is y_goal, %d is current_heading",game.coords[0].x,game.coords[0].y,game.coords[1].x,game.coords[1].y,game.coords[0].theta);
	while(1) {                      //Then go straight, with corrections if necessary
    straight_to_heading();
    turn_to_heading();
	}
}
*/

void vector_driving(void)
{
    if (((game.coords[0].x - next_point_x) < 40) && ((game.coords[0].y - next_point_y) < 40))
    {
        next_point_x = pick_next_point_x(game.coords[1].x);
        next_point_y = pick_next_point_y(game.coords[1].y);
        printf("\n\n\nnext_point_x: %i, next_point_y: %i\n\n\n\n",next_point_x,next_point_y);
    }
        printf("\t\t\t\t\t\t\tcurrent_point_x: %i, current_point_y: %i\n\n",game.coords[0].x,game.coords[0].y);
    vector curr = {cos(game.coords[0].theta/ANGLE_FACTOR), sin(game.coords[0].theta/ANGLE_FACTOR), 0};
    vector error = {(next_point_x - game.coords[0].x),(next_point_y - game.coords[0].y),0};
    float error_mag = fmaxf(error.i,error.j);
    vector error_norm = {error.i / error_mag, error.j / error_mag, 0};
    uint8_t v_fwd = (uint8_t) (dotProduct(curr, error) * kp_fwd);
    uint8_t v_turn = 0;         // avoid divide-by-zero
    if (error_mag > 1) 
        v_turn = (uint8_t) (crossProduct(curr, error_norm).k * kp_turn);

    motor_set_vel(4,limitVelocity(v_fwd));         //Straight motor
	printf("v_fwd: %i",v_fwd);
    motor_set_vel(5,limitVelocity(v_turn));         //Turn motor
	printf("v_turn: %i",v_turn);

//    sleep(.01);
}



// Entry point to contestant code.
void umain (void) {

    while(1){
    copy_objects();
    vector_driving();
//    printf("\t\t\t\t\t\t\tcurrent_point_x: %i, current_point_y: %i, current_heading: %i, \n\n",game.coords[0].x,game.coords[0].y,game.coords[0].theta);
    delay(1000);
    }
    // Will never return, but the compiler complains without a return
    // statement.
//    return 0;
}
