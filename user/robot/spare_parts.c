#include "spare_parts.h"

int count = 0;

void delay(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
    }
}

point pick_next_point(point* point_list)
{
    point next_point;
    count += 1;
    if (count > 18)
        printf ("Way to fuck it up. That's too many incrementations.");
    next_point = point_list[count];
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

////////////////
// Waypoints  //986
////////////////
//point red_goal_far   = { 1720,  1355};
//point red_goal_near  = {-1255, -1700};
//point blue_goal_far  = { 1725, -1200};
//point blue_goal_near = {-1305,  1780};
//point tower_near_r   = { -735,  -550};
//point tower_near_l   = { -735,   550};



//point p1B = {1200, -700};
//point p2B = {1200,  700};
//point p3B = { 1725, -1200}; //blue_goal_far;
//point p4B = {1200,  700}; //p2B;
//point p5B = { -735,  -550}; //tower_near_r;
//point p6B = {0,-1400};
//point p7B = {-1305,  1780}; //blue_goal_near;
//point p8B = {-1200,-700};
//point p9B = { -735,   550}; //tower_near_l;
//point p10B = {-1200,700};
//point p11B = {0, 1400};

//point p1R = {-1200, -700};
//point p2R = {-1200,  700};
//point p3R = { 1720,  1355}; //red_goal_far;
//point p4R = {-1200,  700}; //p2R;
//point p5R = { -735,   550}; //tower_near_l;
//point p6R = {0,-1400};
//point p7R = {-1255, -1700}; //red_goal_near;
//point p8R = {1200,-700};
//point p9R = { -735,  -550}; //tower_near_r;
//point p10R = {1200,700};
//point p11R = {0, 1400};

point p1B = {1200, -700};
point p2B = {1200,  700};
point p3B = { 1725, -1200}; //blue_goal_far;
point p4B = {1200,  700}; //p2B;
point p5B = { -735,  -550}; //tower_near_r;
point p6B = {0,-1400};
point p7B = {-1305,  1780}; //blue_goal_near;
point p8B = {-1200,-700};
point p9B = { -735,   550}; //tower_near_l;
point p10B = {-1200,700};
point p11B = {0, 1400};

point p1R = {-1200, -700};
point p2R = {-1200,  700};
point p3R = { 1720,  1355}; //red_goal_far;
point p4R = {-1200,  700}; //p2R;
point p5R = { -735,   550}; //tower_near_l;
point p6R = {0,-1400};
point p7R = {-1255, -1700}; //red_goal_near;
point p8R = {1200,-700};
point p9R = { -735,  -550}; //tower_near_r;
point p10R = {1200,700};
point p11R = {0, 1400};


void build_list_o_points_blue(point *list_o_points_blue) {
	//static point list_o_points_blue[18];
	list_o_points_blue[0] = p1B; //, , , p5B, p6B, p7B, p8B, p9B, p10B, p11B, p3B, p4B, p5B, p6B, p7B, p8B, p9B};
	list_o_points_blue[1] = p2B;
	list_o_points_blue[2] = p3B;
	list_o_points_blue[3] = p4B;
	list_o_points_blue[4] = p5B;
	list_o_points_blue[5] = p6B;
	list_o_points_blue[6] = p7B;
	list_o_points_blue[7] = p8B;
	list_o_points_blue[8] = p9B;
	list_o_points_blue[9] = p10B;
	list_o_points_blue[10] = p11B;
	list_o_points_blue[11] = p3B;
	list_o_points_blue[12] = p4B;
	list_o_points_blue[13] = p5B;
	list_o_points_blue[14] = p6B;
	list_o_points_blue[15] = p7B;
	list_o_points_blue[16] = p8B;
	list_o_points_blue[17] = p9B;
	return list_o_points_blue;
}

void build_list_o_points_red(point *list_o_points_red) {
//	static point list_o_points_red[18];
	list_o_points_red[0] = p1B; //{p1R, p2R, p3R, p4R, p5R, p6R, p7R, p8R, p9R, p10R, p11R, p3R, p4R, p5R, p6R, p7R, p8R, p9R};
	list_o_points_red[1] = p2B;
	list_o_points_red[2] = p3B;
	list_o_points_red[3] = p4B;
	list_o_points_red[4] = p5B;
	list_o_points_red[5] = p6B;
	list_o_points_red[6] = p7B;
	list_o_points_red[7] = p8B;
	list_o_points_red[8] = p9B;
	list_o_points_red[9] = p10B;
	list_o_points_red[10] = p11B;
	list_o_points_red[11] = p3B;
	list_o_points_red[12] = p4B;
	list_o_points_red[13] = p5B;
	list_o_points_red[14] = p6B;
	list_o_points_red[15] = p7B;
	list_o_points_red[16] = p8B;
	list_o_points_red[17] = p9B;
	return list_o_points_red;
}



