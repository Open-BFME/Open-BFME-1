// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME5: BFME MeshGeometryClass::intersect_obbox_brute_force ABI slice.

#include "always.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "inttest.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass
{
public:
	virtual void Retail_Vtable_Slot_0();
	virtual void Retail_Vtable_Slot_1();
	virtual void Retail_Vtable_Slot_2();
	virtual void Compute_Plane_Equations(Vector4 *array);

protected:
	Vector4 *get_planes(bool create);

	unsigned char m_unmodelled_04[0x14];
	unsigned int Flags;
	unsigned char m_unmodelled_1c[8];
	int PolyCount;
	unsigned char m_unmodelled_28[4];
	ShareBufferClass<TriIndex> *Poly;
	ShareBufferClass<Vector3> *Vertex;

	bool intersect_obbox_brute_force(OBBoxIntersectionTestClass &localtest);
};

// ?intersect_obbox_brute_force@MeshGeometryClass@@IAE_NAAVOBBoxIntersectionTestClass@@@Z
bool MeshGeometryClass::intersect_obbox_brute_force(OBBoxIntersectionTestClass &localtest)
{
	TriClass tri;
	const Vector3 *loc = Vertex->Get_Array();
	const TriIndex *polyverts = Poly->Get_Array();
	const Vector4 *norms = get_planes(true);

	if (norms != NULL && (Flags & 2) != 0) {
		Compute_Plane_Equations(const_cast<Vector4 *>(norms));
	}

	for (int srtri = 0; srtri < PolyCount; srtri++) {
		tri.V[0] = &(loc[polyverts[srtri][0]]);
		tri.V[1] = &(loc[polyverts[srtri][1]]);
		tri.V[2] = &(loc[polyverts[srtri][2]]);
		tri.N = (Vector3 *)&(norms[srtri]);

		if (CollisionMath::Intersection_Test(localtest.Box, tri)) {
			return true;
		}
	}
	return false;
}
