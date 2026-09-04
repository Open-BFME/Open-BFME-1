// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME5: BFME MeshGeometryClass::get_planes ABI slice.
// Retail keeps PolyCount at +0x24 and PlaneEq at +0x50.  The vendored
// MeshGeometry declaration has a different geometry slice, so keep these
// offsets local to the accessor rather than changing the shared header.

#include "always.h"
#include "sharebuf.h"
#include "vector4.h"

class MeshGeometryClass
{
	char _padding[0x50];
	ShareBufferClass<Vector4> *PlaneEq;

protected:
	Vector4 *get_planes(bool create);
};

// ?get_planes@MeshGeometryClass@@IAEPAVVector4@@_N@Z
Vector4 *MeshGeometryClass::get_planes(bool create)
{
	if (create && !PlaneEq) {
		PlaneEq = NEW_REF(ShareBufferClass<Vector4>,
			(*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x24),
			 "MeshGeometryClass::PlaneEq"));
	}
	if (PlaneEq) {
		return PlaneEq->Get_Array();
	}
	return NULL;
}
