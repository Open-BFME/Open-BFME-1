// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// ?first@Gen_00943CF0@@AAEXPAXPAH11@Z -- retail 0x009432B0, 240 bytes, ret 0x10.
// Called by the matched Gen_00943CF0::process (0x00943CF0) and
// Gen_00943CF0::update (0x009434E0), which declare it with int outputs.
// The node value is a RenderObjClass: the body reads Transform[0][3] and
// Transform[1][3] (+0x24/+0x34), calls Get_Obj_Space_Bounding_Sphere (+0x108)
// and _bfme_ro_get_8c (+0x118) of the retail-reconciled rendobj.h, and
// update() compares the packed result with _bfme_unk_94 (+0x94).
// Gen_009431F0 is the same grid object (map_x/map_y read its +0/+4/+0x20/+0x24).
#include "rendobj.h"
#include "sphere.h"

class Gen_009431F0
{
public:
	int map_x(float x);
	int map_y(float y);
};

class Gen_00943CF0 : public Gen_009431F0
{
	void first(void *value, int *xOut, int *yOut, int *diffOut);
};

void Gen_00943CF0::first(void *value, int *xOut, int *yOut, int *diffOut)
{
	RenderObjClass *robj = (RenderObjClass *)value;
	Vector3 center = robj->Get_Transform_No_Validity_Check().Get_Translation();
	SphereClass sphere;
	robj->Get_Obj_Space_Bounding_Sphere(sphere);
	float extent = robj->_bfme_ro_get_8c() + sphere.Radius;

	*xOut = map_x(center[0] - extent);
	*yOut = map_y(center[1] - extent);
	*diffOut = (map_y(center[1] + extent) ^ *yOut) | (map_x(center[0] + extent) ^ *xOut);
	if (*diffOut != 0) {
		unsigned int v = *diffOut;
		int bit = 0;
		if ((v & 0xff00) != 0) {
			v >>= 8;
			bit |= 8;
		}
		if ((v & 0xf0) != 0) {
			v >>= 4;
			bit |= 4;
		}
		if ((v & 0x0c) != 0) {
			v >>= 2;
			bit |= 2;
		}
		if ((v & 2) != 0)
			bit |= 1;
		int keep = ~(1 << bit);
		*xOut &= keep;
		*yOut &= keep;
	}
}
