// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// CivilianSpawnUpdate::update, retail RVA 0x0028A5A0 (1025 bytes).
//
// Identity (BFME 1 target evidence): the CivilianSpawnUpdate constructor
// 0x0028A2F0 installs UpdateModuleInterface table 0x010BCD40 at this+0x10;
// its slot 0 is ILT 0x000089B8, which jumps here, and ilt_oracle CONFIRMS
// ?update@CivilianSpawnUpdate@@UAE?AW4UpdateSleepTime@@XZ at this RVA (the
// old ??1CivilianSpawnUpdate@@UAE@XZ lift name is CONTRADICTED; the primary
// scalar-deleting slot routes through ILT 0x0001EBC8 to 0x0028A450). The
// incoming receiver is that secondary interface: module data at -0xC,
// Object at -8, the spawn delay counter at +0x10 (object +0x20, the field the
// constructor seeds from GetGameLogicRandomValue). The body passes the
// CivilianSpawnUpdate.cpp __FILE__ string (VA 0x010BCCE0) to both random
// draws and returns 0x3FFFFFFF on its early exits.
//
// Donor (BFME 2 Open-BFME-2 59e3f8f825):
// Code/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdate.cpp
// CivilianSpawnUpdate::update (BFME 2 0x0047FAFE, 761 B, WorldBuilder-named)
// supplies the control flow: random civilian template, filtered partition
// iteration in MaximumDistance, random run-to target, new object half a
// bounding radius ahead of the spawner, locomotor set 4 plus a model
// condition, move toward the target or destroy the civilian. Field names come
// from the donor parse table (SpawnDelayTime +0x08, RunToFilter +0x0C,
// MaximumDistance +0x10, Civilian names +0x14); the BFME 1 module-data
// constructor 0x0028A480 stores 300 to +0x10 and three zero words to the
// vector at +0x14, as the donor's constructor does.
//
// BFME 1 adaptations (from the retail body, not the donor): Object layout
// (id +0x74, geometry +0xAC, model-condition words +0x110, AI +0x204, team
// +0x23C), AI::pathfinder at TheAI+0x0C, chooseLocomotorSet at AI slot 127
// (+0x1FC), the refcounted BfmeWideResult hit list released inline with
// STLport node-allocator storage, the ignore-obstacle id set through the
// pathfinder's +0x844 setter, and the BFME 1 filter tables
// (Rva0025ED50RootFilter/ObjectFilter, Rva00265150RJFilter). The condition bit
// is word 2 bit 12; the donor calls its counterpart PANICKING, which is not
// independently proven for BFME 1.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <string.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "Lib/Coord3D.h"

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

#include "ascii_string.h"

class Player;
class Team;
class ThingTemplate;
class Object;

template <int N>
class BitFlags
{
public:
	UnsignedInt m_bits[(N + 31) / 32];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team,
		const BitFlags<86> &statusBits, UnsignedInt id);
};
extern ThingFactory *TheThingFactory;

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V10(0) V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7) V10(8) V10(9)
	V10(10) V10(11)
	V(120) V(121) V(122) V(123) V(124) V(125) V(126)
#undef V10
#undef V
	virtual Bool chooseLocomotorSet(UnsignedInt set);	// slot 127 (+0x1FC)

	void ignoreObstacle(const Object *obj);

	char m_pad04[0x20 - 0x04];
	AICommandInterface m_commandInterface;				// +0x20
};

class BfmeGeometryInfo
{
public:
	Real boxMajorRadius() const;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	void setPosition(const Coord3D *pos);
	const Coord3D *getPosition() const { return &m_cachedPos; }

private:
	char m_pad00[0x38];
	Coord3D m_cachedPos;								// +0x38
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void notifyModelConditionChanged();

	ObjectID getID() const { return m_id; }
	Real getBoundingRadius() const { return m_geometryInfo.boxMajorRadius(); }
	AIUpdateInterface *getAI() const { return m_ai; }
	Team *getTeam() const { return m_team; }

	void setModelConditionWord2(UnsignedInt bit)
	{
		if (!(m_modelConditionFlags[2] & bit))
		{
			m_modelConditionFlags[2] |= bit;
			notifyModelConditionChanged();
		}
	}

private:
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;										// +0x74
	char m_pad78[0xAC - 0x78];
	BfmeGeometryInfo m_geometryInfo;					// +0xAC
	char m_padAD[0x110 - 0xAD];
	UnsignedInt m_modelConditionFlags[3];				// +0x110
	char m_pad11C[0x204 - 0x11C];
	AIUpdateInterface *m_ai;							// +0x204
	char m_pad208[0x23C - 0x208];
	Team *m_team;										// +0x23C
};

class Pathfinder
{
public:
	Bool slowDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to,
		ObjectID ignoreObject);
};

// The pathfinder's +0x844 word setter (address-derived name, 0x003D5620).
class Rva003D5620DwordSlot
{
public:
	void set(Int value);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	char m_pad00[0x0C];
	Pathfinder *m_pathfinder;							// +0x0C
};
extern AI *TheAI;

class GameLogic
{
public:
	void destroyObject(Object *obj);
};
extern GameLogic *TheGameLogic;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);
	Object *m_object;
};

