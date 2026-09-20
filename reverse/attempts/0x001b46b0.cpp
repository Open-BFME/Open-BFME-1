// ?Rva001B46B0@@YAMPBURva001B46B0Vec3@@0@Z
// partial score=0.75 date=2026-09-21
// Retail 0x001B46B0, 120 bytes, __cdecl free function taking two pointers to
// three consecutive floats (x,y,z) and returning a float in ST(0). No proven
// owning class or method identity (callers are still dumps), so the points
// stay raw float pointers rather than a guessed struct, and the function
// keeps its address token.
//
// delta = *b - *a per component; dist = length(delta); when dist is not
// exactly BfmeZeroRange (0x01075350, 0.0f) the delta is normalized by the
// reciprocal distance (1.0f/dist, via the shared 1.0f global at 0x01075334).
// The return expression (dx+dy)*BfmeZeroRange+dz reduces to dz numerically
// (BfmeZeroRange == 0.0f) but IEEE fp rules keep the multiply live in
// codegen, matching retail's fmul/fadd/fxch tail exactly.

extern "C" double __cdecl sqrt(double x);

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

	return (delta.x + delta.y) * BfmeZeroRange + delta.z;
}
