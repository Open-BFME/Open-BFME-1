// ?d_00375650@@YAXXZ
// partial score=0.98 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source
// stlport
// CastleBehavior::rva00375650, retail 0x00375650 (747 bytes).
//
// Owner: both callers (0x00376C70 and 0x00377060, via ILT 0x000279F8) pass
// their own this, a CastleBehavior (0x00376C70 hands the same register to the
// matched CastleBehavior::rva0036F4D0 first; both walk CastleBehavior's
// vectors at +0xB8/+0xC4/+0xDC), and push an Object. The body never reads
// this. The method name stays address-derived.
//
// What it does, read from the retail body: Zero Hour's
// PartitionManager::iteratePotentialCollisions expanded in place on a copy of
// the object's GeometryInfo (radius * 1.1f, PartitionFilterWouldCollide,
// FROM_BOUNDINGSPHERE_3D); every hit that is not INERT, MOVE_ONLY,
// BASE_FOUNDATION, WALK_ON_TOP_OF_WALL or IMMOBILE, is not held by the
// 0x001CF980 query's slot 104 and has an AI is ordered (command 0x36, as in
// BuildAssistant::moveObjectsForConstruction) to a point 1.5 query radii from
// the object's position, away from the object.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <math.h>

typedef bool Bool;
typedef float Real;

#define NULL 0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }

	void normalize();

	Real x;
	Real y;
	Real z;
};
#define BFME_HAVE_COORD3D

enum KindOfType
{
	KINDOF_IMMOBILE = 2,
	KINDOF_WALK_ON_TOP_OF_WALL = 59,
	KINDOF_INERT = 88,
	KINDOF_BASE_FOUNDATION = 103,
	KINDOF_MOVE_ONLY = 133
};

class Rva001CF980Result;
class GeometryInfo;

#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const; \
	const ThingTemplate *getTemplate() const; \
	const Coord3D *getPosition() const { return &m_cachedPos; } \
	Real getOrientation() const { return m_cachedAngle; }
#define OBJECT_TU_MEMBERS \
	Rva001CF980Result *queryAt001CF980(); \
	const GeometryInfo &getGeometryInfo() const \
	{ \
		return *reinterpret_cast<const GeometryInfo *>(m_geometryInfo); \
	}
#include "GameLogic/Object/object.h"

#include "GameLogic/command_source_type.h"

// BFME's 0x5C-byte GeometryInfo (GeometryInfoCopyConstructor.cpp).
class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &that);				///< 0x000FFD10
	virtual ~GeometryInfo();								///< 0x000FFCA0

	Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }

private:
	Bool m_isSmall;
	UnsignedInt m_word08;
	UnsignedInt m_word0c;
	Real m_radius10;
	Real m_boundingSphereRadius;
	UnsignedByte m_unmodelled18[0x44];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *_vptr;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(UnsignedInt)t >> 5] & (1 << ((UnsignedInt)t & 31))) != 0;
	}

private:
	UnsignedByte m_unmodelled08[0xc0];
	UnsignedInt m_kindof[6];							///< +0xC8 KindOfMaskType
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *tmpl = m_template;
	if (tmpl == 0)
		return 0;
	if (tmpl->m_nextOverride)
		tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
// BFME places AICommandInterface's vptr at AIUpdateInterface +0x20.
class AICommandParms;

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiBfmeCommand54(const Coord3D *pos, CommandSourceType cmdSource);	///< 0x000FFB80
};

class UpdateModule
{
public:
	virtual ~UpdateModule();

private:
	UnsignedByte m_unmodelled04[0x1c];
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
};

// The object Object::queryAt001CF980 selects; only slot 104 is used here.
#define RVA00375650_SLOT(n) virtual void slot##n();
class Rva001CF980Result
{
public:
	RVA00375650_SLOT(000) RVA00375650_SLOT(001) RVA00375650_SLOT(002) RVA00375650_SLOT(003)
	RVA00375650_SLOT(004) RVA00375650_SLOT(005) RVA00375650_SLOT(006) RVA00375650_SLOT(007)
	RVA00375650_SLOT(008) RVA00375650_SLOT(009) RVA00375650_SLOT(010) RVA00375650_SLOT(011)
	RVA00375650_SLOT(012) RVA00375650_SLOT(013) RVA00375650_SLOT(014) RVA00375650_SLOT(015)
	RVA00375650_SLOT(016) RVA00375650_SLOT(017) RVA00375650_SLOT(018) RVA00375650_SLOT(019)
	RVA00375650_SLOT(020) RVA00375650_SLOT(021) RVA00375650_SLOT(022) RVA00375650_SLOT(023)
	RVA00375650_SLOT(024) RVA00375650_SLOT(025) RVA00375650_SLOT(026) RVA00375650_SLOT(027)
	RVA00375650_SLOT(028) RVA00375650_SLOT(029) RVA00375650_SLOT(030) RVA00375650_SLOT(031)
	RVA00375650_SLOT(032) RVA00375650_SLOT(033) RVA00375650_SLOT(034) RVA00375650_SLOT(035)
	RVA00375650_SLOT(036) RVA00375650_SLOT(037) RVA00375650_SLOT(038) RVA00375650_SLOT(039)
	RVA00375650_SLOT(040) RVA00375650_SLOT(041) RVA00375650_SLOT(042) RVA00375650_SLOT(043)
	RVA00375650_SLOT(044) RVA00375650_SLOT(045) RVA00375650_SLOT(046) RVA00375650_SLOT(047)
	RVA00375650_SLOT(048) RVA00375650_SLOT(049) RVA00375650_SLOT(050) RVA00375650_SLOT(051)
	RVA00375650_SLOT(052) RVA00375650_SLOT(053) RVA00375650_SLOT(054) RVA00375650_SLOT(055)
	RVA00375650_SLOT(056) RVA00375650_SLOT(057) RVA00375650_SLOT(058) RVA00375650_SLOT(059)
	RVA00375650_SLOT(060) RVA00375650_SLOT(061) RVA00375650_SLOT(062) RVA00375650_SLOT(063)
	RVA00375650_SLOT(064) RVA00375650_SLOT(065) RVA00375650_SLOT(066) RVA00375650_SLOT(067)
	RVA00375650_SLOT(068) RVA00375650_SLOT(069) RVA00375650_SLOT(070) RVA00375650_SLOT(071)
	RVA00375650_SLOT(072) RVA00375650_SLOT(073) RVA00375650_SLOT(074) RVA00375650_SLOT(075)
	RVA00375650_SLOT(076) RVA00375650_SLOT(077) RVA00375650_SLOT(078) RVA00375650_SLOT(079)
	RVA00375650_SLOT(080) RVA00375650_SLOT(081) RVA00375650_SLOT(082) RVA00375650_SLOT(083)
	RVA00375650_SLOT(084) RVA00375650_SLOT(085) RVA00375650_SLOT(086) RVA00375650_SLOT(087)
	RVA00375650_SLOT(088) RVA00375650_SLOT(089) RVA00375650_SLOT(090) RVA00375650_SLOT(091)
	RVA00375650_SLOT(092) RVA00375650_SLOT(093) RVA00375650_SLOT(094) RVA00375650_SLOT(095)
	RVA00375650_SLOT(096) RVA00375650_SLOT(097) RVA00375650_SLOT(098) RVA00375650_SLOT(099)
	RVA00375650_SLOT(100) RVA00375650_SLOT(101) RVA00375650_SLOT(102) RVA00375650_SLOT(103)
	virtual Bool slot104();
};
#undef RVA00375650_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
// BFME filters: virtual destructor, allow, getPlayerMask, then the next link
// at +4 (vtable 0x01083B5C).
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

