// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AssaultTransportAIUpdate::giveFinalOrders, retail 0x002B4950.
//
// This BFME body retains the hash-map GameLogic lookup used by retail.  The
// compiler expands the member lookup in the loop and leaves the designated
// target lookup as the existing GameLogic::findObjectByID call.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef int ObjectID;
typedef bool Bool;

class Object;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;
	void aiAttackObject(Object *victim, Int maxShotsToFire,
		CommandSourceType cmdSource);
	void aiAttackMoveToPosition(const Coord3D *pos, Int maxShotsToFire,
		CommandSourceType cmdSource);
};

class UpdateModule
{
public:
	virtual void updateModuleAnchor() = 0;

private:
	char m_pad04[0x1c];
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
public:
	void setAllowedToChase(Bool allowed)
	{
		m_allowedToChase = allowed;
	}

private:
	char m_pad24[0x32f - 0x24];
	Bool m_allowedToChase;
	char m_pad330[0x340 - 0x330];
};

class Object
{
public:
	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

private:
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

private:
	char m_pad00[0xb0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class AssaultTransportAIUpdate
{
public:
	void giveFinalOrders();

private:
	char m_pad00[0x344];
	ObjectID m_memberIDs[10];
	char m_pad36c[0x14];
	Coord3D m_attackMoveGoalPos;
	ObjectID m_designatedTarget;
	char m_pad390[8];
	Int m_currentMembers;
	Bool m_isAttackMove;
	Bool m_isAttackObject;
};

// ?giveFinalOrders@AssaultTransportAIUpdate@@QAEXXZ
void AssaultTransportAIUpdate::giveFinalOrders()
{
	for (int i = 0; i < m_currentMembers; ++i)
	{
		Object *member = TheGameLogic->findObjectByID(m_memberIDs[i]);
		AIUpdateInterface *ai = member ? member->getAI() : 0;
		if (member && ai)
		{
			Object *designatedTarget = TheGameLogic->findObjectByID(
				m_designatedTarget);

			if (m_isAttackObject && designatedTarget)
			{
				ai->aiAttackObject(designatedTarget, 0x7fffffff,
					CMD_FROM_PLAYER);
			}
			else if (m_isAttackMove)
			{
				ai->aiAttackMoveToPosition(&m_attackMoveGoalPos,
					0x7fffffff, CMD_FROM_PLAYER);
			}

			ai->setAllowedToChase(false);
		}
	}
}
