// cl: /DNDEBUG /MD /EHs-c-
// Angle wrap helpers: fold an angle into [0, 2*pi). Retail calls the
// _CIfmod intrinsic with the float 2*pi widened to a double (VA 0x01127A28
// holds 0x401921FB60000000) and subtracts from the float 2*pi at VA 0x01087B10.

#include <math.h>

#define TWO_PI 6.28318530718f

// Retail VA 0x01075350 is four readonly zero bytes. Both x87 comparisons
// below use DWORD operands; no EA variable name is proven.
extern const float g_rva01075350 = 0.0f;

struct Rva0079D0F0Vector
{
	float x;
	float y;
};

// ?Rva0079D0A0@@YANM@Z
double __cdecl Rva0079D0A0(float angle)
{
	if (angle < g_rva01075350)
		return TWO_PI - fmod(-angle, TWO_PI);
	return fmod(angle, TWO_PI);
}

// ?Rva0079D0F0@@YANPAX@Z
double __cdecl Rva0079D0F0(void *pair)
{
	Rva0079D0F0Vector *vector = (Rva0079D0F0Vector *)pair;
	float angle = (float)atan2(vector->y, vector->x);
	if (angle < g_rva01075350)
		return TWO_PI - fmod(-angle, TWO_PI);
	return fmod(angle, TWO_PI);
}
