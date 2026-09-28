// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
// readable body of ?moveObjectsForConstruction@BuildAssistant@@: game/GameEngine/Source/Common/System/BuildAssistant.cpp
//
// BuildAssistant::moveObjectsForConstruction, retail 0x001012B0 (1109 bytes).
//
// Identity: the matched caller Rva00101820::buildObjectNow (0x00101820) calls
// it through ILT 0x0002EDC5 with the template, position, angle and player,
// and the body is Zero Hour's algorithm step for step: a GEOMETRY_BOX 10-high
// GeometryInfo sized from the template, replaced by the template's own
// geometry when that is a single box; a collision query; skip the objects a
// building may overlap; NEUTRAL or ALLIES objects with an AI are sent to a
// random point 0.5..1.5 radii away (line 1825 and 1828 random calls, the
// BuildAssistant.cpp path literal) and anything else makes the answer false.
//
// BFME differences, all read from the retail body:
//  * the radius is the template geometry's +0x10 radius times 1.4 (Zero Hour
//    computed sqrt(major^2 + minor^2) * 1.4), and before the collision query
//    BFME runs one all-object query on a position/radius filter whose result
//    it discards;
//  * PartitionManager::iteratePotentialCollisions is expanded in place with a
//    linked filter chain (PartitionFilter::link) and three more filters:
//    must be SELECTABLE, must not be INERT, MOVE_ONLY, BASE_FOUNDATION or
//    WALK_ON_TOP_OF_WALL. The chain's temporaries die right after the query,
//    so the owning result is bound to a reference, as in the matched
//    clearRemovableForConstruction (0x000FF4D0);
//  * the skip tests are IMMOBILE, ALWAYS_SELECTABLE, then an inlined
//    isRemovableForConstruction (not INERT and SHRUBBERY, CLEARED_BY_BUILD or
//    effectively dead). Thing::isKindOf is out of line in BFME (0x000A2CF0)
//    and only CLEARED_BY_BUILD calls it; the others test the template's bits;
//  * an object whose 0x001CF980 query answers slot 104 true, or whose AI
//    reports bfmeBlocksFormationRefresh, is left in place.
// Kind names come from retail's KindOf name table at VA 0x012AA068.
//
// Shape notes, each measured against the retail bytes: the mask constructor
// at 0x000C4BC0 and the kind filter's copy constructor are nothrow calls
// (retail stores no unwind state around them), the kind filter constructor
// body is visible so its mask temporaries share the first filter's slot, the
// one-index mask is a real bitset, and Coord3D's copy constructor copies the
// three members in order.

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>
#include "vector3.h"

typedef bool Bool;
typedef float Real;

#define NULL 0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
// A struct, as the pinned caller's mangled name (PBUCoord3D) requires.
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }

	Real x;
	Real y;
	Real z;
};
#define BFME_HAVE_COORD3D

enum KindOfType
{
	KINDOF_SELECTABLE = 1,
	KINDOF_IMMOBILE = 2,
	KINDOF_SHRUBBERY = 6,
	KINDOF_CLEARED_BY_BUILD = 50,
	KINDOF_ALWAYS_SELECTABLE = 57,
	KINDOF_WALK_ON_TOP_OF_WALL = 59,
	KINDOF_INERT = 88,
	KINDOF_BASE_FOUNDATION = 103,
	KINDOF_MOVE_ONLY = 133
};

class Rva001CF980Result;
class Team;

#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const; \
	const ThingTemplate *getTemplate() const;
#define OBJECT_TU_MEMBERS \
	Rva001CF980Result *queryAt001CF980(); \
	Team *getTeam() const { return m_team; }
#include "GameLogic/Object/object.h"

#include "GameLogic/command_source_type.h"

extern Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

// BFME's 0x5C-byte GeometryInfo (see GeometryInfoConstructor.cpp). Only the
// radius at +0x10 and the bounding-sphere radius at +0x14 are read here.
class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);
	virtual ~GeometryInfo();								///< 0x000FFCA0
	GeometryInfo &operator=(const GeometryInfo &that);		///< 0x00100300

	// 0x0087E8D0: true when the shape list holds exactly one GEOMETRY_BOX.
	Bool rva0087E8D0() const;

	Real getRadiusAt10() const { return m_radius10; }
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
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(UnsignedInt)t >> 5] & (1 << ((UnsignedInt)t & 31))) != 0;
	}

private:
	UnsignedByte m_unmodelled08[0x58];
	GeometryInfo m_geometryInfo;						///< +0x60
	UnsignedByte m_unmodelledBC[0x0c];
	UnsignedInt m_kindof[3];							///< +0xC8
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

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player
{
public:
	Relationship getRelationship(const Team *that) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
// BFME places AICommandInterface's vptr at AIUpdateInterface +0x20, as in
// BuildAssistant_sellObject.cpp.
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
public:
	Bool bfmeBlocksFormationRefresh();					///< 0x00278830
};

