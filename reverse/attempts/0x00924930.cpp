// ??4MeshGeometryClass@@QAEAAV0@ABV0@@Z
// partial score=0.93 date=2026-09-04
// ??4MeshGeometryClass@@QAEAAV0@ABV0@@Z
// partial score=0.93 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// MeshGeometryClass::operator= at 0x00924930.  Local ABI-slice replica of the
// BFME layout recovered by the matched copy ctor (0x009267E0): UserText+0x10,
// MeshName+0x14, Flags+0x18, SortLevel+0x1c, then Poly+0x2c.  The eight
// geometry-reference slots at +0x30..+0x4c are walked as
// 0x30/38/40/48 then 0x34/3c/44/4c; +0x30 is the witnessed Vertex slot and
// +0x40 is the witnessed VertexNorm slot, while the remaining slots are kept
// address-derived.  The independently witnessed tail roles are PlaneEq+0x50,
// VertexShadeIdx+0x54, VertexBoneLink+0x58, the influence buffer+0x5c,
// PolySurfaceType+0x60, and the unclassified +0x64 slot.  Bounds start at
// +0x68, SphereClass at +0x80, and CullTree at +0x90.  AABTreeClass is a
// size-only replica so `new AABTreeClass` keeps global operator new (0x1C);
// the real W3DMPO_GLUE pool new is the wrong allocator at this call site.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "vector3.h"
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
	RefCountClass * UserText; ///< retail this+0x10
	RefCountClass * MeshName; ///< retail this+0x14
	int										Flags;				///< retail this+0x18
	char										SortLevel;			///< retail this+0x1c
	uint32									W3dAttributes;		///< retail this+0x20
	int										PolyCount;			///< retail this+0x24
	int										VertexCount;		///< retail this+0x28
	RefCountClass * Poly; ///< retail this+0x2c
	RefCountClass * GeometryRefs[4][2]; ///< retail this+0x30 .. +0x4c; Vertex is +0x30 and VertexNorm is +0x40
	RefCountClass * PlaneEq; ///< retail this+0x50
	RefCountClass * VertexShadeIdx; ///< retail this+0x54
	RefCountClass * VertexBoneLink; ///< retail this+0x58
	RefCountClass * InfluenceRunBuffer; ///< retail this+0x5c; original member name unknown
	RefCountClass * PolySurfaceType; ///< retail this+0x60
	RefCountClass * Slot64; ///< retail this+0x64; role/type not needed by this assignment
	Vector3									BoundBoxMin;		///< retail this+0x68
	Vector3									BoundBoxMax;		///< retail this+0x74
	SphereClass								BoundSphere;		///< retail this+0x80
	AABTreeClass *							CullTree;			///< retail this+0x90
};

// ??4MeshGeometryClass@@QAEAAV0@ABV0@@Z present-unmatched
MeshGeometryClass & MeshGeometryClass::operator = (const MeshGeometryClass & that)
{
	if (this != &that) {
		Flags = that.Flags;
		SortLevel = that.SortLevel;
		W3dAttributes = that.W3dAttributes;
		PolyCount = that.PolyCount;
		VertexCount = that.VertexCount;

		BoundBoxMin = that.BoundBoxMin;
		BoundBoxMax = that.BoundBoxMax;
		BoundSphere = that.BoundSphere;

		REF_PTR_SET(UserText, that.UserText);
		REF_PTR_SET(MeshName, that.MeshName);
		REF_PTR_SET(Poly, that.Poly);
		REF_PTR_SET(Slot64, that.Slot64);
		REF_PTR_SET(PolySurfaceType, that.PolySurfaceType);

		for (int col = 0; col < 2; col++) {
			REF_PTR_SET(GeometryRefs[0][col], that.GeometryRefs[0][col]);
			REF_PTR_SET(GeometryRefs[1][col], that.GeometryRefs[1][col]);
			REF_PTR_SET(GeometryRefs[2][col], that.GeometryRefs[2][col]);
			REF_PTR_SET(GeometryRefs[3][col], that.GeometryRefs[3][col]);
		}

		REF_PTR_SET(PlaneEq, that.PlaneEq);
		REF_PTR_SET(VertexShadeIdx, that.VertexShadeIdx);
		REF_PTR_SET(VertexBoneLink, that.VertexBoneLink);
		REF_PTR_SET(InfluenceRunBuffer, that.InfluenceRunBuffer);

		REF_PTR_RELEASE(CullTree);
		if (that.CullTree) {
			CullTree = NEW_REF(AABTreeClass, ());
			*CullTree = *that.CullTree;
			CullTree->Set_Mesh(this);
		}
	}
	return *this;
}
