#ifndef SPARE_PARTS_H
#define SPARE_PARTS_H
#include <joyos.h>
//#include "vector_math.h"
//int pick_next_point_y(int);

#define waypoints_length 18

//extern point p1B, p2B, p3B, p4B, p5B, p6B, p7B, p8B, p9B, p10B, p11B, p1R, p2R, p3R, p4R, p5R, p6R, p7R, p8R, p9R, p10R, p11R;
//extern point list_o_points_blue[18];
//extern point list_o_points_red[18];

typedef struct {
	int x,y;
	}point; 

point pick_next_point(point*);
void delay(int);

//point pick_next_point(*point_list)
//{
//    point next_point;
//    count += 1;
//    if (count > 18)
//        printf ("Way to fuck it up. That's too many incrementations.");
//    next_point = *(point_list+count);
//    return next_point;
//}

void build_list_o_points_blue(point*);
void build_list_o_points_red(point*);

#endif
