#include "spare_parts.h"

void delay(int n)
{
    int i;
    for (i = 0; i < n; i++)
    { }
}

int dist(int x_curr, int y_curr, int x_new, int y_new)
{
	//printf("current point.x: %d \t current point.y: %d \t next point.x: %d \t next point.y: %d \n", x_curr, y_curr, x_new , y_new);
    return (int) sqrt(pow((x_new - x_curr),2) + pow((y_new - y_curr),2));
}
