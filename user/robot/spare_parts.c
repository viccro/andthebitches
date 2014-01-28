#include "spare_parts.h"

void delay(int n)
{
    int i;
    for (i = 0; i < n; i++)
    { }
}

int dist(point a,point b)
{
    return (int) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
