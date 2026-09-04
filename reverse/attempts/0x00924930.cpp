// ??4MeshGeometryClass@@QAEAAV0@ABV0@@Z
// partial score=0.93 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// MeshGeometryClass::operator= at 0x00924930.  Local ABI-slice replica of the
// BFME layout recovered by the matched copy ctor (0x009267E0): UserText+0x10,
// MeshName+0x14, Flags+0x18, SortLevel+0x1c, then Poly+0x2c, an eight-pointer
// Extra[4][2] grid at +0x30, Vertex..PolySurfaceType at +0x50..+0x64, bounds
// at +0x68, SphereClass at +0x80, CullTree at +0x90.  The Extra grid is what
// emits retail's two-iteration REF_PTR_SET walk (0x30/38/40/48 then 0x34/3c/
// 44/4c).  AABTreeClass is a size-only replica so `new AABTreeClass` keeps
// global operator new (0x1C); the real W3DMPO_GLUE pool new is the wrong
// allocator at this call site.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "sphere.h"
#include "multilist.h"

class MeshGeometryClass;

class AABTreeClass : public RefCountClass
{
	friend class MeshGeometryClass;
	AABTreeClass & operator = (const AABTreeClass & that);
public:
	AABTreeClass(void);
	void Set_Mesh(MeshGeometryClass * mesh);
private:
	unsigned char m_pad[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
// BFME offsets: Code/Libraries/Source/WWVegas/WW3D2/MeshGeometryClass_CopyCtor_Thunk.cpp
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	MeshGeometryClass & operator = (const MeshGeometryClass & that);

protected:
	ShareBufferClass<char> *						UserText;			///< retail this+0x10
	ShareBufferClass<char> *						MeshName;			///< retail this+0x14
	int										Flags;				///< retail this+0x18
	char										SortLevel;			///< retail this+0x1c
	uint32									W3dAttributes;		///< retail this+0x20
	int										PolyCount;			///< retail this+0x24
	int										VertexCount;		///< retail this+0x28
	ShareBufferClass<Vector3i16> *				Poly;				///< retail this+0x2c
	RefCountClass *							Extra[4][2];		///< retail this+0x30 .. +0x4c
	RefCountClass *							Vertex;				///< retail this+0x50
	RefCountClass *							VertexNorm;			///< retail this+0x54
	RefCountClass *							PlaneEq;			///< retail this+0x58
	RefCountClass *							VertexShadeIdx;		///< retail this+0x5c
	RefCountClass *							VertexBoneLink;		///< retail this+0x60
	RefCountClass *							PolySurfaceType;	///< retail this+0x64
	Vector3									BoundBoxMin;		///< retail this+0x68
	Vector3									BoundBoxMax;		///< retail this+0x74
	SphereClass								BoundSphere;		///< retail this+0x80
	AABTreeClass *							CullTree;			///< retail this+0x90
};

// ??4MeshGeometryClass@@QAEAAV0@ABV0@@Z present-unmatched
MeshGeometryClass & MeshGeometryClass::operator = (const MeshGeometryClass & that)
{
	MeshGeometryClass *destination = this;
	const MeshGeometryClass *source = &that;
	if (destination != source) {
		destination->Flags = source->Flags;
		destination->SortLevel = source->SortLevel;
		destination->W3dAttributes = source->W3dAttributes;
		destination->PolyCount = source->PolyCount;
		destination->VertexCount = source->VertexCount;

		destination->BoundBoxMin = source->BoundBoxMin;
		destination->BoundBoxMax = source->BoundBoxMax;
		destination->BoundSphere = source->BoundSphere;

		REF_PTR_SET(destination->UserText, source->UserText);
		REF_PTR_SET(destination->MeshName, source->MeshName);
		REF_PTR_SET(destination->Poly, source->Poly);
		REF_PTR_SET(destination->PolySurfaceType, source->PolySurfaceType);
		REF_PTR_SET(destination->VertexBoneLink, source->VertexBoneLink);

		for (int col = 0; col < 2; col++) {
			REF_PTR_SET(destination->Extra[0][col], source->Extra[0][col]);
			REF_PTR_SET(destination->Extra[1][col], source->Extra[1][col]);
			REF_PTR_SET(destination->Extra[2][col], source->Extra[2][col]);
			REF_PTR_SET(destination->Extra[3][col], source->Extra[3][col]);
		}

		REF_PTR_SET(destination->Vertex, source->Vertex);
		REF_PTR_SET(destination->VertexNorm, source->VertexNorm);
		REF_PTR_SET(destination->PlaneEq, source->PlaneEq);
		REF_PTR_SET(destination->VertexShadeIdx, source->VertexShadeIdx);

		REF_PTR_RELEASE(destination->CullTree);
		if (source->CullTree) {
			destination->CullTree = NEW_REF(AABTreeClass, ());
			*destination->CullTree = *source->CullTree;
			destination->CullTree->Set_Mesh(destination);
		}
	}
	return *destination;
}
