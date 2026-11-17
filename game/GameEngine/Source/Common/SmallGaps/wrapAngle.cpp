// ?wrapAngle@@YAMM@Z
#include <math.h>
extern const double Rva008AC750TwoPi;


extern const float Rva008AC750Span;
float wrapAngle(float x)
{
	x = (float)fmod((double)x, Rva008AC750TwoPi);
	if (x >= 1.57079637f)
		x -= Rva008AC750Span;
	if (x < -1.57079637f)
		x += Rva008AC750Span;
	return x;
}
