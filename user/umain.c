/*
 * The MIT License
 *
 * Copyright (c) 2007 MIT 6.270 Robotics Competition
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

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


