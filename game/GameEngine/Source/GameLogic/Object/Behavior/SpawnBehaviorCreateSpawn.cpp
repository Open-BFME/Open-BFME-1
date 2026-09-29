// cl: /Igame/Libraries/Source/WWVegas/WWLib
// SpawnBehavior::createSpawn, RVA 0x0020C3B0..0x0020C6EB (740 bytes).
//
// IDENTITY. The matched caller SpawnBehaviorUpdate.cpp:212 spells the call
// `if (createSpawn())`; it reaches this body through the 5-byte ILT thunk
// 0x000224FD, whose only target is 0x0020C3B0. That is a matched caller in
// the same class naming this symbol, so the real name is proven. Constructor
// 0x0020AE30 and the ZH SpawnBehavior.cpp twin supply the member names; BFME
// moved them, so the module and object offsets below are BFME's own (module
// data at +0x04, owner at +0x08, spawn template at +0x34, name iterator at
// +0x5C, one-shot countdown at +0x58). Upgrade-era masking is absent here.
//
// SHAPE. 740/740 bytes, 22 relocations, and identical instruction sequence
// once register names are normalised (probe `shape 1.000`).
//
// THE ONE SHAPE LEVER. `findTemplate(*m_templateNameIterator)` spelled
// directly leaves the 0x0020C3B0 affordability load on EDX
// (`mov edx,[esi+0x34]; mov edi,[edx+0x4b4]`) where retail has EAX; that is
// the whole 2-byte residue. MSVC 7.1 hands out EAX/ECX/EDX round-robin in
// program order across the whole function, so one extra code-generation
// temporary before the +0x97 block moves the phase one step and selects EAX,
// and the phase resynchronises before the newObject call at +0xCC, so nothing
// else moves. `getTemplateNameIterator()` below is that temporary: the
// accessor materialises the member into a register before the dereference.
// The other natural spellings that do not materialise it -- a local
// `ThingFactory *factory = TheThingFactory`, a local for the findTemplate
// result, `m_templateNameIterator[0]`, `!md->m_isOneShotData` -- all leave
// EDX, and `const AsciiString *n = m_templateNameIterator` shifts the phase
// just as well. See targets/game/reverse/attempts/0x0020c3b0.cpp for the
// superseded banked source.
//
// The local views preserve the BFME module and object offsets without
// shared-header edits.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef bool Bool;
typedef float Real;

class Team;
class Object;
class Drawable;
#include "ascii_string.h"
class ThingTemplate
{
public:
	Int getCommandPoints(void) const { return m_commandPoints; }

private:
	unsigned char m_beforeCommandPoints[0x4b4];
	Int m_commandPoints;
};
class RvaBehaviorModuleSlots;
class SlavedUpdateInterface;

template <int NUMBITS>
class BitFlags
{
private:
	_STL::bitset<NUMBITS> m_bits;

public:
	BitFlags()
	{
	}
};

typedef BitFlags<86> ObjectStatusMaskType;

enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID = 0,
	OBJECTSHROUD_CLEAR = 1,
	OBJECTSHROUD_PARTIAL_CLEAR = 2,
	OBJECTSHROUD_FOGGED = 3,
	OBJECTSHROUD_SHROUDED = 4
};

class ExitInterface
{
public:
	virtual void slot00();
	virtual ExitDoorType reserveDoorForExit(const ThingTemplate *, Object *);
	virtual void exitObjectViaDoor(Object *, ExitDoorType);
	virtual void exitObjectByBudding(Object *, Object *);
	virtual void unreserveDoorForExit(ExitDoorType);
};

class SlavedUpdateInterface
{
public:
	virtual void slot00();
	virtual void onEnslave(const Object *);
};

class RvaBehaviorModulePrimary
{
public:
	virtual void slot00();
	void *m_pad04;
	void *m_pad08;
};

class RvaBehaviorModuleInterface
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
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();
};

class RvaBehaviorModuleSlots
	: public RvaBehaviorModulePrimary,
	  public RvaBehaviorModuleInterface
{
};

class Drawable
{
public:
	void setDrawableHidden(Bool);
};

enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

class Thing
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
	virtual Drawable *getDrawable() const;

	Bool isKindOf(KindOfType t) const;
};

class Object : public Thing
{
public:

