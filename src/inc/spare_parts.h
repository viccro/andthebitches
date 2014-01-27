#ifndef SPARE_PARTS_H
#define SPARE_PARTS_H
#include <joyos.h>
//#include "vector_math.h"
//int pick_next_point_y(int);

typedef struct{
	int x,y;
	}point; 

point pick_next_point(void);
void delay(int);

extern point p1B, p2B, p3B, p4B, p5B, p6B, p7B, p8B, p9B, p10B, p11B, p1R, p2R, p3R, p4R, p5R, p6R, p7R, p8R, p9R, p10R, p11R;
extern point list_o_points_blue[18];
extern point list_o_points_red[18];

#endif
