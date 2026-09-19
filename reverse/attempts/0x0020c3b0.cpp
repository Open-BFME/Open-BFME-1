// ?createSpawn@SpawnBehavior@@QAE_NXZ
// partial score=0.32 date=2026-09-20
// BFME SpawnBehavior::createSpawn reconstruction at retail RVA 0x0020C3B0.
// The local views preserve the BFME module and object offsets without shared-header edits.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;
typedef bool Bool;
typedef float Real;

class Team;
class Object;
class Drawable;
class AsciiString
{
};
class ThingTemplate
{
public:
	unsigned char m_pad00[0x4b4];
	Int m_unknown4b4;
};
class RvaBehaviorModuleSlots;
class SlavedUpdateInterface;

template <int Bits>
class BitFlags
{
public:
	UnsignedInt m_words[3];

	void clear()
	{
		m_words[0] = 0;
		m_words[1] = 0;
		m_words[2] = 0;
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

class Object
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

	ExitInterface *getObjectExitInterface() const;
	class Player *getControllingPlayer() const;
	void setProducer(const Object *);
	ObjectShroudStatus getShroudedStatus(Int) const;
	Bool isKindOf(Int) const;

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

class Player
{
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

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &);
};

class ThingFactory
{
public:
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
	unsigned char m_pad18;
	unsigned char m_unknown19;
	unsigned char m_pad1a[6];
	AsciiString *m_spawnTemplateNameBegin;
	AsciiString *m_spawnTemplateNameEnd;
	AsciiString *m_spawnTemplateNameCapacity;

	AsciiString *begin() const
	{
		return m_spawnTemplateNameBegin;
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

	Object *reclaimOrphanSpawn();
	Bool createSpawn();

private:
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

#define TheThingFactory (*(BfmeThingFactory **)0x012EF1D8)
#define TheGameLogic (*(GameLogic **)0x012F0898)
#define ThePlayerList (*(struct Rva0020C3B0PlayerList **)0x012ED748)

struct Rva0020C3B0PlayerList
{
	unsigned char m_pad00[0x0c];
	Player *m_localPlayer;
};

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

	Object *newSpawn;
	Bool reclaimedOrphan = false;
	if (md->m_canReclaimOrphans && md->m_isOneShotData == false)
	{
		newSpawn = reclaimOrphanSpawn();
		if (newSpawn)
		{
			reclaimedOrphan = true;
			goto spawnReady;
		}
	}

	{
		m_spawnTemplate = TheThingFactory->findTemplate(*m_templateNameIterator);
		if (md->m_unknown19 && m_spawnTemplate)
		{
			Player *controllingPlayer = parent->getControllingPlayer();
			if (controllingPlayer)
			{
				Rva000C7C30Holder *holder = reinterpret_cast<Rva000C7C30Holder *>(
					reinterpret_cast<char *>(controllingPlayer) + 0x30);
				if (holder && holder->get(1) < m_spawnTemplate->m_unknown4b4)
					return false;
			}
		}

		ObjectStatusMaskType statusBits;
		statusBits.clear();
		newSpawn = reinterpret_cast<ThingFactory *>(TheThingFactory)->newObject(
			m_spawnTemplate, parent->getTeam(), statusBits, 0);

		reinterpret_cast<Rva000C9530 *>(newSpawn->getControllingPlayer())->wrap(
			reinterpret_cast<Int>(parent), reinterpret_cast<Int>(newSpawn));

		if (newSpawn->getDrawable() != 0 &&
			parent->getShroudedStatus(reinterpret_cast<Rva0020C3B0Player *>(
				*reinterpret_cast<Player **>(reinterpret_cast<char *>(ThePlayerList) + 0x0c))->m_playerIndex) >=
				OBJECTSHROUD_FOGGED)
		{
			newSpawn->getDrawable()->setDrawableHidden(true);
		}

		m_templateNameIterator += 1;
		if (m_templateNameIterator == md->end())
			m_templateNameIterator = md->begin();
	}

spawnReady:
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
				Object *barracks = TheGameLogic->findObjectByID(parent->getProducerID());
				if (barracks && barracks->isKindOf(7))
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
						Real dy = curSpawn->getPosition()->y - parent->getPosition()->y;
						Real dx = curSpawn->getPosition()->x - parent->getPosition()->x;
						tapeMeasure = dy * dy + dx * dx;
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
