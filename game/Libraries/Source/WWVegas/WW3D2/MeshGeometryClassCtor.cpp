// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Lift MeshGeometryClass' default constructor at retail 0x00924880 to clean C++.
//
// This local ABI slice preserves the BFME field offsets proven by the constructor's
// stores and by MeshGeometryClass' landed copy constructor. The production header
// carries later layout edits used by other methods, so the constructor stays isolated.

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

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	MeshGeometryClass(void);
	virtual ~MeshGeometryClass(void);

protected:
	void * UserText;
	void * MeshName;
	int Flags;
	char SortLevel;
	uint32 W3dAttributes;
	int PolyCount;
	int VertexCount;
	void * Poly;
	void * Vertex;
	void * Slot34;
	void * Slot38;
	void * Slot3c;
	void * Slot40;
	void * Slot44;
	void * Slot48;
	void * Slot4c;
	void * Slot50;
	void * Slot54;
	void * Slot58;
	void * Slot5c;
	void * Slot60;
	void * Slot64;
	Vector3 BoundBoxMin;
	Vector3 BoundBoxMax;
	SphereClass BoundSphere;
	AABTreeClass * CullTree;
};

MeshGeometryClass::MeshGeometryClass(void) :
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
	BoundBoxMin(0, 0, 0),
	BoundBoxMax(1, 1, 1),
	BoundSphere(Vector3(0, 0, 0), 1),
	CullTree(NULL)
{
	Vertex = NULL;
	Slot40 = NULL;
	Slot38 = NULL;
	Slot48 = NULL;
	Slot34 = NULL;
	Slot44 = NULL;
	Slot3c = NULL;
	Slot4c = NULL;
}
