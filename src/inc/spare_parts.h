#ifndef SPARE_PARTS_H
#define SPARE_PARTS_H
#include <joyos.h>
//#include "vector_math.h"
//int pick_next_point_y(int);

#define waypoints_length 18

enum COMPLETION {ok, error};      /* ok = 0, error = 1 */

typedef struct {
	int x,y;
	}point; 

void delay(int);

int dist(int,int,int,int);
#endif