	ExitInterface *getObjectExitInterface() const;
	class Player *getControllingPlayer() const;
	void setProducer(const Object *);
	ObjectShroudStatus getShroudedStatus(Int) const;

	Team *getTeam() const
	{
		return *reinterpret_cast<Team *const *>(reinterpret_cast<const char *>(this) + 0x23c);
	}

	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const char *>(this) + 0x74);
	}

	ObjectID getProducerID() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const char *>(this) + 0x78);
	}

	RvaBehaviorModuleSlots **getBehaviorModules() const
	{
		return const_cast<RvaBehaviorModuleSlots **>(*reinterpret_cast<RvaBehaviorModuleSlots *const *const *>(
			reinterpret_cast<const char *>(this) + 0x1f0));
	}

	const struct Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Rva000C7C30Holder;

class Player
{
public:
	const Rva000C7C30Holder *commandPoints(void) const
	{
		return (const Rva000C7C30Holder *)((const char *)this + 0x30);
	}
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	unsigned char m_pad00[0x24];
	Int m_playerIndex;
};

class Rva000C9530
{
public:
	void wrap(Int, Int);
};

class Rva000C7C30Holder
{
public:
	Int get(Int) const;

private:
	unsigned char m_pad00[4];
	Int m_left;
	Int m_right;
};

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &);
	Object *newObject(const ThingTemplate *, Team *, const ObjectStatusMaskType &, UnsignedInt);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID);
};

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad00[0x14];
	unsigned char m_isOneShotData;
	unsigned char m_canReclaimOrphans;
	unsigned char m_aggregateHealth;
	unsigned char m_exitByBudding;
	unsigned char m_spawnedRequireSpawner;
	unsigned char m_unknown19;
	unsigned char m_pad1a[6];
	AsciiString *m_spawnTemplateNameData;
	AsciiString *m_spawnTemplateNameEnd;
	AsciiString *m_spawnTemplateNameCapacity;

	AsciiString *begin() const
	{
		return m_spawnTemplateNameData;
	}

	AsciiString *end() const
	{
		return m_spawnTemplateNameEnd;
	}
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

	Object *getObject() const
	{
		return m_object;
	}

protected:
	const SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface();
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

protected:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	UnsignedInt m_updateState;
};

template <int Number>
class SpawnBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class SpawnBehaviorFourthBase
{
public:
	SpawnBehaviorFourthBase();
	virtual void slot();
};

class SpawnBehavior
	: public UpdateModule,
	  public SpawnBehaviorSecondaryBase<1>,
	  public SpawnBehaviorSecondaryBase<2>,
	  public SpawnBehaviorSecondaryBase<3>,
	  public SpawnBehaviorFourthBase
{
public:
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const
	{
		return m_moduleData;
	}

	// Retail materialises the name iterator into a temporary before the
	// dereference; this accessor is what the byte shape requires.
	const AsciiString *getTemplateNameIterator() const
	{
		return m_templateNameIterator;
	}

private:
	Object *reclaimOrphanSpawn();
	Bool createSpawn();
	void *m_unknown30;
	const ThingTemplate *m_spawnTemplate;
	Int m_oneShotCountdown;
	UnsignedInt m_framesToWait;
	UnsignedInt m_firstBatchCount;
	_STL::list<Int> m_replacementTimes;
	_STL::list<ObjectID> m_spawnIDs;
	unsigned char m_active;
	unsigned char m_initialBurstTimesInited;
	unsigned char m_aggregateHealth;
	unsigned char m_pad4f;
	UnsignedInt m_spawnCount;
	UnsignedInt m_selfTaskingSpawnCount;
	UnsignedInt m_initialBurstCountdown;
	AsciiString *m_templateNameIterator;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }
private:
	unsigned char m_pad00[0x0c];
	Player *m_localPlayer;
};

extern ThingFactory *TheThingFactory;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;

struct Rva0020C3B0Player
{
	unsigned char m_pad00[0x24];
	Int m_playerIndex;
};

