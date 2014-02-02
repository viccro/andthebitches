#include <joyos.h>
#include <math.h>
#include "vector_math.h"
#include "spare_parts.h"
#include <stdio.h>
//#include "log.h"
//#include "path_plan.h"

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

//Preset Globals
uint8_t team_number[2] = {1,0};
int min_speed = 50; // ??????????????????????
extern volatile uint8_t robot_id; 

/////Our Global Variables////////////
int is_nav_challenge = 0;
float kp_fwd=.1;
float kp_turn=.05;

int next_point_x;
int next_point_y;
//point next_point;
char side;

bool accomplished_corner = false;
bool accomplished_goal   = false;
bool straight_ahead = false;
int red_goal_x = 1400;
int red_goal_y = 1400;
int red_waypoint_x = -1100;
int red_waypoint_y = 1100;
int blue_goal_x = 1400;
int blue_goal_y = -1400;
int blue_waypoint_x = -1100;
int blue_waypoint_y = -1100;


///////Parameters/////////////////
int buffer_around_waypoint   = 120;   // ~3 inches
int buffer_around_goal       = 42;    //~2 inches
int buffer_theta 			 = 20;
//////////////////////////////////

// usetup is called during the calibration period. 
int usetup (void) {
	robot_id = 1;
	servo_set_pos(0,225);       //Raise the lever-pushing arm
	servo_set_pos(1,475);
    return 0;
}

//  limitVelocityROT: int -> int
//  Ensures that the robot is not exceeding practical physical 
//      limits on rotational velocity
int limitVelocityROT(int velocity) {
	int speed = abs(velocity);
	if(speed > 200) 
		return 200*(velocity/speed);
	else if (speed < 0)
		return 0;
	else if (speed < min_speed && speed > 0)
		return min_speed;
	else
		return velocity;
}

//  limitVelocityFWD: int -> int
//  Ensures that the robot is not exceeding practical physical 
//      limits on forward velocity
int limitVelocityFWD(int velocity) {
	int speed = abs(velocity);
	if(speed > 200) 
		return 200*(velocity/speed);
	else if (speed < 0)
		return 0;
	else if (speed < 125 && speed > 0)
		return 125*(velocity/speed);
	else
		return velocity;
}

//  where_to: void -> int
//  Determines the next waypoint, from a list of four possibilities 
int where_to(void)
{
    if ((accomplished_corner == true) && (side == 'r'))
    {
        next_point_x = red_goal_x;
		next_point_y = red_goal_y;
        //printf("next_point: red_goal, %i, %i\n",next_point_x,next_point_y);
        return ok;
    }
    else if ((accomplished_corner == true) && (side == 'b'))
    {
        next_point_x = blue_goal_x;
		next_point_y = blue_goal_y;
        //printf("next_point: blue_goal, %i, %i\n",next_point_x,next_point_y);
        return ok;
    }
    else if ((accomplished_corner == false) && (side == 'r'))
    {
        next_point_x = red_waypoint_x;
		next_point_y = red_waypoint_y;
        //printf("next_point: red_wp, %i, %i\n",next_point_x,next_point_y);
        return ok;
    }
    else if ((accomplished_corner == false) && (side == 'b'))
    {
        next_point_x = blue_waypoint_x;
		next_point_y = blue_waypoint_y;
        //printf("next_point: blue_wp, %i, %i\n",next_point_x,next_point_y);
        return ok;
    }
    return error;
}

//  check_flag_waypoint: void -> void
//  Have we gotten to the waypoint?
void check_flag_waypoint(void)
{
    if (dist(game.coords[0].x, game.coords[0].y, next_point_x, next_point_y) < (buffer_around_waypoint))
    {
        accomplished_corner = true;
    }
	//printf("Accomplished waypoint: %d", accomplished_corner);
}

//  check_flag_goal: void -> void
//  Have we gotten to the goal?
void check_flag_goal(void)
{
    //point current_point = {game.coords[0].x,game.coords[0].y};
    //printf("dist to goal: %i\n",dist(game.coords[0].x, game.coords[0].y, next_point_x, next_point_y));
    if (dist(game.coords[0].x, game.coords[0].y, next_point_x, next_point_y) < (buffer_around_goal))
    {
        accomplished_goal = true;
    }
	//printf("Accomplished goal: %d", accomplished_goal);
}

