// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// MeshGeometryClass::operator= at retail 0x00924930 (760 bytes).
//
// Identity: the matched copy constructor (0x009267E0) ends in `*this = that`
// and the matched MeshModelClass::operator= (0x0094DA40) calls this body; the
// Zero Hour twin in meshgeometry.cpp has the same scalar copy, REF_PTR_SET run
// and CullTree clone.
//
// Local ABI slice of the BFME layout, following the landed constructor and
// copy constructor.  Witnessed names: UserText+0x10 MeshName+0x14 Flags+0x18
// SortLevel+0x1c PolyCount+0x24 VertexCount+0x28 Poly+0x2c Vertex+0x30
// VertexShadeIdx+0x54 VertexBoneLink+0x58 BoundBoxMin+0x68 BoundBoxMax+0x74
// BoundSphereCenter+0x80 CullTree+0x90.  PlaneEq+0x50 is named by the
// "MeshGeometryClass::PlaneEq" literal get_planes (0x00924FA0) stores there;
// W3dAttributes+0x20 sits where the Zero Hour copy run puts it.  The rest keep
// offset names.
//
// BFME widened four geometry pointers into two-element arrays at +0x30, +0x38,
// +0x40 and +0x48: retail walks them as one loop over the index, and inside
// that loop it only shares a buffer the source actually has.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "vector3.h"
#include "multilist.h"

class MeshGeometryClass;

// Callee contract: ??0 0x0096A8E0, ??4 0x0096A970, Set_Mesh 0x0096A620; the
// 0x1C allocation goes through global operator new (0x00881F30).
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
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	MeshGeometryClass & operator = (const MeshGeometryClass & that);

protected:
	RefCountClass *			UserText;			///< retail this+0x10
	RefCountClass *			MeshName;			///< retail this+0x14
	int						Flags;				///< retail this+0x18
	char					SortLevel;			///< retail this+0x1c
	uint32					W3dAttributes;		///< retail this+0x20
	int						PolyCount;			///< retail this+0x24
	int						VertexCount;		///< retail this+0x28
	RefCountClass *			Poly;				///< retail this+0x2c
	RefCountClass *			Vertex[2];			///< retail this+0x30
	RefCountClass *			Slot38[2];			///< retail this+0x38
	RefCountClass *			Slot40[2];			///< retail this+0x40
	RefCountClass *			Slot48[2];			///< retail this+0x48
	RefCountClass *			PlaneEq;			///< retail this+0x50
	RefCountClass *			VertexShadeIdx;		///< retail this+0x54
	RefCountClass *			VertexBoneLink;		///< retail this+0x58
	RefCountClass *			Slot5c;				///< retail this+0x5c
	RefCountClass *			Slot60;				///< retail this+0x60
	RefCountClass *			Slot64;				///< retail this+0x64
	Vector3					BoundBoxMin;		///< retail this+0x68
	Vector3					BoundBoxMax;		///< retail this+0x74
	Vector3					BoundSphereCenter;	///< retail this+0x80
	float					BoundSphereRadius;	///< retail this+0x8c
	AABTreeClass *			CullTree;			///< retail this+0x90
};

// ??4MeshGeometryClass@@QAEAAV0@ABV0@@Z
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
		BoundSphereCenter = that.BoundSphereCenter;
		BoundSphereRadius = that.BoundSphereRadius;

		REF_PTR_SET(UserText, that.UserText);
		REF_PTR_SET(MeshName, that.MeshName);
		REF_PTR_SET(Poly, that.Poly);
		REF_PTR_SET(Slot64, that.Slot64);
		REF_PTR_SET(Slot60, that.Slot60);

		for (int i = 0; i < 2; i++) {
			if (that.Vertex[i]) REF_PTR_SET(Vertex[i], that.Vertex[i]);
			if (that.Slot38[i]) REF_PTR_SET(Slot38[i], that.Slot38[i]);
			if (that.Slot40[i]) REF_PTR_SET(Slot40[i], that.Slot40[i]);
			if (that.Slot48[i]) REF_PTR_SET(Slot48[i], that.Slot48[i]);
		}

		REF_PTR_SET(PlaneEq, that.PlaneEq);
		REF_PTR_SET(VertexShadeIdx, that.VertexShadeIdx);
		REF_PTR_SET(VertexBoneLink, that.VertexBoneLink);
		REF_PTR_SET(Slot5c, that.Slot5c);

		// Clone the cull tree..
		REF_PTR_RELEASE(CullTree);
		if (that.CullTree) {
			CullTree = NEW_REF(AABTreeClass, ());
			*CullTree = *that.CullTree;
			CullTree->Set_Mesh(this);
		}
	}
	return *this;
}
