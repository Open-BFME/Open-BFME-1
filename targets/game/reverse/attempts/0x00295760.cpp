// ?update@HeightDieUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.41 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1
};

enum DamageType
{
	DAMAGE_NORMAL = 0
};

enum DeathType
{
	DEATH_NORMAL = 8
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 1
};

enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1
};

class Thing
{
public:
	virtual void slot00() = 0;
	void setPosition(const Coord3D *position);
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const throw();
};

class Object
{
public:
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const UnsignedByte *>(this) + 0x38);
	}
	void setPosition(const Coord3D *position);
	void kill(DamageType damageType, DeathType deathType);
	void *getContainedBy() const
	{
		return *reinterpret_cast<void *const *>(
			reinterpret_cast<const UnsignedByte *>(this) + 0x214);
	}
	const GeometryInfo &getGeometryInfo() const
	{
		return *reinterpret_cast<const GeometryInfo *>(
			reinterpret_cast<const UnsignedByte *>(this) + 0xac);
	}
	Real getBoundingCircleRadius() const
	{
		return *reinterpret_cast<const Real *>(
			reinterpret_cast<const UnsignedByte *>(this) + 0xbc);
	}
};

class HeightDieUpdateModuleData
{
public:
	virtual ~HeightDieUpdateModuleData();

	private:
	UnsignedInt m_gap4;

	public:
	Real m_targetHeightAboveTerrain;
	Bool m_targetHeightIncludesStructures;
	Bool m_onlyWhenMovingDown;
	UnsignedByte m_pad0e;
	UnsignedByte m_pad0f;
	Real m_destroyAttachedParticlesAtHeight;
	Bool m_snapToGroundOnDeath;
	UnsignedByte m_pad15;
	UnsignedByte m_pad16;
	UnsignedByte m_pad17;
	UnsignedInt m_initialDelay;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clamp) const;
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *position,
		Bool includeBridge);
};

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, Int);

private:
	UnsignedByte m_bits[NUMBITS / 8];
};

typedef BitFlags<192> KindOfMaskType;
#define KINDOFMASK_NONE (*reinterpret_cast<const KindOfMaskType *>(0x012ED8B8))

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

struct Rva0025ED50Entry
{
	Object *object;
	UnsignedInt unknown04;
};

struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	Int references;
};

struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;

	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	~Rva0025ED50WideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *, Real, IterOrderType,
		PartitionFilter *, Bool);
};

#define ThePartitionManager (*(PartitionManager **)0x012ED5B8)

class ParticleSystemManager
{
public:
	void destroyAttachedSystems(Object *object);
};

#define TheParticleSystemManager (*(ParticleSystemManager **)0x012F64BC)

class Rva00295760Module
{
public:
	virtual ~Rva00295760Module();

protected:
	const HeightDieUpdateModuleData *m_moduleData;
};

class Rva00295760ObjectModule : public Rva00295760Module
{
public:
	virtual void onCapture(Object *, Object *);

protected:
	Object *m_object;
};

class Rva00295760BehaviorModuleInterface
{
public:
	virtual void getBody();
	virtual void getCollide();
	virtual void getContain();
	virtual void getCreate();
	virtual void getDamage();
	virtual void getDestroy();
	virtual void getDie();
	virtual void getSpecialPower();
	virtual void getUpdate();
};

class Rva00295760BehaviorModule : public Rva00295760ObjectModule,
	public Rva00295760BehaviorModuleInterface
{
};

class Rva00295760UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class Rva00295760UpdateModule : public Rva00295760BehaviorModule,
	public Rva00295760UpdateModuleInterface
{
protected:
	UnsignedInt m_nextCallFrame;
	Int m_indexInLogic;
	Int m_updateState;

	Object *getObject() const
	{
		return m_object;
	}
	const HeightDieUpdateModuleData *getModuleData() const
	{
		return m_moduleData;
	}
};

class HeightDieUpdate : public Rva00295760UpdateModule
{
public:
	virtual UpdateSleepTime update();

protected:
	Bool m_hasDied;
	Bool m_particlesDestroyed;
	Coord3D m_lastPosition;
	UnsignedInt m_earliestDeathFrame;
};

// ?update@HeightDieUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime HeightDieUpdate::update()
{
	UnsignedInt now = TheBfmeGameLogic->m_frame;
	if (m_earliestDeathFrame == (UnsignedInt)-1)
		m_earliestDeathFrame = now + getModuleData()->m_initialDelay;
	if (m_earliestDeathFrame > now)
		return UPDATE_SLEEP_NONE;

	if (getObject()->getContainedBy() != 0)
	{
		m_lastPosition = *getObject()->getPosition();
		return UPDATE_SLEEP_NONE;
	}

	const HeightDieUpdateModuleData *modData = getModuleData();
	const Coord3D *position = getObject()->getPosition();
	Bool directionOK = true;
	if (!m_hasDied)
	{
		if (modData->m_onlyWhenMovingDown)
		{
			if (position->z >= m_lastPosition.z)
				directionOK = false;
		}

		Real terrainHeight = TheTerrainLogic->getGroundHeight(
			position->x, position->y, 0);
		if (modData->m_targetHeightIncludesStructures)
		{
			PathfindLayerEnum layer =
				TheTerrainLogic->getHighestLayerForDestination(position, false);
			if (layer != PATHFIND_LAYER_GROUND)
			{
				Real layerHeight = TheTerrainLogic->getLayerHeight(
					position->x, position->y, layer, 0, true);
				if (layerHeight > terrainHeight)
					terrainHeight = layerHeight;
			}
		}

		Real targetHeight = terrainHeight +
			modData->m_targetHeightAboveTerrain;
		if (modData->m_targetHeightIncludesStructures == true)
		{
			BitFlags<192> mustBeSet(BitFlags<192>::kInit, 7);
			PartitionFilterAcceptByKindOf filter(mustBeSet, KINDOFMASK_NONE);
			Rva0025ED50WideResult iterator = ThePartitionManager->iterate(
				position, getObject()->getBoundingCircleRadius(),
				(static_cast<IterOrderType>(3)), &filter, false);
			Real tallestHeight = 0.0f;
			Object *other;
			while (iterator.next(other))
			{
				if (other == getObject())
					continue;
				Real height = other->getGeometryInfo().getMaxHeightAbovePosition();
				if (height > tallestHeight)
					tallestHeight = height;
			}
			if (tallestHeight > modData->m_targetHeightAboveTerrain)
				targetHeight = tallestHeight + terrainHeight;
		}

		if (position->z < targetHeight && directionOK)
		{
			if (!modData->m_snapToGroundOnDeath || position->z < terrainHeight)
			{
				Coord3D groundPosition;
				groundPosition.x = position->x;
				groundPosition.y = position->y;
				groundPosition.z = terrainHeight;
				getObject()->setPosition(&groundPosition);
			}
			getObject()->kill(DAMAGE_NORMAL, DEATH_NORMAL);
			m_hasDied = true;
		}
	}

	if (!m_particlesDestroyed &&
		position->z < modData->m_destroyAttachedParticlesAtHeight &&
		(m_hasDied || directionOK))
	{
		TheParticleSystemManager->destroyAttachedSystems(getObject());
		m_particlesDestroyed = true;
	}

	m_lastPosition = *position;
	return UPDATE_SLEEP_NONE;
}
