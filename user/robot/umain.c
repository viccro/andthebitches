#include <joyos.h>
#include <math.h>
#include "vector_math.h"
#include "spare_parts.h"
#include <stdio.h>
//#include "path_plan.h"

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

//Preset Globals
uint8_t team_number[2] = {1,0};
extern volatile uint8_t robot_id; 


//Our Global Variables////////////
int is_nav_challenge = 0;
float kp_fwd=.1;
float kp_turn=.05;

int next_point_x;
int next_point_y;
point next_point;
char side;
//point point_list[18];
//int index_num;
bool accomplished_corner = false;
point red_goal      = { 1730, 1355};
point red_waypoint  = {-1200, 1200};
point blue_goal     = { 1730,-1195};
point blue_waypoint = {-1200, 1200};

enum COMPLETION {ok, error};      /* ok = 0, error = 1 */
//////////////////////////////////

// usetup is called during the calibration period. 
int usetup (void) {
	robot_id = 1;
    return 0;
}

int limitVelocity(int velocity) {
	int speed = abs(velocity);
	if(speed > 200) 
		return 200*(velocity/speed);
	else if (speed < 0)
		return 0;
	else if (speed < 75 && speed > 0)
		return 125*(velocity/speed);
	else
		return velocity;
}

int where_to(void)
{
    if ((accomplished_corner == true) && (side == 'r'))
    {
        next_point = red_goal;
        return ok;
    }
    else if ((accomplished_corner == true) && (side == 'b'))
    {
        next_point = blue_goal;
        return ok;
    }
    else if ((accomplished_corner == false) && (side == 'r'))
    {
        next_point = red_waypoint;
        return ok;
    }
    else if ((accomplished_corner == false) && (side == 'b'))
    {
        next_point = blue_waypoint;
        return ok;
    }
    return error;
}

int vector_driving(void)
{
    if (where_to() == error)
    {
        motor_set_vel(4,0);         //Straight motor stopped
        motor_set_vel(5,0);         //Turning motor stopped
    	printf("Dear god, what have you done?\n");
        return error;
    }   
    vector curr = {cos(game.coords[0].theta/ANGLE_FACTOR), sin(game.coords[0].theta/ANGLE_FACTOR), 0};
	next_point_x = next_point.x;
    next_point_y = next_point.y;

    vector error = {(next_point_x - game.coords[0].x),(next_point_y - game.coords[0].y),0};
    float error_mag = fmaxf(error.i,error.j); // Optimization? 
    vector error_norm = {error.i / error_mag, error.j / error_mag, 0};

    int v_fwd = (int) (dotProduct(curr, error) * kp_fwd);
    int v_turn = (int) (crossProduct(curr, error_norm).k * kp_turn * ANGLE_FACTOR);

    motor_set_vel(4,limitVelocity(v_fwd));         //Straight motor
//	printf("v_fwd: %i, ",v_fwd);
    motor_set_vel(5,limitVelocity(v_turn));         //Turn motor
//	printf("v_turn: %i",v_turn);
    return ok;
}

void umain (void) {
	copy_objects();
	if (game.coords[0].y > 0) {
//		build_list_o_points_red(point_list);
//		next_point_x = -1200;
//		next_point_y = 1200;
        side = 'r';
		printf("ON RED SIDE, BITCHES!!!!\n");
	}
    else {
//		build_list_o_points_blue(point_list);
//		next_point_x = -1200;
//		next_point_y = -1200;
        side = 'b';
		printf("ON BLUE SIDE, MOTHERFUCKERS!!!!\n");
	}
	
    while(vector_driving() == ok)
    {
        copy_objects();
        delay(500);

//		printf("goal x = %d, goal y = %d\t\t", next_point_x, next_point_y);        
        //printf("\t\tcurrent_point_x: %i, current_point_y: %i, current_heading: %i, \n",game.coords[0].x,game.coords[0].y,game.coords[0].theta);
    }

    printf("Yep, everything has failed. Sucks.\n");
}
