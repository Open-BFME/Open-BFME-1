// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AssaultTransportAIUpdate::retrieveMembers, retail 0x002B4850.
//
// BFME still uses the STLport hash-map object lookup.  The surrounding ZH
// source has the same operation, but its current AIUpdate layout puts the
// transport's member table 0x54 bytes too early.  This TU keeps only the
// proven ABI slices needed by the body: the lookup map at GameLogic+0xB0,
// Object's AI/contained fields, and the AssaultTransport member count/table.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef int ObjectID;
typedef bool Bool;

class Object;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;
	void aiEnter(Object *object, CommandSourceType source);
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
};

class Object
{
public:
	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	Bool isContained() const
	{
		return m_containedBy != 0;
	}

private:
	char m_pad00[0x204];
	AIUpdateInterface *m_ai;
	char m_pad208[0x0c];
	Object *m_containedBy;
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
	void retrieveMembers();
	Object *getObject() const
	{
		return m_object;
	}

private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0c[0x344 - 0x0c];
	ObjectID m_memberIDs[10];
	char m_pad36c[0x398 - 0x36c];
	Int m_currentMembers;
};

// ?retrieveMembers@AssaultTransportAIUpdate@@QAEXXZ
void AssaultTransportAIUpdate::retrieveMembers()
{
	for (int i = 0; i < m_currentMembers; ++i)
	{
		Object *member = TheGameLogic->findObjectByID(m_memberIDs[i]);
		AIUpdateInterface *ai = member ? member->getAI() : 0;
		if (member && ai && !member->isContained())
		{
			ai->aiEnter(getObject(), CMD_FROM_AI);
		}
	}
}
