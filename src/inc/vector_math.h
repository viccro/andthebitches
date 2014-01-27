#ifndef _VECTOR_MATH_H_
#define _VECTOR_MATH_H_

#include <pgmspace.h>
//#include <unistd.h>
#define PROGMEM   __ATTR_PROGMEM__

typedef struct{
	float i,j,k;
	}vector;

extern int count;


float dotProduct(vector, vector);
vector crossProduct(vector, vector);


//python -c 'count=256
//print "const char[count] LUT = {", ", ".join(hex(int(128*__import__("math").sin(2*__import__("math").pi*i/(count+0.)))) for i in range(count))+"}"'

#endif
