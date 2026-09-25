// cl: /DNDEBUG /MD /EHsc
// readable body of ?dozerInQueue@AIPlayer@@IAE_NXZ: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
// readable body of ?findDozer@AIPlayer@@MAEPAVObject@@PBUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// Open-BFME: the two AIPlayer members that answer "do we have a dozer".
//
//   ?dozerInQueue@  0x00165780,  76 bytes
//   ?findDozer@     0x00165A50, 379 bytes
//
// Two halves of one question asked at two moments. dozerInQueue looks at what
// the player has ORDERED -- it walks the team build queue at AIPlayer+0x04 and
// every team's work orders, and answers true as soon as one of them is for a
// KINDOF_DOZER template that is not a resource gatherer. findDozer looks at what
// the player HAS -- it walks every object in the game, keeps the ones this
// player controls whose template carries KINDOF_DOZER, and returns the nearest
// idle one; if it found no dozer at all it calls queueDozer on the way out,
// which is what puts an order into the queue dozerInQueue reads.
//
// KINDOF_DOZER is bit 14 at ThingTemplate+0xC8 in both, and both were written
// with their own name for it: findDozer with the enumerator, dozerInQueue with a
// local `mask = 0x4000` that has to stay a local because it is where retail
// keeps it.
//
// The two files gave AIPlayer two shapes that only look incompatible.
// dozerInQueue declared no virtuals at all and modelled the vptr as a plain
// `void *m_vptr` data member, so its build queue landed at +0x04 by arithmetic;
// findDozer declared 22 virtual slots, which puts a real vptr at +0x00 and pins
// findDozer to slot 20 and queueDozer to slot 21. Both are below, so +0x04 is
// now named behind a vtable rather than behind a placeholder word, and the class
// carries every field either body reached: the build queue at +0x04, the player
// at +0x0C, the repair dozer's id at +0x50.
//
// findDozer's Object is reached entirely through raw offsets -- the next object
// at +0x88, the template at +0x04, the id at +0x74, the AI at +0x204, the
// position at +0x38. The AI at +0x204 and the position at +0x38 are the same two
// offsets the AIGroup and AIUpdateInterface lanes measured independently.

typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

#define NULL 0

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Player;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getNextOverride() const { return m_nextOverride; }
	const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	const Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xc8 - 8];
	unsigned int m_kindOf;					// +0xC8, KINDOF_DOZER is bit 14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	void *m_vptr;
	ThingTemplate *m_thing;					// +0x04
	int m_factoryID;
	WorkOrder *m_next;					// +0x0C
	int m_numCompleted;
	int m_numRequired;
	unsigned char m_required;
	unsigned char m_isResourceGatherer;			// +0x19
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	TeamInQueue *next();

	unsigned char m_pad[0x14];
	WorkOrder *m_workOrders;				// +0x14
};

class DozerAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Bool isTaskPending(int task);
	virtual void slot1c();
	virtual Bool isAnyTaskPending();
};

class SupplyTruckAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual Bool isCurrentlyFerryingSupplies();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual Bool isForcedIntoWantingState();
};

class AIUpdateInterface
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02c();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03c();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04c();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05c();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06c();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07c();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08c();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09c();
	virtual void slot0a0();
	virtual void slot0a4();
	virtual void slot0a8();
	virtual void slot0ac();
	virtual void slot0b0();
	virtual void slot0b4();
	virtual void slot0b8();
	virtual void slot0bc();
	virtual void slot0c0();
	virtual void slot0c4();
	virtual void slot0c8();
	virtual void slot0cc();
	virtual void slot0d0();
	virtual void slot0d4();
	virtual void slot0d8();
	virtual void slot0dc();
	virtual void slot0e0();
	virtual void slot0e4();
	virtual void slot0e8();
	virtual void slot0ec();
	virtual void slot0f0();
	virtual void slot0f4();
	virtual void slot0f8();
	virtual void slot0fc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual DozerAIInterface *getDozerAIInterface();
	virtual void slot140();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();
};

class Object
{
public:
	Object *getNextObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) + 0x88);
	}
	Player *getControllingPlayer() const;
	const ThingTemplate *getTemplate() const
	{
		return *reinterpret_cast<const ThingTemplate *const *>(
			reinterpret_cast<const char *>(this) + 4);
	}
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const char *>(this) + 0x74);
	}
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *reinterpret_cast<AIUpdateInterface *const *>(
			reinterpret_cast<const char *>(this) + 0x204);
	}
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(
			reinterpret_cast<const char *>(this) + 0x38);
	}
};

