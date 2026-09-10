// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME MeshGeometryClass::Reset_Geometry, RVA 0x009268C0.
//
// The shipped meshgeometry.h has the Zero Hour member ordering. BFME's
// constructor, copy constructor, accessors, and Load_W3D body instead prove
// the layout used here: UserText/MeshName at +0x10/+0x14, the geometry
// counts at +0x24/+0x28, the buffer slots through +0x64, and CullTree at
// +0x90. Keep that ABI slice local to this method's translation unit.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "multilist.h"
#include <string.h>

typedef Vector3i16 TriIndex;

// Slot64 owns the 16-byte raw-buffer specialization at retail 0x00923F70.
// It is deliberately a distinct POD type: the common Vector4 specialization
// owns the separate 0x011135DC vtable family.  This type has no element
// constructor or destructor; ShareBufferClass still owns the allocation.
struct MeshGeometrySlot64Element_00923F70
{
	uint8 Data[16];
};

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	void Reset_Geometry(int polycount, int vertcount, bool keep_alloc);

protected:
	RefCountClass *UserText;                         // retail +0x10
	RefCountClass *MeshName;                         // retail +0x14
	int Flags;                                       // retail +0x18
	char SortLevel;                                  // retail +0x1c
	uint32 W3dAttributes;                             // retail +0x20
	int PolyCount;                                   // retail +0x24
	int VertexCount;                                 // retail +0x28
	ShareBufferClass<TriIndex> *Poly;                // retail +0x2c
	ShareBufferClass<Vector3> *Vertex;               // retail +0x30
	RefCountClass *Slot34;                           // retail +0x34
	RefCountClass *Slot38;                           // retail +0x38
	RefCountClass *Slot3c;                           // retail +0x3c
	ShareBufferClass<Vector3> *VertexNorm;           // retail +0x40
	RefCountClass *Slot44;                           // retail +0x44
	RefCountClass *Slot48;                           // retail +0x48
	RefCountClass *Slot4c;                           // retail +0x4c
	RefCountClass *PlaneEq;                          // retail +0x50
	RefCountClass *VertexShadeIdx;                   // retail +0x54
	RefCountClass *VertexBoneLink;                   // retail +0x58
	RefCountClass *Slot5c;                           // retail +0x5c
	ShareBufferClass<uint8> *PolySurfaceType;        // retail +0x60
	ShareBufferClass<MeshGeometrySlot64Element_00923F70> *Slot64; // retail +0x64
	char Bounds[0x28];                               // retail +0x68..+0x8f
	RefCountClass *CullTree;                         // retail +0x90
};

// These two BFME specializations are inlined by the retail Reset_Geometry TU.
// Keep their real ShareBuffer ownership/layout while forcing the same inline
// constructor path; the ordinary out-of-line specializations are separate
// retail callees used by other translation units.
template<>
__forceinline ShareBufferClass<uint8>::ShareBufferClass(int count, const char *msg, int alignment) :
	Count(count),
	Alignment(alignment)
{
	if (Alignment == 0) {
		RawBuffer = MSGW3DNEWARRAY(msg) uint8[Count];
		Array = RawBuffer;
	} else {
		RawBuffer = (uint8 *)MSGW3DNEWARRAY(msg) char[Count * sizeof(uint8) + Alignment];
		Array = (uint8 *)(((unsigned int)RawBuffer + Alignment - 1) & ~(Alignment - 1));
	}
}

template<>
__forceinline ShareBufferClass<MeshGeometrySlot64Element_00923F70>::ShareBufferClass(
	int count, const char *msg, int alignment) :
	Count(count),
	Alignment(alignment)
{
	if (Alignment == 0) {
		RawBuffer = (MeshGeometrySlot64Element_00923F70 *)MSGW3DNEWARRAY(msg)
			char[Count * sizeof(MeshGeometrySlot64Element_00923F70)];
		Array = RawBuffer;
	} else {
		RawBuffer = (MeshGeometrySlot64Element_00923F70 *)MSGW3DNEWARRAY(msg)
			char[Count * sizeof(MeshGeometrySlot64Element_00923F70) + Alignment];
		Array = (MeshGeometrySlot64Element_00923F70 *)(((unsigned int)RawBuffer + Alignment - 1) & ~(Alignment - 1));
	}
}

// ?Reset_Geometry@MeshGeometryClass@@QAEXHH_N@Z
void MeshGeometryClass::Reset_Geometry(int polycount, int vertcount, bool keep_alloc)
{
	Flags = 0;
	PolyCount = 0;
	VertexCount = 0;
	SortLevel = 0;

	REF_PTR_RELEASE(UserText);
	REF_PTR_RELEASE(MeshName);
	REF_PTR_RELEASE(Poly);
	REF_PTR_RELEASE(Slot64);
	REF_PTR_RELEASE(PolySurfaceType);

	for (int i = 0; i < 2; ++i) {
		REF_PTR_RELEASE((*reinterpret_cast<RefCountClass **>(reinterpret_cast<char *>(this) + 0x30 + i * 4)));
		REF_PTR_RELEASE((*reinterpret_cast<RefCountClass **>(reinterpret_cast<char *>(this) + 0x38 + i * 4)));
		REF_PTR_RELEASE((*reinterpret_cast<RefCountClass **>(reinterpret_cast<char *>(this) + 0x40 + i * 4)));
		REF_PTR_RELEASE((*reinterpret_cast<RefCountClass **>(reinterpret_cast<char *>(this) + 0x48 + i * 4)));
	}

	REF_PTR_RELEASE(PlaneEq);
	REF_PTR_RELEASE(VertexShadeIdx);
	REF_PTR_RELEASE(VertexBoneLink);
	REF_PTR_RELEASE(Slot5c);
	REF_PTR_RELEASE(CullTree);

	PolyCount = polycount;
	VertexCount = vertcount;

	if (PolyCount && VertexCount) {
		Poly = NEW_REF(ShareBufferClass<TriIndex>,
			(PolyCount, "MeshGeometryClass::Poly"));
		Poly->Clear();

		PolySurfaceType = NEW_REF(ShareBufferClass<uint8>,
			(PolyCount, "MeshGeometryClass::PolySurfaceType"));
		PolySurfaceType->Clear();

		Vertex = NEW_REF(ShareBufferClass<Vector3>,
			(VertexCount, "MeshGeometryClass::Vertex"));
		Vertex->Clear();

		VertexNorm = NEW_REF(ShareBufferClass<Vector3>,
			(VertexCount, "MeshGeometryClass::VertexNorm"));
		VertexNorm->Clear();

		Slot64 = NEW_REF(ShareBufferClass<MeshGeometrySlot64Element_00923F70>, (0, NULL));
	}
}
