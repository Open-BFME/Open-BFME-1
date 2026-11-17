// ?wrapAngle@@YAMM@Z
#include <math.h>



// Retail VA 0x01136850 .rdata bytes db0f4940 = pi as float; owned here once.
extern const float Rva008AC750Span = 3.14159274f;
float wrapAngle(float x)
{
	x = (float)fmod((double)x, 3.1415927410125732);
	if (x >= 1.57079637f)
		x -= Rva008AC750Span;
	if (x < -1.57079637f)
		x += Rva008AC750Span;
	return x;
}
