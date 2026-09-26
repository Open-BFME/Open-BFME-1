// cl: /DNDEBUG /MD /EHsc

// The five bodies that reach Object's GeometryInfo at +0xAC:
//
//   ObjectGeometryBoundsShim::getMin  0x001BFC20  position minus the extents
//   ObjectGeometryBoundsShim::getMax  0x001BFC80  position plus the extents
//   Object::bfmeGeometryIntersects    0x001BE980  two oriented footprints
//   Object::lazySet                   0x001D5C20  clone the embedded one, then assign
//   Object::setGeometryInfo           0x001D5D20  assign, then notify four helpers
//
// Five files, and they contradicted each other about how big that field is.
// bfmeGeometryIntersects declared GeometryInfo as 0x20 bytes; getMin and getMax
// only ever reached +0x10 of it; lazySet and setGeometryInfo did not call it
// GeometryInfo at all but BfmeCopyElementA, 0x5C bytes.
//
// 0x5C is right, and lazySet proves it twice in four instructions: it compares
// the pointer at +0x108 against `lea eax,[esi+0xAC]`, so the embedded object
// spans +0xAC..+0x107, and when they are equal it allocates a fresh one with
// `push 0x5C; call ??2@YAPAXI@Z`. 0xAC + 0x5C = 0x108 exactly. setGeometryInfo
// then assigns into +0xAC through the same ILT (0x00003828) lazySet uses, so the
// thing lazySet clones and the thing setGeometryInfo assigns are one type -- and
// setGeometryInfo's OWN row name calls it GeometryInfo.
//
// The two spellings both have to stay, because each is inside a decorated name
// that has to resolve: `ABVGeometryInfo@@` in ?setGeometryInfo@Object@@, and
// `?bfmeAssign@BfmeCopyElementA@@QAEPAU1@PAU1@@Z` for the assign itself -- a
// class and a struct, so not even a spelling a typedef could bridge. What the
// merge can do, and does, is give them one size and say here that they are one
// field.
//
// ObjectGeometryBoundsShim is a sub-object at Object+0x70: getMin reads the
// position at `[ecx-0x38]`, which is Object+0x38, and the geometry at
// `[ecx+0x3C]`, which is Object+0xAC. Its two files each carried a private copy
// of Object under the name ObjectGeometryBoundsData; there is one Object here
// and the shim reaches it as a friend.
//
// The layout the five settle, all of it read off the bytes:
//
//   +0x038  m_position          getMin/getMax/bfmeGeometryIntersects
//   +0x044  m_orientation       bfmeGeometryIntersects
//   +0x070  the bounds shim
//   +0x0AC  m_geometryInfo      0x5C bytes
//   +0x108  m_geometryClone     null until lazySet clones
//   +0x3B0  m_partitionData     same field ObjectStatusBits.cpp names at +0x3B0
//   +0x3B4  +0x3B8             two unidentified helpers, each with an init()
//
// setGeometryInfo's fourth notification goes to +0x80, which
// ObjectModelConditions.cpp names m_drawable. The callee keeps its BfmeBCNG
// spelling because that is the name its pin resolves under.

typedef bool Bool;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
	void set(Real xIn, Real yIn, Real zIn)
	{
		x = xIn;
		y = yIn;
		z = zIn;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	Real getMaxHeightBelowPosition() const;
	Bool bfmeIntersects(const Coord3D &thisPosition, Real thisAngle,
		const GeometryInfo &otherGeometry, const Coord3D &otherPosition,
		Real otherAngle) const;

	inline Real getMajorRadius() const { return m_majorRadius; }

private:
	unsigned char m_unmodelled_000[0x10];
	Real m_majorRadius;				// +0x10
	unsigned char m_unmodelled_014[0x5c - 0x14];
};

// The same 0x5C bytes as GeometryInfo, under the spelling the copy-assign body is
// pinned as: ?bfmeAssign@BfmeCopyElementA@@QAEPAU1@PAU1@@Z.
struct BfmeCopyElementA
{
	BfmeCopyElementA();
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *other);

private:
	char m_bytes[0x5c];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void makeDirty();
};

class Rva009A2350
{
public:
	void init();
};

class Rva009F2BA0
{
public:
	void init();
};

// The object at +0x80, which ObjectModelConditions.cpp names m_drawable.
class BfmeBCNG
{
public:
	void bfmeThreeCNG();
};

