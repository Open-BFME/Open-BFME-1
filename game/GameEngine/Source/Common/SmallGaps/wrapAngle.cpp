// ?wrapAngle@@YAMM@Z
#include <math.h>
extern const double Rva008AC750TwoPi;
extern const float g_bfmeDefaultEG;
extern const float Rva008AC750Lower;
extern const float Rva008AC750Span;
float wrapAngle(float x)
{
	x = (float)fmod((double)x, Rva008AC750TwoPi);
	if (x >= g_bfmeDefaultEG)
		x -= Rva008AC750Span;
	if (x < Rva008AC750Lower)
		x += Rva008AC750Span;
	return x;
}
