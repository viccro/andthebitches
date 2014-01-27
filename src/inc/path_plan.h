#ifndef _PATH_PLAN_H_
#define _PATH_PLAN_H_

typedef struct{
    float x,y;
    }meas;

typedef struct{
	int x,y;
	}point;

typedef struct{
    int i,j;
    }ind;

////////////////
// Waypoints  //986
////////////////
point red_goal_far   = { 1720,  1355};
point red_goal_near  = {-1255, -1700};
point blue_goal_far  = { 1725, -1200};
point blue_goal_near = {-1305,  1780};
point tower_near_r   = { -735,  -550};
point tower_near_l   = { -735,   550};

point p1B, p2B, p3B, p4B, p5B, p6B, p7B, p8B, p9B, p10B, p11B, p1R, p2R, p3R, p4R, p5R, p6R, p7R, p8R, p9R, p10R, p11R;
point list_o_points_blue[18];
point list_o_points_red[18];

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

point meas2point(meas m)
{
    point p;
    p.x = (int)(-2000 + 41.6344 * m.x);
    p.y = (int)(-2000 + 41.6344 * m.x);
}

/*ind point2index(point p)
{
    ind i;
    i.i = (int)(7.747 + 0.00387397 * p.x);
    i.j = (int)(7.747 + 0.00387397 * p.y);
    return i;
}

int distSq(point a, point b)
{
    int sqX = (a.x - b.x) * (a.x - b.x);
    int sqY = (a.y - b.y) * (a.y - b.y);
    return (int)(sqX + sqY);
}

int map[16*16] = {
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                  };
*/
#endif
