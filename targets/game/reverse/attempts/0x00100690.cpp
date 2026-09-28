// ?isLocationClearOfObjects00100690@BuildAssistant@@UAE_NPBUCoord3D@@PBVThingTemplate@@MPAVObject@@IPAVPlayer@@@Z
// partial score=0.99 date=2026-09-28
// Probe shape 0.994, 2484 B vs retail 2483 B, frame 0x224 exact. The only residue
// is register assignment: retail holds build in EBP and worldPos in EDI, ours the
// reverse ([ebp] encodes one byte longer), which moves the prologue pushes and
// the loop-1 alignment pad. Before landing: pin setMajorRadius/setMinorRadius
// (bodies 0x000FD030/0x000FD070, ILTs 0x000424B5/0x0002CA2F) and the
// getMajorRadius/getMinorRadius getters (0x0087DC20/0x0087DC30) or call the
// BfmeGeometryInfo spellings directly. See
// targets/game/reverse/identity_evidence/00100690-buildassistant-location-clear.md
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <bitset>
#include <math.h>

typedef bool Bool;
typedef float Real;

#define NULL 0
#define TRUE 1

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
	KINDOF_IMMOBILE = 2,
	KINDOF_SHRUBBERY = 6,
	KINDOF_STRUCTURE = 7,
	KINDOF_CLEARED_BY_BUILD = 50,
	KINDOF_WALK_ON_TOP_OF_WALL = 59,
	KINDOF_INERT = 88,
	KINDOF_BASE_FOUNDATION = 103
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const; \
	const ThingTemplate *getTemplate() const; \
	const Coord3D *getPosition() const { return &m_cachedPos; } \
	Real getOrientation() const { return m_cachedAngle; }
#define OBJECT_TU_MEMBERS \
	Relationship getRelationship(const Object *that) const; \
	const GeometryInfo &getGeometryInfo() const { return *(const GeometryInfo *)m_geometryInfo; } \
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
class GeometryInfo;
#include "GameLogic/Object/object.h"

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

class BfmeGeometryInfo
{
public:
	Real boxMajorRadius() const;							///< 0x0087DC20
	Real boxMinorRadius() const;							///< 0x0087DC30
};

// BFME's 0x5C-byte GeometryInfo (see GeometryInfoConstructor.cpp).
class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &that);					///< 0x000FFD10
	virtual ~GeometryInfo();								///< 0x000FFCA0

	void set(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);				///< 0x008804E0
	Bool rva0087E8D0() const;								///< one GEOMETRY_BOX shape
	Real getMajorRadius() const;
	Real getMinorRadius() const;
	void setMajorRadius(Real value);							///< shape 0 major
	void setMinorRadius(Real value);							///< shape 0 minor
	Bool bfmeIntersects(const Coord3D &pos, Real angle, const GeometryInfo &other,
		const Coord3D &otherPos, Real otherAngle) const;	///< 0x0087F2F0

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

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *_vptr;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(UnsignedInt)t >> 5] & (1 << ((UnsignedInt)t & 31))) != 0;
	}
	Real getFactoryExitWidth() const { return m_factoryExitWidth; }
	Real getFactoryExtraBibWidth() const { return m_factoryExtraBibWidth; }

private:
	UnsignedByte m_unmodelled08[0x58];
	GeometryInfo m_geometryInfo;						///< +0x60
	UnsignedByte m_unmodelledBC[0x0c];
	UnsignedInt m_kindof[6];							///< +0xC8
	UnsignedByte m_unmodelledE0[0x2d4];
	Real m_factoryExitWidth;							///< +0x3B4
	Real m_factoryExtraBibWidth;						///< +0x3B8
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *tmpl = m_template;
	if (tmpl && tmpl->m_nextOverride)
		tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

class Rva000C93E0
{
public:
	Bool call();
};

class Player;

