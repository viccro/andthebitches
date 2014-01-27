#ifndef SPARE_PARTS_H
#define SPARE_PARTS_H
#include <joyos.h>
int pick_next_point_y(int);
int pick_next_point_x(int);
void delay(int);


extern int x_list[8];
extern int y_list[8];
extern int red_goal_far[2];
extern int red_goal_near[2];
extern int blue_goal_far[2];
extern int blue_goal_near[2];

#endif