// The object Object::queryAt001CF980 selects; only slot 104 is used here.
#define RVA001012B0_SLOT(n) virtual void slot##n();
class Rva001CF980Result
{
public:
	RVA001012B0_SLOT(000) RVA001012B0_SLOT(001) RVA001012B0_SLOT(002) RVA001012B0_SLOT(003)
	RVA001012B0_SLOT(004) RVA001012B0_SLOT(005) RVA001012B0_SLOT(006) RVA001012B0_SLOT(007)
	RVA001012B0_SLOT(008) RVA001012B0_SLOT(009) RVA001012B0_SLOT(010) RVA001012B0_SLOT(011)
	RVA001012B0_SLOT(012) RVA001012B0_SLOT(013) RVA001012B0_SLOT(014) RVA001012B0_SLOT(015)
	RVA001012B0_SLOT(016) RVA001012B0_SLOT(017) RVA001012B0_SLOT(018) RVA001012B0_SLOT(019)
	RVA001012B0_SLOT(020) RVA001012B0_SLOT(021) RVA001012B0_SLOT(022) RVA001012B0_SLOT(023)
	RVA001012B0_SLOT(024) RVA001012B0_SLOT(025) RVA001012B0_SLOT(026) RVA001012B0_SLOT(027)
	RVA001012B0_SLOT(028) RVA001012B0_SLOT(029) RVA001012B0_SLOT(030) RVA001012B0_SLOT(031)
	RVA001012B0_SLOT(032) RVA001012B0_SLOT(033) RVA001012B0_SLOT(034) RVA001012B0_SLOT(035)
	RVA001012B0_SLOT(036) RVA001012B0_SLOT(037) RVA001012B0_SLOT(038) RVA001012B0_SLOT(039)
	RVA001012B0_SLOT(040) RVA001012B0_SLOT(041) RVA001012B0_SLOT(042) RVA001012B0_SLOT(043)
	RVA001012B0_SLOT(044) RVA001012B0_SLOT(045) RVA001012B0_SLOT(046) RVA001012B0_SLOT(047)
	RVA001012B0_SLOT(048) RVA001012B0_SLOT(049) RVA001012B0_SLOT(050) RVA001012B0_SLOT(051)
	RVA001012B0_SLOT(052) RVA001012B0_SLOT(053) RVA001012B0_SLOT(054) RVA001012B0_SLOT(055)
	RVA001012B0_SLOT(056) RVA001012B0_SLOT(057) RVA001012B0_SLOT(058) RVA001012B0_SLOT(059)
	RVA001012B0_SLOT(060) RVA001012B0_SLOT(061) RVA001012B0_SLOT(062) RVA001012B0_SLOT(063)
	RVA001012B0_SLOT(064) RVA001012B0_SLOT(065) RVA001012B0_SLOT(066) RVA001012B0_SLOT(067)
	RVA001012B0_SLOT(068) RVA001012B0_SLOT(069) RVA001012B0_SLOT(070) RVA001012B0_SLOT(071)
	RVA001012B0_SLOT(072) RVA001012B0_SLOT(073) RVA001012B0_SLOT(074) RVA001012B0_SLOT(075)
	RVA001012B0_SLOT(076) RVA001012B0_SLOT(077) RVA001012B0_SLOT(078) RVA001012B0_SLOT(079)
	RVA001012B0_SLOT(080) RVA001012B0_SLOT(081) RVA001012B0_SLOT(082) RVA001012B0_SLOT(083)
	RVA001012B0_SLOT(084) RVA001012B0_SLOT(085) RVA001012B0_SLOT(086) RVA001012B0_SLOT(087)
	RVA001012B0_SLOT(088) RVA001012B0_SLOT(089) RVA001012B0_SLOT(090) RVA001012B0_SLOT(091)
	RVA001012B0_SLOT(092) RVA001012B0_SLOT(093) RVA001012B0_SLOT(094) RVA001012B0_SLOT(095)
	RVA001012B0_SLOT(096) RVA001012B0_SLOT(097) RVA001012B0_SLOT(098) RVA001012B0_SLOT(099)
	RVA001012B0_SLOT(100) RVA001012B0_SLOT(101) RVA001012B0_SLOT(102) RVA001012B0_SLOT(103)
	virtual Bool slot104();
};
#undef RVA001012B0_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType k, Int idx1)
	{
		m_bits.set(idx1);
	}
	// 0x000C4BC0, called through ILT 0x0000125D.
	BitFlags(BogusInitType k, Int idx1, Int idx2, Int idx3, Int idx4) throw();

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;

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

	PartitionFilter *link(PartitionFilter *next);		///< 0x009F2AE0

	PartitionFilter *m_next;
};

// Position/radius filter, vtable 0x010860C4; its out-of-line constructor is
// the 32-byte body at 0x000FC2E0.
class Rva000FC2E0Filter : public PartitionFilter
{
public:
	Rva000FC2E0Filter(const Coord3D *pos, Real radius)
		: m_pos(pos), m_radius(radius)
	{
	}
	virtual Bool allow(Object *obj);

	const Coord3D *m_pos;
	Real m_radius;
};

