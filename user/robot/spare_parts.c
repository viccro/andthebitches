#include "spare_parts.h"

int count = 0;

int pick_next_point_x(int gcx)
{
    int next_point_x;

    count += 1;
    if (count > 8)
        printf ("Way to fuck it up. That's too many incrementations.");
    next_point_x = *(x_list+count);

    return next_point_x;
}

int pick_next_point_y(int gcy)
{
    int next_point_y;
    next_point_y = *(y_list+count);

    return next_point_y;
}


void delay(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
    }
}