Bool SpawnBehavior::createSpawn()
{
	Object *parent = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 0x08);
	const SpawnBehaviorModuleData *md = *reinterpret_cast<const SpawnBehaviorModuleData *const *>(
		reinterpret_cast<const char *>(this) + 0x04);
	ExitInterface *exitInterface = parent->getObjectExitInterface();
	if (!exitInterface)
		return false;

	ExitDoorType exitDoor = exitInterface->reserveDoorForExit(0, 0);
	if (exitDoor == DOOR_NONE_AVAILABLE)
		return false;

	Object *newSpawn = 0;
	Bool reclaimedOrphan = false;
	if (md->m_canReclaimOrphans && md->m_isOneShotData == false)
	{
		newSpawn = reclaimOrphanSpawn();
		if (newSpawn)
			reclaimedOrphan = true;
	}

	if (!newSpawn)
	{
		m_spawnTemplate = TheThingFactory->findTemplate(*getTemplateNameIterator());
		if (md->m_unknown19 && m_spawnTemplate)
		{
			Player *controllingPlayer = parent->getControllingPlayer();
			if (controllingPlayer && controllingPlayer->commandPoints())
			{
				if (controllingPlayer->commandPoints()->get(1) < m_spawnTemplate->getCommandPoints())
					return false;
			}
		}

		Team *team = parent->getTeam();
		newSpawn = TheThingFactory->newObject(
			m_spawnTemplate, team, ObjectStatusMaskType(), 0);

		reinterpret_cast<Rva000C9530 *>(newSpawn->getControllingPlayer())->wrap(
			reinterpret_cast<Int>(parent), reinterpret_cast<Int>(newSpawn));

		if (newSpawn->getDrawable() != 0 &&
			parent->getShroudedStatus(ThePlayerList->getLocalPlayer()->getPlayerIndex()) >=
				OBJECTSHROUD_FOGGED)
		{
			newSpawn->getDrawable()->setDrawableHidden(true);
		}

		m_templateNameIterator += 1;
		if (m_templateNameIterator == md->end())
			m_templateNameIterator = md->begin();
	}

	newSpawn->setProducer(parent);
	for (RvaBehaviorModuleSlots **update = newSpawn->getBehaviorModules(); *update; ++update)
	{
		SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
		if (sdu != 0)
		{
			sdu->onEnslave(parent);
			break;
		}
	}

	m_spawnIDs.push_back(newSpawn->getID());

	if (!reclaimedOrphan)
	{
		if (md->m_exitByBudding)
		{
			Bool barracksExitSuccess = false;
			if (m_initialBurstCountdown > 0)
			{
				Object *barracks = TheGameLogic->findObjectByID(*reinterpret_cast<ObjectID *>(reinterpret_cast<char *>(parent) + 0x78));
				if (barracks && barracks->isKindOf(KINDOF_STRUCTURE))
				{
					ExitInterface *barracksExitInterface = barracks->getObjectExitInterface();
					if (barracksExitInterface)
					{
						ExitDoorType barracksDoor = barracksExitInterface->reserveDoorForExit(0, 0);
						barracksExitInterface->exitObjectViaDoor(newSpawn, barracksDoor);
						newSpawn->setProducer(parent);
						--m_initialBurstCountdown;
						barracksExitSuccess = true;
					}
				}
			}

			if (!barracksExitSuccess)
			{
				Object *budHost = 0;
				Object *curSpawn = 0;
				Real tapeMeasure = 99999.0f;
				Real closest = 999999.9f;
				for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin();
					iter != m_spawnIDs.end(); ++iter)
				{
					curSpawn = TheGameLogic->findObjectByID(*iter);
					if (curSpawn)
					{
						if (curSpawn == newSpawn)
							continue;
						Real dx = curSpawn->getPosition()->x - parent->getPosition()->x;
						Real dy = curSpawn->getPosition()->y - parent->getPosition()->y;
						tapeMeasure = dx * dx;
						tapeMeasure = tapeMeasure + dy * dy;
						if (tapeMeasure < closest)
						{
							closest = tapeMeasure;
							budHost = curSpawn;
						}
					}
				}
				exitInterface->exitObjectByBudding(newSpawn, budHost);
			}
		}
		else
		{
			exitInterface->exitObjectViaDoor(newSpawn, exitDoor);
		}
	}
	else
		exitInterface->unreserveDoorForExit(exitDoor);

	if (md->m_isOneShotData)
		--m_oneShotCountdown;
	if (m_spawnCount == 0xffffffff)
		m_spawnCount = 1;
	else
		++m_spawnCount;
	return true;
}
