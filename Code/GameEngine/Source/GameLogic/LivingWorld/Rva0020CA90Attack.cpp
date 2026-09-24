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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class AICommandInterface
{
public:
	void aiAttackPosition(const Coord3D *position, Int maxShots,
		CommandSourceType commandSource);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_commands;
};

#include "../Object/object.h"

struct Rva0020CA90ListNode
{
	Rva0020CA90ListNode *m_next;
	Int m_previous;
	Int m_objectID;
};

struct Rva0020CA90List
{
	Rva0020CA90ListNode *m_head;
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

class Rva0020CA90Owner
{
public:
	void attack(const Coord3D *position, Int maxShots,
		CommandSourceType commandSource);

private:
	Rva0020CA90ListNode *targetHead() const
	{
		return m_targets;
	}

	char m_pad00[0x28];
	Rva0020CA90ListNode *m_targets;
};

#pragma comment(linker, "/alternatename:?aiAttackPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z=?j_000404c1@@YAXXZ")

void Rva0020CA90Owner::attack(const Coord3D *position, Int maxShots,
	CommandSourceType commandSource)
{
	Rva0020CA90ListNode *head = targetHead();
	Rva0020CA90ListNode *node = head->m_next;
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
			object->m_ai->m_commands.aiAttackPosition(
				position, maxShots, commandSource);
			_ReadWriteBarrier();
		}

		node = node->m_next;
	}
}
