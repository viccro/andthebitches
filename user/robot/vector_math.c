#include <vector_math.h>

float dotProduct(vector a, vector b)
{
	return a.i*b.i+a.j*b.j+a.k*b.k;
}

vector crossProduct(vector a, vector b)
{
	vector c = {a.j*b.k - a.k*b.j, a.k*b.i - a.i*b.k, a.i*b.j - a.j*b.i};
	return c;
}