class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(const void *subobject, Player *player, Bool match)
		: m_subobject(subobject), m_player(player), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);
	const void *m_subobject;
	Player *m_player;
	Bool m_match;
};

struct CivilianSpawnHit
{
	Object *object;
	UnsignedInt distance;
};

struct CivilianSpawnHitList
{
	_STL::vector<CivilianSpawnHit> entries;
	CivilianSpawnHit *current;
	Int references;
};

struct BfmeWideResult
{
	CivilianSpawnHitList *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	Int getCount() const { return value->entries.size(); }
	Object *next()
	{
		if (value->current == value->entries.end())
			return 0;
		return (value->current++)->object;
	}
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int, float, int, int, int);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

// Opaque 4-byte RunToFilter handle (constructed by ILT 0x0003747A in the
// module-data constructor).
struct CivilianSpawnRunToFilter
{
	UnsignedInt m_handle;
};

class ModuleData;

class CivilianSpawnUpdateModuleData
{
public:
	char m_pad00[0x08];									// vtable, +0x04
	UnsignedInt m_spawnDelayTime;						// +0x08
	CivilianSpawnRunToFilter m_runToFilter;				// +0x0C
	Int m_maximumDistance;								// +0x10
	_STL::vector<AsciiString> m_civilianNames;			// +0x14
};

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void anchor();
};

class BehaviorModule : public PB_DeepBase, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual void disabled();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	UnsignedInt m_storage[3];
};

class CivilianSpawnUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

private:
	const CivilianSpawnUpdateModuleData *getCivilianSpawnUpdateModuleData() const
	{
		return (const CivilianSpawnUpdateModuleData *)getModuleData();
	}

	UpdateSleepTime m_spawnFrame;						// +0x20
};

#define CIVILIAN_SPAWN_FILE "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\CivilianSpawnUpdate.cpp"

static inline void civilianSpawnScale(Coord3D &c, Real s)
{
	c.x *= s;
	c.y *= s;
	c.z *= s;
}

// ?update@CivilianSpawnUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime CivilianSpawnUpdate::update()
{
	const CivilianSpawnUpdateModuleData *data = getCivilianSpawnUpdateModuleData();
	Object *obj = getObject();
	Int index = GetGameLogicRandomValue(0, data->m_civilianNames.size() - 1, CIVILIAN_SPAWN_FILE, 0x55);
	const ThingTemplate *unitTemplate = TheThingFactory->findTemplate(data->m_civilianNames[index]);
	if (!unitTemplate)
		return UPDATE_SLEEP_FOREVER;

	Rva0025ED50RootFilter filterRoot;
	Rva0025ED50ObjectFilter filterObject(obj);
	Rva00265150RJFilter filterRunTo(&data->m_runToFilter, obj->getControllingPlayer(), true);
	filterRoot.link(&filterObject);
	filterRoot.link(&filterRunTo);
	BfmeWideResult iter = reinterpret_cast<BfmeWideForwardC *>(ThePartitionManager)->bfmeForwardWideC(
		(int)obj->getPosition(), (Real)data->m_maximumDistance, 0, (int)&filterRoot, 0);
	Int count = iter.getCount();
	if (count == 0)
		return m_spawnFrame;

	UnsignedInt pick = GetGameLogicRandomValue(0, count - 1, CIVILIAN_SPAWN_FILE, 0x74);
	Object *runToObject = 0;
	for (UnsignedInt i = 0; i <= pick; ++i)
		runToObject = iter.next();

	BitFlags<86> statusBits;
	memset(&statusBits, 0, sizeof(statusBits));
	Object *newObj = TheThingFactory->newObject(unitTemplate, getObject()->getTeam(), statusBits, 0);
	const Coord3D *dir = obj->getUnitDirectionVector2D();
	Coord3D pos;
	pos.x = dir->x;
	pos.y = dir->y;
	pos.z = dir->z;
	civilianSpawnScale(pos, obj->getBoundingRadius() * 0.5);
	pos.x += obj->getPosition()->x;
	pos.y += obj->getPosition()->y;
	pos.z = obj->getPosition()->z;
	newObj->setPosition(&pos);

	AIUpdateInterface *ai = newObj->getAI();
	if (!ai)
		return UPDATE_SLEEP_FOREVER;
	ai->chooseLocomotorSet(4);
	newObj->setModelConditionWord2(0x1000);

	pos = *runToObject->getUnitDirectionVector2D();
	civilianSpawnScale(pos, runToObject->getBoundingRadius() * 0.5);
	pos.x += runToObject->getPosition()->x;
	pos.y += runToObject->getPosition()->y;
	pos.z = runToObject->getPosition()->z;
	ai->ignoreObstacle(runToObject);
	reinterpret_cast<Rva003D5620DwordSlot *>(TheAI->pathfinder())->set(runToObject->getID());
	if (TheAI->pathfinder()->slowDoesPathExist(newObj, newObj->getPosition(), &pos, INVALID_ID))
		ai->m_commandInterface.aiMoveToPosition(&pos, CMD_FROM_AI);
	else
		TheGameLogic->destroyObject(newObj);
	reinterpret_cast<Rva003D5620DwordSlot *>(TheAI->pathfinder())->set(0);
	return m_spawnFrame;
}
