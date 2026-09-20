// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectID;
typedef bool Bool;

class Object;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	__forceinline Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

	void destroyObject(Object *object);

private:
	char m_pad00[0xb0];
	ObjectPtrHash m_objHash;
};

class SpawnBehaviorModuleData
{
public:
	char m_pad00[0x18];
	Bool m_spawnedRequireSpawner;
};

struct SpawnIDNode
{
	SpawnIDNode *next;
	SpawnIDNode *previous;
	ObjectID value;
};

class SpawnBehavior
{
public:
	virtual void onDelete();

private:
	char m_pad00[0x48];
	SpawnIDNode *m_spawnIDs;
};

#define TheGameLogic (*(GameLogic **)0x012f0898)

#pragma comment(linker, "/alternatename:?destroyObject@GameLogic@@QAEXPAVObject@@@Z=?j_0001d0de@@YAXXZ")

void SpawnBehavior::onDelete()
{
	SpawnBehaviorModuleData *moduleData = *(SpawnBehaviorModuleData **)((char *)this + 4);
	if (!moduleData->m_spawnedRequireSpawner)
		return;

	SpawnIDNode *entry = (*(SpawnIDNode **)((char *)this + 0x48))->next;
	if (entry == *(SpawnIDNode **)((char *)this + 0x48))
		return;

	GameLogic *logic = TheGameLogic;
	while (entry != *(SpawnIDNode **)((char *)this + 0x48))
	{
		Object *object = logic->findObjectByID(entry->value);
		entry = entry->next;
		if (object && ((*(unsigned char *)((char *)object + 0x344) & 1) == 0))
		{
			logic->destroyObject(object);
			logic = TheGameLogic;
		}
	}
}
