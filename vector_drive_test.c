
#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

#include "src/inc/pgmspace.h"
//#include <unistd.h>
#define PROGMEM   __ATTR_PROGMEM__

typedef struct{
	float i,j,k;
	}vector;

extern int count;

float dotProduct(vector, vector);
vector crossProduct(vector, vector);


//python -c 'count=256
//print "const char[count] LUT = {", ", ".join(hex(int(128*__import__("math").sin(2*__import__("math").pi*i/(count+0.)))) for i in range(count))+"}"'

#endif

#include "vector_math.h"
//TODO: eliminate floats!!

void vector_driving(void);


float dotProduct(vector a, vector b)
{
	return a.i*b.i+a.j*b.j+a.k*b.k;
}

vector crossProduct(vector a, vector b)
{
	vector c = {a.j*b.k - a.k*b.j, a.k*b.i - a.i*b.k, a.i*b.j - a.j*b.i};
	return c;
}

#include <math.h>
#include "vector_math.h"
#include "spare_parts.h"
#include <stdio.h>
//#include "path_plan.h"

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

int setup (void) {
//	robot_id = 1;
    return 0;
}

int next_point_x = 0;
int next_point_y = 0;
int current_point_x = -100;
int current_point_y = -1500;
int current_theta = 1024;

void umain (void) {
 	vector curr = {cos(current_theta/ANGLE_FACTOR), sin(current_theta/ANGLE_FACTOR), 0};
    vector error = {(next_point_x - current_point_x),(next_point_y - current_point_y),0};
    float error_mag = fmaxf(error.i,error.j); // Optimization? 
    vector error_norm = {error.i / error_mag, error.j / error_mag, 0};
    uint8_t v_fwd = (uint8_t) (dotProduct(curr, error) * kp_fwd);
    uint8_t v_turn;
//    uint8_t v_turn = 0;         // avoid divide-by-zero
//    if (error_mag > 1) 
    v_turn = (uint8_t) (crossProduct(curr, error_norm).k * kp_turn);
	printf("v_fwd: %i",v_fwd);
	printf("v_turn: %i",v_turn);
}
