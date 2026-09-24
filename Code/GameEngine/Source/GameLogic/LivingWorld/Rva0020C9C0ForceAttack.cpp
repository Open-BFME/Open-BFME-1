// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Object;

class AICommandInterface
{
public:
	void aiForceAttackObject(Object *victim, Int maxShots,
		CommandSourceType commandSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;
};

#include "../Object/object.h"

struct Rva0020C9C0ListNode
{
	Rva0020C9C0ListNode *m_next;
	Int m_previous;
	Int m_objectID;
};

typedef _STL::hash_map<Int, Object *, _STL::hash<Int>,
	_STL::equal_to<Int> > ObjectHash;

class GameLogic
{
public:
	char m_pad00[0xb0];
	ObjectHash m_objects;
};

extern GameLogic *TheGameLogic;

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Rva0020C9C0Owner
{
public:
	void forceAttack(Object *victim, Int maxShots, CommandSourceType commandSource);

private:
	Rva0020C9C0ListNode *targetHead() const
	{
		return m_targets;
	}

	char m_pad00[0x28];
	Rva0020C9C0ListNode *m_targets;
};

void Rva0020C9C0Owner::forceAttack(Object *victim, Int maxShots,
	CommandSourceType commandSource)
{
	Rva0020C9C0ListNode *head = targetHead();
	Rva0020C9C0ListNode *node = head->m_next;
	if (node == head)
		return;

	while (node != targetHead())
	{
		Object *object = 0;
		Int objectID = node->m_objectID;
		if (objectID != 0)
		{
			ObjectHash::iterator objectEntry = TheGameLogic->m_objects.find(objectID);
			if (objectEntry != TheGameLogic->m_objects.end())
				object = (*objectEntry).second;
		}

		if (object != 0 && object->m_ai != 0)
		{
			object->m_ai->m_commands.aiForceAttackObject(
				victim, maxShots, commandSource);
			_ReadWriteBarrier();
		}

		node = node->m_next;
	}
}
