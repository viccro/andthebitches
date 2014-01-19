#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

typedef struct{
	float i,j,k;
	}vector;

float dotProduct(vector, vector);
vector crossProduct(vector, vector);



#endif
