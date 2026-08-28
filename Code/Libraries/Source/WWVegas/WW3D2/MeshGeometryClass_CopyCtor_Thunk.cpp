// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Lift MeshGeometryClass' copy constructor (0x9267E0) to clean C++.
//
// Local ABI-slice replica: the real meshgeometry.h lays the members out at the
// Zero Hour offsets, which retail does not use.  Retail's own stores pin the
// BFME layout (see the member comments below) and three already-landed bodies
// corroborate it: Get_Bounding_Box's thunk puts BoundBoxMin/BoundBoxMax at
// this+0x68/+0x74, read_user_text's notes put UserText at this+0x10 with
// MeshName at this+0x14, and AABTreeClass::Update_Min_Max (0x96AFC0, still
// unconverted) reads the polygon and vertex ShareBuffers at mesh+0x2c and
// mesh+0x30 -- a uniform -4 from the Zero Hour header, which is exactly what
// moving UserText down to +0x10 produces.
//
// Only the offsets are proven.  Zero Hour's VertexNorm, PlaneEq,
// VertexShadeIdx, VertexBoneLink and PolySurfaceType are five of the twelve
// pointer slots between +0x34 and +0x64, but which five is not settled by this
// body -- the names below are deliberately neutral where the evidence is.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "sphere.h"
#include "multilist.h"

class AABTreeClass;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	MeshGeometryClass(const MeshGeometryClass & that);
	virtual ~MeshGeometryClass(void);
	MeshGeometryClass & operator = (const MeshGeometryClass & that);


protected:
	void *			                    UserText;			///< retail this+0x10
	void *			                    MeshName;			///< retail this+0x14
	int										Flags;				///< retail this+0x18
	char										SortLevel;			///< retail this+0x1c
	uint32									W3dAttributes;		///< retail this+0x20
	int										PolyCount;			///< retail this+0x24
	int										VertexCount;		///< retail this+0x28
	void *		                    Poly;					///< retail this+0x2c
	void *									Vertex;			///< retail this+0x30
	void *									Slot34;			///< retail this+0x34
	void *									Slot38;			///< retail this+0x38
	void *									Slot3c;			///< retail this+0x3c
	void *									Slot40;			///< retail this+0x40
	void *									Slot44;			///< retail this+0x44
	void *									Slot48;			///< retail this+0x48
	void *									Slot4c;			///< retail this+0x4c
	void *		                    Slot50;				///< retail this+0x50
	void *		                    Slot54;				///< retail this+0x54
	void *		                    Slot58;				///< retail this+0x58
	void *			                    Slot5c;				///< retail this+0x5c
	void *			                    Slot60;				///< retail this+0x60
	void *			                    Slot64;				///< retail this+0x64
	Vector3									BoundBoxMin;		///< retail this+0x68
	Vector3									BoundBoxMax;		///< retail this+0x74
	SphereClass								BoundSphere;		///< retail this+0x80 (centre) and +0x8c (radius)
	AABTreeClass *							CullTree;			///< retail this+0x90
};

// ??0MeshGeometryClass@@QAE@ABV0@@Z
MeshGeometryClass::MeshGeometryClass(const MeshGeometryClass & that) :
	UserText(NULL),
	MeshName(NULL),
	Flags(0),
	SortLevel(0),
	W3dAttributes(0),
	PolyCount(0),
	VertexCount(0),
	Poly(NULL),
	Slot50(NULL),
	Slot54(NULL),
	Slot58(NULL),
	Slot5c(NULL),
	Slot60(NULL),
	Slot64(NULL),
	BoundBoxMin(0,0,0),
	BoundBoxMax(1,1,1),
	BoundSphere(Vector3(0,0,0),1),
	CullTree(NULL)
{
	// Retail clears these eight -- and only these eight -- after everything the
	// member-initialiser list covers, in the order 0x30, 0x40, 0x38, 0x48, 0x34,
	// 0x44, 0x3c, 0x4c.  That is the eight-element block walked in bit-reversed
	// index order, which is why they are written out longhand: any in-order
	// spelling schedules differently and loses the byte match.
	Vertex = NULL;
	Slot40 = NULL;
	Slot38 = NULL;
	Slot48 = NULL;
	Slot34 = NULL;
	Slot44 = NULL;
	Slot3c = NULL;
	Slot4c = NULL;
	*this = that;
}
