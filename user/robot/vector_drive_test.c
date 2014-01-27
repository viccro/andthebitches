#include <math.h>
#include "vector_math.h"
#include "spare_parts.h"
#include <stdio.h>
//#include "path_plan.h"

#define PI 3.14159265
#define ANGLE_FACTOR 651.898647649

int usetup (void) {
//	robot_id = 1;
    return 0;
}

float kp_fwd=.12;
float kp_turn=2.1;
int next_point_x = 0;
int next_point_y = 0;
int current_point_x = -500;
int current_point_y = -1500;
int current_theta = 1024;

void umain (void) {
 	vector curr = {cos(current_theta/ANGLE_FACTOR), sin(current_theta/ANGLE_FACTOR), 0};
    vector error = {(next_point_x - current_point_x),(next_point_y - current_point_y),0};
    float error_mag = fmaxf(error.i,error.j); // Optimization? 
    vector error_norm = {error.i / error_mag, error.j / error_mag, 0};
	float dot = dotProduct(curr, error);
	printf("dot product is %.3f\n",dot);
    int v_fwd = (int) (dotProduct(curr, error) * kp_fwd);
//    uint8_t v_turn = 0;         // avoid divide-by-zero
//    if (error_mag > 1) 
	vector cross = crossProduct(curr, error_norm);
    int v_turn = (int) (cross.k * kp_turn * 651.89);
	printf("cross product is %.3f\n",cross.k);
	printf("uncasted v_turn = %.3f\n",floor(cross.k * kp_turn * 651.89));
	printf("v_fwd: %d",v_fwd);
	printf("v_turn: %d",v_turn);
}
