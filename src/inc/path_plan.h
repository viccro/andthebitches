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

point p1B = {1200, -700};
point p2B = {1200,  700};
point p3B = blue_goal_far;
point p4B = p2B;
point p5B = tower_near_r;
point p6B = {0,-1400};
point p7B = blue_goal_near;
point p8B = {-1200,-700};
point p9B = tower_near_l;
point p10B = {-1200,700};
point p11B = {0, 1400};

point p1B = {-1200, -700};
point p2B = {-1200,  700};
point p3B = red_goal_far;
point p4B = p2B;
point p5B = tower_near_l;
point p6B = {0,-1400};
point p7B = red_goal_near;
point p8B = {1200,-700};
point p9B = tower_near_r;
point p10B = {1200,700};
point p11B = {0, 1400};

point list_o_points_blue [19] = {p1B, p2B, p3B, p4B, p5B, p6B, p7B, p8B, p9B, p10B, p11B, p3B, p4B, p5B, p6B, p7B, p8B, p9B};
point list_o_points_red  [19] = {p1R, p2R, p3R, p4R, p5R, p6R, p7R, p8R, p9R, p10R, p11R, p3R, p4R, p5R, p6R, p7R, p8R, p9R};

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
