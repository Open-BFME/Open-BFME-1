// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

// PointGroupClass array-update helper, retail RVA 0x00917B10 (85 bytes).
// Forwards to the out-of-line sizing prologue at 0x00914860 and the three
// split fills (0x009148C0 vertex locations, 0x00916CD0 UV, 0x00912880
// diffuse). The matched renderer at 0x00917B70 inlines the same sizing
// prologue and calls the same three fills with the same arity, proving the
// receiver (PointGroupClass) and each callee ABI. The sizing callee keeps
// its landed address-derived owner (Rva00914860Sizer); the call below
// reinterprets this accordingly and emits no code. The method name keeps
// its address token: the header's Update_Arrays decl is the likely donor
// but its trailing (vnum&, pnum&) pair is unproven against this body's
// (vnum-pointer, unknown-int) tail, so no semantic name is claimed.

#include "vector3.h"
#include "vector4.h"

extern void d_009148c0(void);

class Rva00914860Sizer
{
public:
	void updatePoolSizes(int width, int height, int *storedWidth);
};

class PointGroupClass
{
public:
	void rva00917B10(Vector3 *point_loc, Vector4 *point_diffuse, float *point_size,
		unsigned char *point_orientation, unsigned char *point_frame,
		int active_points, int total_points, int *vnum, int unknown);

	void rva00916CD0(unsigned char *point_frame, int active_points, int unknown);
	void rva00912880(Vector4 *point_diffuse, int active_points);

private:
	virtual void abstract_dtor(void);
};

void PointGroupClass::rva00917B10(Vector3 *point_loc, Vector4 *point_diffuse, float *point_size,
	unsigned char *point_orientation, unsigned char *point_frame,
	int active_points, int total_points, int *vnum, int unknown)
{
	((Rva00914860Sizer *)this)->updatePoolSizes(active_points, total_points, vnum);
	typedef void (__fastcall *Rva009148C0Call)(PointGroupClass *, unsigned char *, Vector3 *,
		float *, unsigned char *, int);
	((Rva009148C0Call)d_009148c0)(this, point_orientation, point_loc, point_size,
		point_orientation, active_points);
	rva00916CD0(point_frame, active_points, unknown);
	rva00912880(point_diffuse, active_points);
}