// vtable 0x010860A0; the Zero Hour members, as in moveObjectsForConstruction.
class PartitionFilterWouldCollide : public PartitionFilter
{
public:
	PartitionFilterWouldCollide(const Coord3D &pos, const GeometryInfo &geom,
		Real angle, Bool desired)
		: m_position(pos), m_geom(geom), m_angle(angle), m_desired(desired)
	{
	}
	virtual Bool allow(Object *obj);

	Coord3D m_position;
	const GeometryInfo &m_geom;
	Real m_angle;
	Bool m_desired;
};

// The owning query result: a pointer to the refcounted iterator payload.
struct SimpleObjectIteratorClump
{
	Object *m_object;
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
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}

	Object *next() const
	{
		if (m_mpo->m_cursor == m_mpo->m_entries.end())
			return NULL;
		SimpleObjectIteratorClump *cursor = m_mpo->m_cursor;
		Object *object = cursor->m_object;
		++cursor;
		m_mpo->m_cursor = cursor;
		return object;
	}
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0,
	FROM_CENTER_3D = 1,
	FROM_BOUNDINGSPHERE_2D = 2,
	FROM_BOUNDINGSPHERE_3D = 3
};

class PartitionManager;

// The 0x009F2960 range query, spelled as in clearRemovableForConstruction.
class BfmeWideForwardC
{
private:
	UnsignedByte m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Real b, Int c, Int d, Int e);
};

extern PartitionManager *ThePartitionManager;

class CastleBehavior
{
public:
	void rva00375650(Object *obj);
};

// ?rva00375650@CastleBehavior@@QAEXPAVObject@@@Z
void CastleBehavior::rva00375650(Object *obj)
{
	if (obj == NULL)
		return;

	Coord3D pos = *obj->getPosition();
	GeometryInfo geom = obj->getGeometryInfo();
	Real maxDist = geom.getBoundingSphereRadius() * 1.1f;	// just a little slop

	const BfmeWideResult &iter =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(Int)&pos,
			maxDist,
			FROM_BOUNDINGSPHERE_3D,
			(Int)&PartitionFilterWouldCollide(pos, geom, obj->getOrientation(), true),
			0);

	Object *them;
	while ((them = iter.next()) != NULL)
	{
		if (them->getTemplate()->isKindOf(KINDOF_INERT))
			continue;
		if (them->getTemplate()->isKindOf(KINDOF_MOVE_ONLY))
			continue;
		if (them->getTemplate()->isKindOf(KINDOF_BASE_FOUNDATION))
			continue;
		if (them->getTemplate()->isKindOf(KINDOF_WALK_ON_TOP_OF_WALL))
			continue;
		if (them->isKindOf(KINDOF_IMMOBILE))
			continue;

		Rva001CF980Result *result = them->queryAt001CF980();
		if (result && result->slot104())
			continue;

		AIUpdateInterface *ai = them->m_ai;
		if (ai == NULL)
			continue;

		Coord3D dir = *them->getPosition();
		dir.z = 0.0f;
		dir.x -= obj->getPosition()->x;
		dir.y -= obj->getPosition()->y;
		if (sqrtf(dir.x * dir.x + dir.y * dir.y) > 0.0f)
		{
			dir.normalize();
		}
		else
		{
			dir.y = 0.0f;
			dir.x = 1.0f;
		}

		Real dist = maxDist * 1.5f;
		dir.y *= dist;
		dir.z *= dist;

		Coord3D dest;
		dest.x = pos.x + dir.x * dist;
		dest.y = pos.y + dir.y;
		dest.z = pos.z + dir.z;
		ai->aiBfmeCommand54(&dest, CMD_FROM_AI);
	}
}