class TerrainVisual
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0;
	virtual void addFactionBib(Object *factionBuilding, Bool highlight, Real extra = 0) = 0;
};
extern TerrainVisual *TheTerrainVisual;

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

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

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

	void reset() const
	{
		m_mpo->m_cursor = m_mpo->m_entries.begin();
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

class BfmeWideForwardC
{
private:
	UnsignedByte m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(Int a, Real b, Int c, Int d, Int e);
};

extern PartitionManager *ThePartitionManager;

enum
{
	NO_ENEMY_OBJECT_OVERLAP = 0x20
};

class BuildAssistant
{
public:
	virtual Bool isLocationClearOfObjects00100690(const Coord3D *worldPos,
		const ThingTemplate *build, Real angle, Object *builderObject,
		UnsignedInt options, Player *thePlayer);

protected:
	Bool isRemovableForConstruction(Object *obj);
};

inline Bool Thing::isKindOf(KindOfType t) const
{
	return getTemplate()->isKindOf(t);
}

inline Bool BuildAssistant::isRemovableForConstruction(Object *obj)
{
	if (obj == 0)
		return false;

	if (obj->isKindOf(KINDOF_INERT))
		return false;

	if (obj->isKindOf(KINDOF_SHRUBBERY))
		return true;

	if (obj->isKindOf(KINDOF_CLEARED_BY_BUILD))
		return true;

	if (obj->isEffectivelyDead())
		return true;

	return false;
}

Bool BuildAssistant::isLocationClearOfObjects00100690(const Coord3D *worldPos,
	const ThingTemplate *build, Real angle, Object *builderObject,
	UnsignedInt options, Player *thePlayer)
{
	Bool onlyCheckEnemies = (options == NO_ENEMY_OBJECT_OVERLAP);
	const BfmeWideResult &iter =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(Int)worldPos,
			build->getTemplateGeometryInfo().getBoundingSphereRadius() * 1.1f,
			FROM_BOUNDINGSPHERE_3D,
			(Int)&PartitionFilterWouldCollide(*worldPos,
				build->getTemplateGeometryInfo(), angle, true),
			0);

	Object *them;
	while ((them = iter.next()) != NULL)
	{
		// ignore any kind of class of objects that we will "remove" for building
		if (isRemovableForConstruction(them) == TRUE)
			continue;

		if (them->isKindOf(KINDOF_INERT))
			continue;

		if (them->isKindOf(KINDOF_BASE_FOUNDATION))
			continue;

		if (them->isKindOf(KINDOF_WALK_ON_TOP_OF_WALL))
			continue;

		// an immobile object may obstruct our building depending on flags.
		if (them->isKindOf(KINDOF_IMMOBILE))
		{
			if (onlyCheckEnemies && builderObject &&
				builderObject->getRelationship(them) != ENEMIES)
				continue;
			TheTerrainVisual->addFactionBib(them, TRUE);
			return false;
		}

		if (builderObject && builderObject->getRelationship(them) == ENEMIES)
		{
			TheTerrainVisual->addFactionBib(them, TRUE);
			return false;
		}
	}

	if (onlyCheckEnemies)
		return true;

	// Check for overlapping exit areas.
	Real range = 2 * build->getTemplateGeometryInfo().getRadiusAt10();

	const BfmeWideResult &iter2 =
		((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
			(Int)worldPos, range, FROM_CENTER_3D,
			(Int)&PartitionFilterAcceptByKindOf(
				KindOfMaskType(KindOfMaskType::kInit, KINDOF_STRUCTURE),
				KINDOFMASK_NONE),
			0);

	Real myFactoryExitWidth = build->getFactoryExitWidth();
	Real myExtraWidth = build->getFactoryExtraBibWidth();

	if (thePlayer && ((Rva000C93E0 *)thePlayer)->call())
	{
		// Skirmish ai adds a little extra around the edges so it doesn't build itself into a corner.
		if (myExtraWidth < 30.0f)
		{
			myExtraWidth = 30.0f;
			myFactoryExitWidth -= myExtraWidth;
			if (myFactoryExitWidth < 0)
				myFactoryExitWidth = 0;
		}
	}

	Bool checkMyExit = false;
	Coord3D myExitPos;
	GeometryInfo myBounds = build->getTemplateGeometryInfo();
	myBounds.setMajorRadius(myBounds.getMajorRadius() + myExtraWidth);
	if (!myBounds.rva0087E8D0())
		myBounds.set(GEOMETRY_BOX, false, 40, myBounds.getMajorRadius(), myBounds.getMajorRadius());
	else
		myBounds.setMinorRadius(myBounds.getMinorRadius() / 2.0f + myExtraWidth);

	GeometryInfo myGeom = build->getTemplateGeometryInfo();
	if (!myGeom.rva0087E8D0())
		myGeom.setMinorRadius(myGeom.getMinorRadius() / 2.0f);
	myGeom.setMajorRadius(myFactoryExitWidth / 2.0f);
	if (myFactoryExitWidth > 0)
	{
		myExitPos = *worldPos;
		checkMyExit = true;
		Real c = (Real)cos(angle);
		Real s = (Real)sin(angle);
		Real offset = build->getTemplateGeometryInfo().getMajorRadius() + myFactoryExitWidth / 2.0f;
		myExitPos.x += c * offset;
		myExitPos.y += s * offset;
	}

	iter2.reset();
	while ((them = iter2.next()) != NULL)
	{
		// ignore any kind of class of objects that we will "remove" for building
		if (isRemovableForConstruction(them) == TRUE)
			continue;

		if (them->isKindOf(KINDOF_BASE_FOUNDATION))
			continue;

		if (them->isKindOf(KINDOF_WALK_ON_TOP_OF_WALL))
			continue;

		Real themFactoryExitWidth = them->getTemplate()->getFactoryExitWidth();
		Real hisExtraWidth = them->getTemplate()->getFactoryExtraBibWidth();

		Bool checkHisExit = false;
		Coord3D hisExitPos;
		GeometryInfo hisBounds = them->getGeometryInfo();
		hisBounds.setMajorRadius(hisBounds.getMajorRadius() + hisExtraWidth);
		if (!hisBounds.rva0087E8D0())
			hisBounds.set(GEOMETRY_BOX, false, 40, hisBounds.getMajorRadius(), hisBounds.getMajorRadius());
		else
			hisBounds.setMinorRadius(hisBounds.getMinorRadius() / 2.0f + myExtraWidth);

		GeometryInfo hisGeom = them->getGeometryInfo();
		hisGeom.setMajorRadius(themFactoryExitWidth / 2.0f);
		if (!hisGeom.rva0087E8D0())
			hisGeom.setMinorRadius(them->getGeometryInfo().getMajorRadius());
		if (themFactoryExitWidth > 0)
		{
			hisExitPos = *them->getPosition();
			checkHisExit = true;
			Real c = (Real)cos(them->getOrientation());
			Real s = (Real)sin(them->getOrientation());
			Real offset = them->getGeometryInfo().getMajorRadius() + themFactoryExitWidth / 2.0f;
			hisExitPos.x += c * offset;
			hisExitPos.y += s * offset;
		}

		if (hisBounds.bfmeIntersects(*them->getPosition(), them->getOrientation(),
			myBounds, *worldPos, angle))
		{
			TheTerrainVisual->addFactionBib(them, true);
			return false;
		}

		if (!checkMyExit && !checkHisExit && !hisExtraWidth && !myExtraWidth)
			continue; // neither has extra exit space.

		// an immobile object will obstruct our building no matter what team it's on
		if (them->isKindOf(KINDOF_IMMOBILE))
		{
			// Check for overlap of my exit rectangle to his geom info.
			if (checkMyExit && hisBounds.bfmeIntersects(*them->getPosition(),
				them->getOrientation(), myGeom, myExitPos, angle))
			{
				TheTerrainVisual->addFactionBib(them, true);
				return false;
			}
			// Check for overlap of his exit rectangle with my geom info
			if (checkHisExit && hisGeom.bfmeIntersects(hisExitPos,
				them->getOrientation(), myBounds, *worldPos, angle))
			{
				TheTerrainVisual->addFactionBib(them, true);
				return false;
			}
			// Check both exit rectangles together.
			if (checkMyExit && checkHisExit && hisGeom.bfmeIntersects(hisExitPos,
				them->getOrientation(), myGeom, myExitPos, angle))
			{
				TheTerrainVisual->addFactionBib(them, true);
				return false;
			}
		}
	}
	return true;
}