//  check_flag_straght: void -> void
//  Are we facing the lever straight on?
void check_flag_straight(void)
{
    //point current_point = {game.coords[0].x,game.coords[0].y};
    //printf("dist to goal: %i\n",dist(game.coords[0].x, game.coords[0].y, next_point_x, next_point_y));
    if (abs(0-game.coords[0].theta) < (buffer_theta))
    {
        straight_ahead = true;
    }
}

//  vector_driving: void -> int
//  Uses where_to to choose a point to go to, and finds the component vectors from our current heading,
//      as well as those of our error, to calculate forward and rotational motors
//      The dot product of these vectors is proportional to the fwd velocity, and the cross product is related
//      to our rotational velocity
int vector_driving(void)
{
    if (where_to() == error)    //Did where_to fail?
    {
        motor_set_vel(4,0);         //Straight motor stopped
        motor_set_vel(5,0);         //Turning motor stopped
    	printf("Dear god, what have you done?\n");
        return error;
    }   
    vector curr = {cos(game.coords[0].theta/ANGLE_FACTOR), sin(game.coords[0].theta/ANGLE_FACTOR), 0};

    vector error = {(next_point_x - game.coords[0].x),(next_point_y - game.coords[0].y),0};
    float error_mag = fmaxf(error.i,error.j);           //That's totally legit, right?
    vector error_norm = {error.i / error_mag, error.j / error_mag, 0};

    int v_fwd = (int) (dotProduct(curr, error) * kp_fwd);
    int v_turn = (int) (crossProduct(curr, error_norm).k * kp_turn * ANGLE_FACTOR);

    motor_set_vel(4,limitVelocityFWD(v_fwd));           //Straight motor	
	//printf("v_fwd: %i, ",v_fwd);
    motor_set_vel(5,limitVelocityROT(v_turn));          //Rotation motor    	
	//printf("v_turn: %i",v_turn);
    return ok;
}

int vector_spinning(void)
{
	if (where_to() == error)    //Did where_to fail?
    {
        motor_set_vel(4,0);         //Straight motor stopped
        motor_set_vel(5,0);         //Turning motor stopped
    	printf("Dear god, what have you done?\n");
        return error;
    }   
	int kp_turn_spin = .08;
	int v_turn = (int) (kp_turn_spin * (0-game.coords[0].theta));
	motor_set_vel(5,limitVelocityROT(v_turn));
	return ok;
}

void umain (void) {
	copy_objects();                                                     //Get VPS data
	if (game.coords[0].y > 0) {                                         // Determines whether we are on the red side or blue side, based on starting position
        side = 'r';
		//printf("ON RED SIDE, BITCHES!!!!\n");
	}

    else {
        side = 'b';
		//printf("ON BLUE SIDE, MOTHERFUCKERS!!!!\n");
	}
	
    //printf("Driving to waypoint\n");                      

    while((vector_driving() == ok) && (accomplished_corner == false))   // Driving hasn't failed, and we're not at the waypoint yet.
    {
        copy_objects();                                                 // Get VPS data
        check_flag_waypoint();                                          // Did we hit the waypoint this time?
    }

    //printf("Driving to goal\n");

    while((vector_driving() == ok) && (accomplished_goal == false))
    {
        copy_objects();     
        check_flag_goal();
    }    

    //printf("Fixing heading to goal\n");

	while((vector_spinning() == ok) && (straight_ahead == false))
	{
		copy_objects();
		check_flag_straight();
	}

    //printf("Ready to push the lever\n");

    motor_set_vel(4,0);         //Straight motor stopped
    motor_set_vel(5,0);         //Turning motor stopped   


	//pause(5);
	
	while (1)                   //Press the lever repeatedly by raising and lowering the arm
	{
	servo_set_pos(0,500);
	servo_set_pos(1,200); 
	pause(750);
	servo_set_pos(0,225);
	servo_set_pos(1,475);
	pause(750);
	}
}