class ObjectGeometryBoundsShim;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool bfmeGeometryIntersects(const Object *other) const;
	void lazySet(void *arg);
	void setGeometryInfo(const GeometryInfo &geom);

private:
	friend class ObjectGeometryBoundsShim;

	unsigned char m_unmodelled_000[0x38];
	Coord3D m_position;				// +0x038
	Real m_orientation;				// +0x044
	unsigned char m_unmodelled_048[0x80 - 0x48];
	BfmeBCNG *m_drawable;				// +0x080
	unsigned char m_unmodelled_084[0xac - 0x84];
	GeometryInfo m_geometryInfo;			// +0x0AC, 0x5C bytes
	BfmeCopyElementA *m_geometryClone;		// +0x108
	unsigned char m_unmodelled_10c[0x3b0 - 0x10c];
	PartitionData *m_partitionData;			// +0x3B0
	Rva009F2BA0 *m_helper3b4;			// +0x3B4
	Rva009A2350 *m_helper3b8;			// +0x3B8
};

// The bounds accessors live on a sub-object at Object+0x70 and reach the Object
// by that fixed displacement.
class ObjectGeometryBoundsShim
{
public:
	void getMin(Coord3D &out) const;
	void getMax(Coord3D &out) const;

	__forceinline const Object *getObject() const
	{
		return reinterpret_cast<const Object *>(
			reinterpret_cast<const char *>(this) - 0x70);
	}
};

// ?getMin@ObjectGeometryBoundsShim@@QBEXAAUCoord3D@@@Z
void ObjectGeometryBoundsShim::getMin(Coord3D &out) const
{
	const Object *object = getObject();
	const GeometryInfo &geometry = object->m_geometryInfo;
	Coord3D result;
	result.x = object->m_position.x;
	result.y = object->m_position.y;
	result.z = object->m_position.z;
	result.z -= geometry.getMaxHeightBelowPosition();
	result.x -= geometry.getMajorRadius();
	result.y -= geometry.getMajorRadius();
	out.set(result.x, result.y, result.z);
}

// ?getMax@ObjectGeometryBoundsShim@@QBEXAAUCoord3D@@@Z
void ObjectGeometryBoundsShim::getMax(Coord3D &out) const
{
	const Object *object = getObject();
	const GeometryInfo &geometry = object->m_geometryInfo;
	Coord3D result;
	result.x = object->m_position.x;
	result.y = object->m_position.y;
	result.z = object->m_position.z;
	result.z += geometry.getMaxHeightAbovePosition();
	result.x += geometry.getMajorRadius();
	result.y += geometry.getMajorRadius();
	out.set(result.x, result.y, result.z);
}

// ?bfmeGeometryIntersects@Object@@QBE_NPBV1@@Z
//
// The public retail spelling of this BFME-only operation has not survived, so the
// bfme prefix records that the identity is descriptive; the field layout and
// argument order are proven by the exact call sequence.
Bool Object::bfmeGeometryIntersects(const Object *other) const
{
	// These temporaries preserve retail's VC7.1 x87 spill and push order.
	Real otherAngle = other->m_orientation;
	Real thisAngle = m_orientation;
	return m_geometryInfo.bfmeIntersects(m_position, thisAngle,
		other->m_geometryInfo, other->m_position, otherAngle);
}

// ?lazySet@Object@@QAEXPAX@Z
//
// Until something sets it, the pointer at +0x108 aims at the embedded geometry,
// so the first write clones it out to the heap rather than scribbling on the
// shared one.
void Object::lazySet(void *arg)
{
	if (m_geometryClone == reinterpret_cast<BfmeCopyElementA *>(&m_geometryInfo))
		m_geometryClone = new BfmeCopyElementA;
	m_geometryClone->bfmeAssign((BfmeCopyElementA *)arg);
}

// ?setGeometryInfo@Object@@QAEXABVGeometryInfo@@@Z
//
// Assign, then notify four optional helpers in retail's order: +0x3B0, +0x3B8,
// +0x3B4, +0x80.
void Object::setGeometryInfo(const GeometryInfo &geom)
{
	reinterpret_cast<BfmeCopyElementA *>(&m_geometryInfo)->bfmeAssign(
		(BfmeCopyElementA *)&geom);

	if (m_partitionData)
		m_partitionData->makeDirty();

	if (m_helper3b8)
		m_helper3b8->init();

	if (m_helper3b4)
		m_helper3b4->init();

	if (m_drawable)
		m_drawable->bfmeThreeCNG();
}