// vtable 0x010860A0; the Zero Hour members, as in clearRemovableForConstruction.
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

// The complete 102-byte constructor at 0x000C3DD0 (ILT 0x000382FD), as in
// Rva002622D0Collect.cpp: it copies both masks and retains neither.
class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(
		const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual Bool allow(Object *obj);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

// Member-less filter, vtable 0x010860B0; constructor 0x000FBDC0.
class Rva000FBDC0Filter : public PartitionFilter
{
public:
	Rva000FBDC0Filter() {}
	virtual Bool allow(Object *obj);
};

// Member-less filter, vtable 0x01083B80 (Rva0025ED50ChargeTargets.cpp).
class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *obj);
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

struct BfmeResultA
{
	SimpleObjectIterator *m_mpo;
	BfmeResultA();
	BfmeResultA(const BfmeResultA &that);
	~BfmeResultA()
	{
		if (--m_mpo->m_refCount == 0)
			delete m_mpo;
	}
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

class PartitionManager
{
public:
	BfmeResultA iterateAllAt002622D0(PartitionFilter *filter);	///< 0x009F2A40
};

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h
class BuildAssistant
{
protected:
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild,
		const Coord3D *pos, Real angle, Player *playerToBuild);
};

#define PI 3.14159265359f

// ?moveObjectsForConstruction@BuildAssistant@@IAE_NPBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@@Z
Bool BuildAssistant::moveObjectsForConstruction(const ThingTemplate *whatToBuild,
	const Coord3D *pos, Real angle, Player *playerToBuild)
{
	GeometryInfo gi(GEOMETRY_BOX, false, 10,
		whatToBuild->getTemplateGeometryInfo().getRadiusAt10(),
		whatToBuild->getTemplateGeometryInfo().getRadiusAt10());
	if (whatToBuild->getTemplateGeometryInfo().rva0087E8D0())
		gi = whatToBuild->getTemplateGeometryInfo();

	Real radius = gi.getRadiusAt10() * 1.4f;	// Fudge the distance,
	{
		Rva000FC2E0Filter filter(pos, radius);
		ThePartitionManager->iterateAllAt002622D0(&filter);
	}

	Bool anyUnmovables = false;
	const BfmeWideResult &iter =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(Int)pos,
			gi.getBoundingSphereRadius() * 1.1f,
			FROM_BOUNDINGSPHERE_3D,
			(Int)Rva0025ED50RootFilter().link(&Rva000FBDC0Filter())
				->link(&PartitionFilterAcceptByKindOf(
					KindOfMaskType(KindOfMaskType::kInit, KINDOF_SELECTABLE),
					KindOfMaskType(KindOfMaskType::kInit, KINDOF_INERT,
						KINDOF_MOVE_ONLY, KINDOF_BASE_FOUNDATION,
						KINDOF_WALK_ON_TOP_OF_WALL)))
				->link(&PartitionFilterWouldCollide(*pos, gi, angle, true)),
			0);

	Object *them;
	while ((them = iter.next()) != NULL)
	{
		if (them->getTemplate()->isKindOf(KINDOF_IMMOBILE))
			continue;

		// Skip KINDOF_ALWAYS_SELECTABLE and isRemovableForConstruction.
		if (them->getTemplate()->isKindOf(KINDOF_ALWAYS_SELECTABLE))
			continue;
		if (!them->getTemplate()->isKindOf(KINDOF_INERT))
		{
			if (them->getTemplate()->isKindOf(KINDOF_SHRUBBERY))
				continue;
			if (them->isKindOf(KINDOF_CLEARED_BY_BUILD))
				continue;
			if (them->m_privateStatus & 1)
				continue;
		}

		Relationship rel = playerToBuild->getRelationship(them->getTeam());
		if (rel == NEUTRAL || rel == ALLIES)
		{
			Rva001CF980Result *result = them->queryAt001CF980();
			if (result && result->slot104())
				continue;

			AIUpdateInterface *ai = them->m_ai;
			if (ai)
			{
				// Vary the distance to move between one half and 1.5 times
				// the radius of the building.
				Real variedRadius = GetGameLogicRandomValueReal(0.5f, 1.5f,
					"F:\\bfme\\Code\\gameengine\\Source\\Common\\System\\BuildAssistant.cpp",
					1825) * radius;

				Coord3D destPos;
				Real dir = GetGameLogicRandomValueReal(-PI, PI,
					"F:\\bfme\\Code\\gameengine\\Source\\Common\\System\\BuildAssistant.cpp",
					1828);
				Vector3 vec(variedRadius, 0, 0);
				vec.Rotate_Z(dir);

				destPos.x = pos->x + vec.X;
				destPos.y = pos->y + vec.Y;
				destPos.z = pos->z;

				if (ai->bfmeBlocksFormationRefresh())
					continue;
				ai->aiBfmeCommand54(&destPos, CMD_FROM_AI);
			}
			else
			{
				anyUnmovables = true;
			}
		}
		else
		{
			anyUnmovables = true;
		}
	}

	return !anyUnmovables;
}
