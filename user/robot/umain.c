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

/////Our Global Variables////////////
int is_nav_challenge = 0;
float kp_fwd=.1;
float kp_turn=.05;

int next_point_x;
int next_point_y;
point next_point;
char side;

bool accomplished_corner = false;
bool accomplished_goal   = false;
point red_goal      = { 1730, 1355};
point red_waypoint  = {-1200, 1200};
point blue_goal     = { 1730,-1195};
point blue_waypoint = {-1200, 1200};

///////Parameters/////////////////
int buffer_around_waypoint   = 127;   // ~3 inches
int buffer_around_goal       = 75;    //~2 inches
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

void flip_flag_waypoint(void)
{
    point current_point = {game.coords[0].x,game.coords[0].y};
    if (dist_sqd(current_point,next_point) < (buffer_around_waypoint * buffer_around_waypoint))
    {
        accomplished_corner = true;
    }
}

void flip_flag_goal(void)
{
    point current_point = {game.coords[0].x,game.coords[0].y};
    if (dist_sqd(current_point,next_point) < (buffer_around_goal * buffer_around_goal))
    {
        accomplished_goal = true;
    }
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

    motor_set_vel(4,limitVelocity(v_fwd));         //Straight motor //	printf("v_fwd: %i, ",v_fwd);
    motor_set_vel(5,limitVelocity(v_turn));         //Turn motor    //	printf("v_turn: %i",v_turn);
    return ok;
}

void umain (void) {
	copy_objects();
	if (game.coords[0].y > 0) {
        side = 'r';
		printf("ON RED SIDE, BITCHES!!!!\n");
	}

    else {
        side = 'b';
		printf("ON BLUE SIDE, MOTHERFUCKERS!!!!\n");
	}
	
    printf("Start driving to waypoint\n");

    while((vector_driving() == ok) && (accomplished_corner = false))
    {
        copy_objects();      //		printf("goal x = %d, goal y = %d\t\t", next_point_x, next_point_y);        
        flip_flag_waypoint();
        delay(500);          //printf("\t\tcurrent_point_x: %i, current_point_y: %i, current_heading: %i, \n",game.coords[0].x,game.coords[0].y,game.coords[0].theta);
    }

    printf("Start driving to goal\n");

    while((vector_driving() == ok) && (accomplished_goal = false))
    {
        copy_objects();     
        flip_flag_goal();
        delay(500);
    }    
        printf("waiting to push some shit\n");
    while 1
    {}

    printf("Yep, everything has failed. Sucks.\n");
}
