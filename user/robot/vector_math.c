#include "vector_math.h"
//TODO: eliminate floats!!

void vector_driving(void);


float dotProduct(vector a, vector b)
{
	return a.i*b.i+a.j*b.j+a.k*b.k;
}

vector crossProduct(vector a, vector b)
{
	vector c = {a.j*b.k - a.k*b.j, a.k*b.i - a.i*b.k, a.i*b.j - a.j*b.i};
	return c;
}

/*PROGMEM const char LUT_sin = {0x0, 0x3, 0x6, 0x9, 0xc, 0xf, 0x12, 0x15, 0x18, 0x1c, 0x1f, 0x22, 0x25, 0x28, 0x2b, 0x2e, 0x30, 0x33, 0x36, 0x39, 0x3c, 0x3f, 0x41, 0x44, 0x47, 0x49, 0x4c, 0x4e, 0x51, 0x53, 0x55, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6d, 0x6f, 0x70, 0x72, 0x73, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7c, 0x7d, 0x7e, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x80, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e, 0x7d, 0x7c, 0x7c, 0x7b, 0x7a, 0x79, 0x78, 0x77, 0x76, 0x75, 0x73, 0x72, 0x70, 0x6f, 0x6d, 0x6c, 0x6a, 0x68, 0x66, 0x64, 0x62, 0x60, 0x5e, 0x5c, 0x5a, 0x58, 0x55, 0x53, 0x51, 0x4e, 0x4c, 0x49, 0x47, 0x44, 0x41, 0x3f, 0x3c, 0x39, 0x36, 0x33, 0x30, 0x2e, 0x2b, 0x28, 0x25, 0x22, 0x1f, 0x1c, 0x18, 0x15, 0x12, 0xf, 0xc, 0x9, 0x6, 0x3, 0x0, -0x3, -0x6, -0x9, -0xc, -0xf, -0x12, -0x15, -0x18, -0x1c, -0x1f, -0x22, -0x25, -0x28, -0x2b, -0x2e, -0x30, -0x33, -0x36, -0x39, -0x3c, -0x3f, -0x41, -0x44, -0x47, -0x49, -0x4c, -0x4e, -0x51, -0x53, -0x55, -0x58, -0x5a, -0x5c, -0x5e, -0x60, -0x62, -0x64, -0x66, -0x68, -0x6a, -0x6c, -0x6d, -0x6f, -0x70, -0x72, -0x73, -0x75, -0x76, -0x77, -0x78, -0x79, -0x7a, -0x7b, -0x7c, -0x7c, -0x7d, -0x7e, -0x7e, -0x7f, -0x7f, -0x7f, -0x7f, -0x7f, -0x80, -0x7f, -0x7f, -0x7f, -0x7f, -0x7f, -0x7e, -0x7e, -0x7d, -0x7c, -0x7c, -0x7b, -0x7a, -0x79, -0x78, -0x77, -0x76, -0x75, -0x73, -0x72, -0x70, -0x6f, -0x6d, -0x6c, -0x6a, -0x68, -0x66, -0x64, -0x62, -0x60, -0x5e, -0x5c, -0x5a, -0x58, -0x55, -0x53, -0x51, -0x4e, -0x4c, -0x49, -0x47, -0x44, -0x41, -0x3f, -0x3c, -0x39, -0x36, -0x33, -0x30, -0x2e, -0x2b, -0x28, -0x25, -0x22, -0x1f, -0x1c, -0x18, -0x15, -0x12, -0xf, -0xc, -0x9, -0x6, -0x3};

PROGMEM const char LUT_cos = { 0x80, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e, 0x7d, 0x7c, 0x7c, 0x7b, 0x7a, 0x79, 0x78, 0x77, 0x76, 0x75, 0x73, 0x72, 0x70, 0x6f, 0x6d, 0x6c, 0x6a, 0x68, 0x66, 0x64, 0x62, 0x60, 0x5e, 0x5c, 0x5a, 0x58, 0x55, 0x53, 0x51, 0x4e, 0x4c, 0x49, 0x47, 0x44, 0x41, 0x3f, 0x3c, 0x39, 0x36, 0x33, 0x30, 0x2e, 0x2b, 0x28, 0x25, 0x22, 0x1f, 0x1c, 0x18, 0x15, 0x12, 0xf, 0xc, 0x9, 0x6, 0x3, 0x0, -0x3, -0x6, -0x9, -0xc, -0xf, -0x12, -0x15, -0x18, -0x1c, -0x1f, -0x22, -0x25, -0x28, -0x2b, -0x2e, -0x30, -0x33, -0x36, -0x39, -0x3c, -0x3f, -0x41, -0x44, -0x47, -0x49, -0x4c, -0x4e, -0x51, -0x53, -0x55, -0x58, -0x5a, -0x5c, -0x5e, -0x60, -0x62, -0x64, -0x66, -0x68, -0x6a, -0x6c, -0x6d, -0x6f, -0x70, -0x72, -0x73, -0x75, -0x76, -0x77, -0x78, -0x79, -0x7a, -0x7b, -0x7c, -0x7c, -0x7d, -0x7e, -0x7e, -0x7f, -0x7f, -0x7f, -0x7f, -0x7f, -0x80, -0x7f, -0x7f, -0x7f, -0x7f, -0x7f, -0x7e, -0x7e, -0x7d, -0x7c, -0x7c, -0x7b, -0x7a, -0x79, -0x78, -0x77, -0x76, -0x75, -0x73, -0x72, -0x70, -0x6f, -0x6d, -0x6c, -0x6a, -0x68, -0x66, -0x64, -0x62, -0x60, -0x5e, -0x5c, -0x5a, -0x58, -0x55, -0x53, -0x51, -0x4e, -0x4c, -0x49, -0x47, -0x44, -0x41, -0x3f, -0x3c, -0x39, -0x36, -0x33, -0x30, -0x2e, -0x2b, -0x28, -0x25, -0x22, -0x1f, -0x1c, -0x18, -0x15, -0x12, -0xf, -0xc, -0x9, -0x6, -0x3, 0x0, 0x3, 0x6, 0x9, 0xc, 0xf, 0x12, 0x15, 0x18, 0x1c, 0x1f, 0x22, 0x25, 0x28, 0x2b, 0x2e, 0x30, 0x33, 0x36, 0x39, 0x3c, 0x3f, 0x41, 0x44, 0x47, 0x49, 0x4c, 0x4e, 0x51, 0x53, 0x55, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6d, 0x6f, 0x70, 0x72, 0x73, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7c, 0x7d, 0x7e, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f};

*/