// ?wrapAngle@@YAMM@Z
#include <math.h>



extern const float Rva008AC750Span;
float wrapAngle(float x)
{
	x = (float)fmod((double)x, 3.1415927410125732);
	if (x >= 1.57079637f)
		x -= Rva008AC750Span;
	if (x < -1.57079637f)
		x += Rva008AC750Span;
	return x;
}
