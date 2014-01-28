#ifndef SPARE_PARTS_H
#define SPARE_PARTS_H
#include <joyos.h>
//#include "vector_math.h"
//int pick_next_point_y(int);

#define waypoints_length 18

typedef struct {
	int x,y;
	}point; 

point pick_next_point(point*);
void delay(int);

void build_list_o_points_blue(point*);
void build_list_o_points_red(point*);

#endif
