// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <math.h>

// AerialPathfinder member at retail 0x00148C70 (737 bytes, ret 0x10).
//
// Identity: both callers load the receiver as an AerialPathfinder (0x00149010
// through TheAerialPathfinder at 0x012EF1F8; 0x00149130 passes its own
// AerialPathfinder `this`) and push four arguments (Object*, position,
// Real* worst overlap, Coord3D* accumulated push).  The method's real name is
// not proven, so it keeps the address token.
//
// The body queries the partition manager with the same inlined
// PartitionFilterWouldCollide temporary and BfmeWideResult handle as the
// matched BuildAssistant::clearRemovableForConstruction (0x000FF4D0): same
// filter vtable 0x010860A0, same three unwind states.  For every other
// object in range it measures the overlap of the two bounding spheres, keeps
// the worst overlap and adds the separation vector scaled by the overlap to
// the caller's push; it returns false when anything overlapped.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef Int ObjectID;

#define NULL 0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void normalize();
};

// The opaque position-delta helper at 0x00148990 returns this view.
class BfmeVec3DG : public Coord3D
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *_vptr;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GeometryInfo.h
class GeometryInfo
{
public:
	Real getBoundingSphereRadius() const
	{
		return m_boundingSphereRadius;
	}

private:
	unsigned char m_pad[0x14];
	Real m_boundingSphereRadius;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	UnsignedInt getKindOfWord(Int word) const
	{
		return m_kindof[word];
	}

private:
	unsigned char m_pad[0xc0];
	UnsignedInt m_kindof[4];
};

// The object the AI pointer's slot-83 virtual hands back; only the ObjectID
// at +0x3F8 is read here.
class Rva00148C70AIPartner
{
private:
	unsigned char m_pad[0x3f8];

public:
	ObjectID m_id3f8;
};

class AIUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual Rva00148C70AIPartner *slot83();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	// Zero Hour reads the template through OVERRIDE<ThingTemplate>::operator->,
	// with the first level of Overridable::getFinalOverride inlined.
	const ThingTemplate *getTemplate() const
	{
		if (!m_template)
			return NULL;
		if (m_template->m_nextOverride)
			return static_cast<const ThingTemplate *>(
				m_template->m_nextOverride->getFinalOverride());
		return m_template;
	}

	const Coord3D *getPosition() const
	{
		return &m_cachedPos;
	}

	Real getOrientation() const
	{
		return m_cachedAngle;
	}

private:
	void *_vptr;
	const ThingTemplate *m_template;
	unsigned char m_transform[0x30];
	Coord3D m_cachedPos;
	Real m_cachedAngle;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	UnsignedInt getKindOfWord(Int word) const
	{
		return getTemplate()->getKindOfWord(word);
	}

	ObjectID getID() const
	{
		return m_id;
	}

	const GeometryInfo &getGeometryInfo() const
	{
		return m_geometryInfo;
	}

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

private:
	unsigned char m_pad48[0x74 - 0x48];
	ObjectID m_id;
	unsigned char m_pad78[0xac - 0x78];
	GeometryInfo m_geometryInfo;
	unsigned char m_padc4[0x204 - 0xc4];
	AIUpdateInterface *m_ai;
};

class Gen_00148990
{
public:
	BfmeVec3DG bfmeDelta(const BfmeVec3DG *point) const;
};

// The result wrapper points to this vector payload and its ownership count.
struct SimpleObjectIteratorClump
{
	Int m_valueBits;
	Int m_distanceBits;
};

struct SimpleObjectIterator
{
	_STL::vector<SimpleObjectIteratorClump> m_entries;
	SimpleObjectIteratorClump *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
public:
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);

	Object *next(void) const
	{
		if (m_mpo->m_cursor == m_mpo->m_entries.end())
			return NULL;
		SimpleObjectIteratorClump *cursor = m_mpo->m_cursor;
		Object *object = reinterpret_cast<Object *>(cursor->m_valueBits);
		++cursor;
		m_mpo->m_cursor = cursor;
		return object;
	}

	~BfmeWideResult()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilter
{
public:
	PartitionFilter() : m_base(0) { }
	virtual ~PartitionFilter() { }
	virtual Bool allow(Object *obj) = 0;

private:
	UnsignedInt m_base;
};

class PartitionFilterWouldCollide : public PartitionFilter
{
public:
	PartitionFilterWouldCollide(const Coord3D &pos, const GeometryInfo *geometry,
		Real angle, Bool desired)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_position.z = pos.z;
		m_geometry = geometry;
		m_angle = angle;
		m_desired = desired;
	}

	virtual Bool allow(Object *obj)
	{
		return false;
	}

	operator Int()
	{
		return (Int)this;
	}

private:
	Coord3D m_position;
	const GeometryInfo *m_geometry;
	Real m_angle;
	Bool m_desired;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1,
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

class PartitionManager
{
};

class BfmeWideForwardC
{
private:
	unsigned char m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Real b, Int c, Int d, Int e);
};

extern PartitionManager *ThePartitionManager;

class AerialPathfinder
{
public:
	Bool rva00148C70SeparationPush(Object *obj, const Coord3D *pos,
		Real *worstOverlap, Coord3D *push);
};

// ?rva00148C70SeparationPush@AerialPathfinder@@QAE_NPAVObject@@PBUCoord3D@@PAMPAU3@@Z
Bool AerialPathfinder::rva00148C70SeparationPush(Object *obj,
	const Coord3D *pos, Real *worstOverlap, Coord3D *push)
{
	Bool clear = true;
	Real radius = obj->getGeometryInfo().getBoundingSphereRadius();
	ObjectID partnerID = 0;
	if (obj->getAI() != NULL)
	{
		Rva00148C70AIPartner *partner = obj->getAI()->slot83();
		if (partner != NULL)
			partnerID = partner->m_id3f8;
	}

	const BfmeWideResult &found =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(Int)pos,
			radius,
			FROM_BOUNDINGSPHERE_3D,
			PartitionFilterWouldCollide(*pos, &obj->getGeometryInfo(),
				obj->getOrientation(), true),
			0);
	Object *them;
	while ((them = found.next()) != NULL)
	{
		if (them == obj)
			continue;
		if (partnerID != 0 && partnerID == them->getID())
			continue;
		if ((them->getKindOfWord(0) & 0x100) != 0)
			continue;
		if ((them->getKindOfWord(0) & 0x200) != 0)
			continue;
		if ((them->getKindOfWord(3) & 0x1000) != 0)
			continue;
		if ((them->getKindOfWord(0) & 0x4) == 0)
		{
			Real dx = them->getPosition()->x - obj->getPosition()->x;
			Real dy = them->getPosition()->y - obj->getPosition()->y;
			Real dz = them->getPosition()->z - obj->getPosition()->z;
			Real range = radius * 1.2f;
			if (dx * dx + dy * dy + dz * dz > range * range)
				continue;
		}

		BfmeVec3DG delta = ((const Gen_00148990 *)them)->bfmeDelta(
			(const BfmeVec3DG *)pos);
		Real overlap = them->getGeometryInfo().getBoundingSphereRadius() * 2.0f
			+ obj->getGeometryInfo().getBoundingSphereRadius()
			- (Real)sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
		if (*worstOverlap < overlap)
			*worstOverlap = overlap;
		delta.normalize();
		clear = false;
		delta.x *= overlap;
		delta.y *= overlap;
		delta.z *= overlap;
		push->x += delta.x;
		push->y += delta.y;
		push->z += delta.z;
	}

	return clear;
}
