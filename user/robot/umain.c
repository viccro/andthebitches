#include <joyos.h>
#include <math.h>
#include "vector_math.h"
#include "spare_parts.h"
//#include "path_plan.h"

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
//int x_list[8] = { 1024,  2050, 1024,    0, -1024, -2050, -1024,     0};
//int y_list[8] = {-1024,     0, 1024, 2050,  1024,     0, -1024, -2050};
point point_list[18];
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


void vector_driving(void)
{
    if (((game.coords[0].x - next_point_x) < 40) && ((game.coords[0].y - next_point_y) < 40))
    {
        point p = pick_next_point();
        next_point_x = p.x;
        next_point_y = p.y;
        printf("\n\n\nnext_point_x: %i, next_point_y: %i\n\n\n\n",next_point_x,next_point_y);
    }
        printf("\t\t\t\t\t\t\tcurrent_point_x: %i, current_point_y: %i\n\n",game.coords[0].x,game.coords[0].y);
    vector curr = {cos(game.coords[0].theta/ANGLE_FACTOR), sin(game.coords[0].theta/ANGLE_FACTOR), 0};
    vector error = {(next_point_x - game.coords[0].x),(next_point_y - game.coords[0].y),0};
    float error_mag = fmaxf(error.i,error.j);
    vector error_norm = {error.i / error_mag, error.j / error_mag, 0};
    uint8_t v_fwd = (uint8_t) (dotProduct(curr, error) * kp_fwd);
    uint8_t v_turn;
//    uint8_t v_turn = 0;         // avoid divide-by-zero
//    if (error_mag > 1) 
    v_turn = (uint8_t) (crossProduct(curr, error_norm).k * kp_turn);

    motor_set_vel(4,limitVelocity(v_fwd));         //Straight motor
	printf("v_fwd: %i",v_fwd);
    motor_set_vel(5,limitVelocity(v_turn));         //Turn motor
	printf("v_turn: %i",v_turn);
}



// Entry point to contestant code.
void umain (void) {
    if (game.coords[0].y > 0)
        point_list = list_o_points_red;
    else 
        point_list = list_o_points_blue;

    while(1)
    {
        copy_objects();
        vector_driving();
    //    printf("\t\t\t\t\t\t\tcurrent_point_x: %i, current_point_y: %i, current_heading: %i, \n\n",game.coords[0].x,game.coords[0].y,game.coords[0].theta);
        delay(1000);
    }
    // Will never return, but the compiler complains without a return
    // statement.
//    return 0;
}
