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

#include "../../../Include/Common/ScalarTypes.h"



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

// Locomotor +0x44 is read as a length by the airspace sampler below; ZH has
// m_offsetIncrement there, which BFME may have moved, so it keeps its offset.
class Locomotor
{
public:
	unsigned char m_pad[0x44];
	Real m_unknown44;
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

	unsigned char m_pad004[0x1cc - 4];
	Locomotor *m_curLocomotor;
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

// retired debt: ??_7PartitionFilterWouldCollide@?A0x47eb9fc7@@6B@ replaced with ??_7PartitionFilterWouldCollide@@6B@
// Retail vftable 0x010860A0 is recorded as ??_7PartitionFilterWouldCollide@@6B@;
// the class keeps that name outside an anonymous namespace, whose decorated
// name changes with the source path.
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

#include "../../../Include/Common/Enums/DistanceCalculationType.h"







class PartitionManager
{
};

class BfmeWideForwardC
{
private:
	unsigned char m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);
};

extern PartitionManager *ThePartitionManager;

class AerialPathfinder
{
public:
	Bool rva00148C70SeparationPush(Object *obj, const Coord3D *pos,
		Real *worstOverlap, Coord3D *push);
	Bool rva00149010Query(Object *obj, class BfmeObjGK *query, Real range,
		Real lowering);
	Bool rva00148800(class BfmeObjGK *query, Real range, Coord3D *result);
	Real getNoFlyZoneHeight(Real x, Real y);
	Int rva00149130SampleAirspace(Object *object, const Coord3D *position,
		Coord3D *result);
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
			*(Int *)&radius,
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

// The query record the 0x00148800 range check reads; this body only tests its
// ready flag at +0x24.
class BfmeObjGK
{
public:
	unsigned char m_pad00[0x24];
	Bool m_ready;
	Bool isReady() const { return m_ready; }
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = NULL) const;
};

extern TerrainLogic *TheTerrainLogic;
extern AerialPathfinder *TheAerialPathfinder;

// The 0.5 at VA 0x01094A50 is a named constant of the AerialPathfinder bodies
// (only 0x00149010, 0x00149130 and two later ones read it), not the shared
// __real@3f000000 literal at 0x0107533C.
extern const Real g_rva01094A50;

// AerialPathfinder member at retail 0x00149010 (219 bytes, ret 0x10), called
// on TheAerialPathfinder by the matched Giant Bird selector 0x002BC9C0. When
// the object has an AI and the query record is ready, it takes the queried
// position, lowers it by half of `lowering`, and succeeds only if that point
// is above the ground and the separation pass (0x00148C70) finds no overlap;
// a missing AI, an unready record or a failed range check also succeed.
// Retail calls the 0x00148800 range check with ECX still holding `this`
// (as the 0x002BC9C0 selector does with TheAerialPathfinder), so it is an
// AerialPathfinder thiscall member here; the body never reads ECX.
// The method's real name is not proven, so it keeps the address token.
// ?rva00149010Query@AerialPathfinder@@QAE_NPAVObject@@PAVBfmeObjGK@@MM@Z
Bool AerialPathfinder::rva00149010Query(Object *obj, BfmeObjGK *query,
	Real range, Real lowering)
{
	if (obj->getAI() == NULL)
		return true;
	if (!query->isReady())
		return true;

	Coord3D pos;
	if (!rva00148800(query, range, &pos))
		return true;

	pos.z -= lowering * g_rva01094A50;
	Bool aboveGround = false;
	Bool clear = false;
	if (TheTerrainLogic->getGroundHeight(pos.x, pos.y) < pos.z)
		aboveGround = true;

	Real worstOverlap = 0.0f;
	Coord3D push;
	push.x = 0.0f;
	push.y = 0.0f;
	push.z = 0.0f;
	if (TheAerialPathfinder->rva00148C70SeparationPush(obj, &pos, &worstOverlap, &push))
		clear = true;

	return (aboveGround == true && clear == true) ? true : false;
}

// ?g_rva01094A50@@3MB
extern const Real g_rva01094A50 = 0.5f;

// Height of the higher of terrain and no-fly ceiling above pt.z.
inline Real Rva00149130HeightAbove(AerialPathfinder *self, const Coord3D &pt)
{
	Real terrain = TheTerrainLogic->getGroundHeight(pt.x, pt.y, 0);
	Real noFly = self->getNoFlyZoneHeight(pt.x, pt.y);
	return (noFly > terrain ? noFly : terrain) - pt.z;
}

// Retail 0x00149130 (657 bytes, ret 0x0C), called five times by 0x00149470.
// Samples terrain and no-fly ceiling at the centre and four corners offset by
// the object's bounding-sphere radius, lifts the result by the highest
// clearance found, lets rva00148C70SeparationPush add its push, and returns
// whether any clearance was needed. It shares this TU with the separation
// push: with that body visible VC7.1 knows `best` does not escape through it
// and hoists TheTerrainLogic's vtable load above best = 0, as retail does.
// The method's real name is not proven, so it keeps the address token.
// ?rva00149130SampleAirspace@AerialPathfinder@@QAEHPAVObject@@PBUCoord3D@@PAU3@@Z
Int AerialPathfinder::rva00149130SampleAirspace(Object *object,
	const Coord3D *position, Coord3D *result)
{
	AIUpdateInterface *ai = object->getAI();
	if (ai == 0)
		return 2;

	result->x = 0.0f;
	result->y = 0.0f;
	result->z = 0.0f;

	Real best;
	Real sampleRadius = ai->m_curLocomotor->m_unknown44;
	Real halfRadius = sampleRadius * 0.5f;
	Real objectRadius = object->getGeometryInfo().getBoundingSphereRadius();
	Coord3D pt;
	Real height;
	{
		pt.x = position->x;
		pt.y = position->y;
		pt.z = position->z - halfRadius;
		best = 0.0f;
		height = Rva00149130HeightAbove(this, pt);
		if (0.0f < height)
			best = height;
	}
	{
		pt.x = position->x - objectRadius;
		pt.y = position->y - objectRadius;
		pt.z = position->z - sampleRadius * 0.3885f;
		height = Rva00149130HeightAbove(this, pt);
		if (best < height)
			best = height;
	}
	{
		pt.y = position->y + objectRadius;
		height = Rva00149130HeightAbove(this, pt);
		if (best < height)
			best = height;
	}
	{
		pt.x = position->x + objectRadius;
		height = Rva00149130HeightAbove(this, pt);
		if (best < height)
			best = height;
	}
	{
		Real sampleY = position->y - objectRadius;
		Real terrain = TheTerrainLogic->getGroundHeight(pt.x, sampleY, 0);
		Real noFly = getNoFlyZoneHeight(pt.x, sampleY);
		height = (noFly > terrain ? noFly : terrain) - pt.z;
		if (best < height)
			best = height;
	}
	result->z += best;
	rva00148C70SeparationPush(object, position, &best, result);
	return best > 0.0f;
}