class GameLogic
{
public:
	Object *getFirstObject();
};

extern GameLogic *TheGameLogic;

class AIPlayer
{
protected:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual Object *findDozer(const Coord3D *searchPosition);		// vtable slot 20
	virtual void queueDozer();				// vtable slot 21

	Bool dozerInQueue();

private:
	TeamInQueue *m_teamBuildQueue;				// +0x04
	unsigned char m_unreconstructed_008[4];
	Player *m_player;					// +0x0C
	unsigned char m_unreconstructed_010[0x40];
	ObjectID m_repairDozer;					// +0x50
};

enum { DOZER_TASK_BUILD = 0, KINDOF_DOZER = 1 << 14 };

// ?dozerInQueue@AIPlayer@@IAE_NXZ
// TeamInQueue::includesADozer is inlined here.
Bool AIPlayer::dozerInQueue()
{
	TeamInQueue *team = m_teamBuildQueue;
	unsigned int mask = 0x4000;
	if (team)
	{
		do
		{
			for (WorkOrder *order = team->m_workOrders; order; order = order->m_next)
			{
				if ((order->m_thing->m_kindOf & mask) && !order->m_isResourceGatherer)
					return true;
			}
			team = team->next();
		} while (team);
	}
	return false;
}

// ?findDozer@AIPlayer@@MAEPAVObject@@PBUCoord3D@@@Z
Object *AIPlayer::findDozer(const Coord3D *searchPosition)
{
	Object *candidateObject;
	Object *fallbackDozer = NULL;
	Bool shouldQueueDozer = true;
	Object *closestIdleDozer = NULL;
	Real closestIdleDistanceSquared = 0;

	for (candidateObject = TheGameLogic->getFirstObject(); candidateObject;
		candidateObject = candidateObject->getNextObject())
	{
		Player *candidateOwner = candidateObject->getControllingPlayer();
		if (candidateOwner == m_player)
		{
			const ThingTemplate *candidateTemplate = candidateObject->getTemplate();
			if (candidateTemplate && candidateTemplate->getNextOverride())
				candidateTemplate = static_cast<const ThingTemplate *>(
					candidateTemplate->getNextOverride()->getFinalOverride());
			if ((candidateTemplate->m_kindOf & KINDOF_DOZER) != 0)
			{
				AIUpdateInterface *candidateAI = candidateObject->getAIUpdateInterface();
				if (candidateAI == NULL)
					continue;

				DozerAIInterface *dozerInterface = candidateAI->getDozerAIInterface();
				if (dozerInterface)
				{
					SupplyTruckAIInterface *supplyTruckInterface =
						candidateAI->getSupplyTruckAIInterface();
					if (!dozerInterface->isAnyTaskPending() && supplyTruckInterface)
					{
						if (supplyTruckInterface->isCurrentlyFerryingSupplies()
							|| supplyTruckInterface->isForcedIntoWantingState())
							continue;
					}
					if (candidateObject->getID() == m_repairDozer)
						continue;
					shouldQueueDozer = false;
					if (dozerInterface->isTaskPending(DOZER_TASK_BUILD))
						continue;
					if (!dozerInterface->isAnyTaskPending())
						fallbackDozer = candidateObject;
					if (fallbackDozer == NULL)
						fallbackDozer = candidateObject;
					if (fallbackDozer && !dozerInterface->isAnyTaskPending())
					{
						Real dozerDistanceSquared;
						Real deltaX = searchPosition->x - fallbackDozer->getPosition()->x;
						Real deltaY = searchPosition->y - fallbackDozer->getPosition()->y;
						dozerDistanceSquared = deltaX * deltaX + deltaY * deltaY;
						if (closestIdleDozer == NULL)
						{
							closestIdleDozer = fallbackDozer;
							closestIdleDistanceSquared = dozerDistanceSquared;
						}
						else if (dozerDistanceSquared < closestIdleDistanceSquared)
						{
							closestIdleDozer = fallbackDozer;
							closestIdleDistanceSquared = dozerDistanceSquared;
						}
					}
				}
			}
		}
	}
	if (shouldQueueDozer)
		queueDozer();
	if (closestIdleDozer)
		return closestIdleDozer;
	return fallbackDozer;
}
