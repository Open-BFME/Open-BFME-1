// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int ObjectID;

enum CommandSourceType
{
	COMMAND_SOURCE_AI = 2
};

class Object;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

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
	char m_pad000[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic; // retail DIR32 global 0x012F0898

class AICommandInterface
{
public:
	// This is the existing retail ILT ?aiIdle@AICommandInterface... at RVA 0x00024D70.
	void aiIdle(CommandSourceType commandSource);
};

class AIUpdateInterface
{
public:
	char m_pad000[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	// Object::getAI() is the observed Object+0x204 pointer load in this body.
	AIUpdateInterface *getAI()
	{
		return *reinterpret_cast<AIUpdateInterface **>(reinterpret_cast<char *>(this) + 0x204);
	}
};

// The receiver is the SpawnBehaviorInterface secondary subobject at object+0x20.
// Its m_spawnIDs sentinel is therefore secondary-this+0x28 (complete object+0x48).
// The constructor at 0x0020AE30 installs the nine-entry table at 0x010A6BD0;
// this override is slot 8, +0x20, through j_000425f5 to 0x0020CB60.
class __declspec(novtable) SpawnBehavior
{
public:
	virtual void spawnInterfaceSlot0();
	virtual void spawnInterfaceSlot1();
	virtual void spawnInterfaceSlot2();
	virtual void spawnInterfaceSlot3();
	virtual void spawnInterfaceSlot4();
	virtual void spawnInterfaceSlot5();
	virtual void spawnInterfaceSlot6();
	virtual void spawnInterfaceSlot7();
	virtual void orderSlavesToGoIdle(CommandSourceType commandSource);

private:
	char m_pad004[0x24];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?orderSlavesToGoIdle@SpawnBehavior@@UAEXW4CommandSourceType@@@Z
void SpawnBehavior::orderSlavesToGoIdle(CommandSourceType commandSource)
{
	SpawnBehavior *self = this;
	for (_STL::list<ObjectID>::iterator it = self->m_spawnIDs.begin(); it != self->m_spawnIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			AIUpdateInterface *ai = obj->getAI();
			if (ai)
				ai->m_commands.aiIdle(commandSource);
		}
	}
}
