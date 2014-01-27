#include "spare_parts.h"

int count = 0;

point pick_next_point(void)
{
    point next_point;
    count += 1;
    if (count > 18)
        printf ("Way to fuck it up. That's too many incrementations.");
    next_point = *(point_list+count);
    return next_point;
}
/*
int pick_next_point_y(int gcy)
{
    int next_point_y;
    next_point_y = *(y_list+count);

    return next_point_y;
}
*/

void delay(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
    }
}

////////////////
// Waypoints  //986
////////////////
point red_goal_far   = { 1720,  1355};
point red_goal_near  = {-1255, -1700};
point blue_goal_far  = { 1725, -1200};
point blue_goal_near = {-1305,  1780};
point tower_near_r   = { -735,  -550};
point tower_near_l   = { -735,   550};



 p1B = {1200, -700};
 p2B = {1200,  700};
 p3B = blue_goal_far;
 p4B = p2B;
 p5B = tower_near_r;
 p6B = {0,-1400};
 p7B = blue_goal_near;
 p8B = {-1200,-700};
 p9B = tower_near_l;
 p10B = {-1200,700};
 p11B = {0, 1400};

 p1R = {-1200, -700};
 p2R = {-1200,  700};
 p3R = red_goal_far;
 p4R = p2R;
 p5R = tower_near_l;
 p6R = {0,-1400};
 p7R = red_goal_near;
 p8R = {1200,-700};
 p9R = tower_near_r;
 p10R = {1200,700};
 p11R = {0, 1400};

list_o_points_blue[18] = {p1B, p2B, p3B, p4B, p5B, p6B, p7B, p8B, p9B, p10B, p11B, p3B, p4B, p5B, p6B, p7B, p8B, p9B};
list_o_points_red[18] = {p1R, p2R, p3R, p4R, p5R, p6R, p7R, p8R, p9R, p10R, p11R, p3R, p4R, p5R, p6R, p7R, p8R, p9R};

