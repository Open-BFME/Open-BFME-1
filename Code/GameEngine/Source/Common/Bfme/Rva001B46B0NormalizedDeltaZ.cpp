// cl: /DNDEBUG /MD /EHsc
// Retail 0x001B46B0, 120 bytes, __cdecl free function taking two pointers to
// three consecutive floats (x,y,z) and returning a float in ST(0). No proven
// owning class or method identity (both callers, via ILT, are still dumps in
// the Locomotor range), so the points stay an address-named struct and the
// function keeps its address token.
//
// delta = *b - *a per component; dist = length(delta); when dist is not
// exactly BfmeZeroRange (0x01075350, 0.0f) the delta is normalized by the
// reciprocal distance (1.0f/dist, via the shared 1.0f global at 0x01075334).
// The result (dx+dy)*BfmeZeroRange+dz reduces to dz numerically
// (BfmeZeroRange == 0.0f) but IEEE fp rules keep the multiply live in
// codegen. Naming the result in a local before returning it is what keeps
// retail's shared branch tail and its fadd st(1)/fxch/fstp cleanup.

#include <math.h>

extern const float BfmeZeroRange;   // 0x01075350 == 0.0f
extern float g_bfmeDefaultBU;        // 0x01075334 == 1.0f

struct Rva001B46B0Vec3
{
	float x, y, z;
};

// ?Rva001B46B0@@YAMPBURva001B46B0Vec3@@0@Z
float Rva001B46B0(const Rva001B46B0Vec3 *a, const Rva001B46B0Vec3 *b)
{
	Rva001B46B0Vec3 delta;
	delta.x = b->x;
	delta.y = b->y;
	delta.z = b->z;
	delta.x -= a->x;
	delta.y -= a->y;
	delta.z -= a->z;

	float dist = (float)sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x);
	if (dist != BfmeZeroRange)
	{
		dist = g_bfmeDefaultBU / dist;
		delta.x *= dist;
		delta.y *= dist;
		delta.z *= dist;
	}

	float result = (delta.x + delta.y) * BfmeZeroRange + delta.z;
	return result;
}
