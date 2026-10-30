// ?update@HeightDieUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.6193 date=2026-10-30
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// HeightDieUpdate::update, retail 0x00295760 (654 bytes).
// BFME 1 target evidence: the matched constructor 0x00295550 installs vtable
// VA 0x010BF608 at +0x10, whose slot 0 reaches this body (ILT 0x0002C926),
// and ilt_oracle confirms ?update@HeightDieUpdate@@UAE?AW4UpdateSleepTime@@XZ.
// `this` is the UpdateModuleInterface subobject: module data at -0xC, the
// Object at -8; m_hasDied +0x10, m_particlesDestroyed +0x11, m_lastPosition
// +0x14, m_earliestDeathFrame +0x20 (module+0x20..+0x30). Module data:
// +0x08 target height above terrain, +0x0C includes structures, +0x0D only
// when moving down, +0x10 destroy-attached-particles height, +0x14 snap to
// ground, +0x18 initial delay.
// Zero Hour HeightDieUpdate::update is the semantic source; the BFME 2 donor
// (open-bfme-2 20a0cb6173, Code/GameEngine/Source/GameLogic/Object/Update/
// HeightDieUpdate.cpp, retail 0x0048FD1B there) supplies the BFME partition
// query shape: a KindOf filter temporary built from MAKE_KINDOF_MASK(7) and
// KINDOFMASK_NONE, and the wide iterator result. The filter declarations
// follow the matched Rva002FA7C0ScriptAction.cpp.

#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
enum DistanceCalculationType
{
	FROM_BOUNDINGSPHERE_3D = 3
};
enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};
enum DeathType
{
	DEATH_NORMAL = 0
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	__declspec(nothrow) BitFlags(BogusInitType, Int bit);
	~BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;

#define MAKE_KINDOF_MASK(bit) KindOfMaskType(KindOfMaskType::kInit, (bit))

extern const KindOfMaskType KINDOFMASK_NONE;

class Object;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;

	PartitionFilter *m_next;
};

struct VptrZeroBlock24
{
	unsigned int m_dword00;
	unsigned int m_dword04;
	unsigned int m_dword08;
	unsigned int m_dword0c;
	unsigned int m_dword10;
	unsigned int m_dword14;
};

class Rva000C3DD0VptrZeroBlockObject : public PartitionFilter
{
public:
	__declspec(nothrow) Rva000C3DD0VptrZeroBlockObject(
		const VptrZeroBlock24 &first, const VptrZeroBlock24 &second);
	virtual Bool allow(Object *object);

	VptrZeroBlock24 m_first;
	VptrZeroBlock24 m_second;
};

// The partition iterator: a pair vector with a cursor (BfmeWideResultForward.cpp).
struct Rva00295760Pair
{
	Object *first;
	int second;
};
struct Rva00295760Payload
{
	Rva00295760Pair *m_start;
	Rva00295760Pair *m_finish;
	Rva00295760Pair *m_endOfStorage;
	Rva00295760Pair *m_cursor;
};

// Release of the iterator payload, ledgered as 0x000C5FC0.
class BfmeThingCAD
{
public:
	void bfmeGoCAD();
};

struct BfmeWideResult
{
	~BfmeWideResult() { ((BfmeThingCAD *)this)->bfmeGoCAD(); }
	__forceinline Object *next()
	{
		Rva00295760Payload *payload = m_value;
		if (payload->m_cursor == payload->m_finish)
			return 0;
		Rva00295760Pair *cursor = payload->m_cursor;
		Object *obj = cursor->first;
		payload->m_cursor = cursor + 1;
		return obj;
	}
	Rva00295760Payload *m_value;
};

// ThePartitionManager's iterateObjectsInRange as the ledger spells it.
class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int pos, Int range, Int distCalc, Int filters, Int order);
};
extern BfmeWideForwardC *ThePartitionManager;

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
	unsigned char m_pad00[0x10];
	Real m_boundingCircleRadius;			// +0x10
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	void kill(DamageType damageType = DAMAGE_UNRESISTABLE, DeathType deathType = DEATH_NORMAL);
	const Coord3D *getPosition() const { return &m_position; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	Object *getContainedBy() const { return m_containedBy; }
	unsigned char m_pad000[0x38];
	Coord3D m_position;				// +0x38
	unsigned char m_pad044[0xac - 0x44];
	GeometryInfo m_geometryInfo;			// +0xAC
	unsigned char m_padc0[0x214 - 0xc0];
	Object *m_containedBy;				// +0x214
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;				// +0x3C
};
extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02();
	virtual void t03(); virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const;
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges = false);
};
extern TerrainLogic *TheTerrainLogic;

class ParticleSystemManager
{
public:
	void destroyAttachedSystems(Object *obj);
};
extern ParticleSystemManager *TheParticleSystemManager;

