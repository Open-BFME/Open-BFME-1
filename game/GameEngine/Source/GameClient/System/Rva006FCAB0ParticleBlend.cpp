// cl: /DNDEBUG /MD /EHsc
#include <math.h>

// ?Rva006FCAB0ParticleBlend@@YAMM@Z
float Rva006FCAB0ParticleBlend(float x)
{
	float square = x*x;
	float root = sqrtf(x);
	return square + (root-square)*x;
}