struct HeightDieUpdateModuleData
{
	unsigned char m_pad00[8];
	Real m_targetHeightAboveTerrain;		// +0x08
	Bool m_targetHeightIncludesStructures;		// +0x0C
	Bool m_onlyWhenMovingDown;			// +0x0D
	unsigned char m_pad0e[2];
	Real m_destroyAttachedParticlesAtHeight;	// +0x10
	Bool m_snapToGroundOnDeath;			// +0x14
	unsigned char m_pad15[3];
	UnsignedInt m_initialDelay;			// +0x18
};

class HeightDieUpdate
{
public:
	virtual UpdateSleepTime update();
	Object *getObject() const { return *(Object **)((char *)this - 8); }
	const HeightDieUpdateModuleData *getHeightDieUpdateModuleData() const
	{
		return *(const HeightDieUpdateModuleData **)((char *)this - 0xc);
	}
private:
	unsigned char m_pad04[0x10 - 4];
	Bool m_hasDied;					// +0x10
	Bool m_particlesDestroyed;			// +0x11
	unsigned char m_pad12[2];
	Coord3D m_lastPosition;				// +0x14
	UnsignedInt m_earliestDeathFrame;		// +0x20
};

UpdateSleepTime HeightDieUpdate::update( void )
{
	UnsignedInt now = TheGameLogic->m_frame;
	if( m_earliestDeathFrame == 0xffffffff )
		m_earliestDeathFrame = getHeightDieUpdateModuleData()->m_initialDelay + now;

	// If at least a one frame delay has been set, then stop for a while
	if( m_earliestDeathFrame > now )
		return UPDATE_SLEEP_NONE;

	// do nothing if we're contained within other objects ... like a transport
	if( getObject()->getContainedBy() != 0 )
	{
		// keep track of our last position even though we're not doing anything yet
		m_lastPosition = *getObject()->getPosition();
	}
	else
	{

		const HeightDieUpdateModuleData *modData = getHeightDieUpdateModuleData();
		const Coord3D *pos = getObject()->getPosition();

		Bool directionOK = true;
		if( m_hasDied == false )
		{
			if( modData->m_onlyWhenMovingDown )
			{
				if( pos->z >= m_lastPosition.z )
					directionOK = false;
			}

			// get the terrain height
			Real terrainHeightAtPos = TheTerrainLogic->getGroundHeight( pos->x, pos->y );

			// if including structures, check for bridges
			if( modData->m_targetHeightIncludesStructures )
			{
				PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination( pos );
				if( layer != LAYER_GROUND )
				{
					Real layerHeight = TheTerrainLogic->getLayerHeight( pos->x, pos->y, layer );
					if( layerHeight > terrainHeightAtPos )
						terrainHeightAtPos = layerHeight;
				}
			}

			Real targetHeight = terrainHeightAtPos + modData->m_targetHeightAboveTerrain;

			if( modData->m_targetHeightIncludesStructures == true )
			{
				Real tallestHeight = 0.0f;

				// scan all objects in the radius of our extent and find the tallest height among them
				Real range = getObject()->getGeometryInfo().m_boundingCircleRadius;
				BfmeWideResult iter = ThePartitionManager->bfmeForwardWideC( (Int)getObject()->getPosition(),
					*(Int *)&range, FROM_BOUNDINGSPHERE_3D,
					(Int)&Rva000C3DD0VptrZeroBlockObject( *(const VptrZeroBlock24 *)&MAKE_KINDOF_MASK( 7 ),
						*(const VptrZeroBlock24 *)&KINDOFMASK_NONE ),
					0 );
				Object *obj;
				Real thisHeight;
				while( (obj = iter.next()) != 0 )
				{
					// ignore ourselves
					if( obj == getObject() )
						continue;

					// store the height of the tallest object under us
					thisHeight = obj->getGeometryInfo().getMaxHeightAbovePosition();
					if( thisHeight > tallestHeight )
						tallestHeight = thisHeight;
				}

				if( tallestHeight > modData->m_targetHeightAboveTerrain )
					targetHeight = tallestHeight + terrainHeightAtPos;
			}

			// if we are below the target height ... DIE!
			if( pos->z < targetHeight && directionOK )
			{
				// snap us to the ground on death, and never leave us below ground
				if( modData->m_snapToGroundOnDeath || pos->z < terrainHeightAtPos )
				{
					Coord3D ground;
					ground.x = pos->x;
					ground.y = pos->y;
					ground.z = terrainHeightAtPos;
					getObject()->setPosition( &ground );
				}

				// kill the object
				getObject()->kill();

				// we have died ... don't do this again
				m_hasDied = true;
			}
		}

		// below the destroy-attached-particles height, clean them up
		if( m_particlesDestroyed == false && pos->z < modData->m_destroyAttachedParticlesAtHeight && (m_hasDied || directionOK) )
		{
			TheParticleSystemManager->destroyAttachedSystems( getObject() );
			m_particlesDestroyed = true;
		}

		// save our current position as the last position we monitored
		m_lastPosition = *pos;
	}
	return UPDATE_SLEEP_NONE;
}
