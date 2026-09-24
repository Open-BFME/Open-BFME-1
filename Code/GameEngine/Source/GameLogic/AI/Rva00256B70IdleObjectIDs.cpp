// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: neutral ABI recovery for retail 0x00256B70 (182 bytes).
// The owning class and public method name are not proven by a named caller or
// vtable, so the address-derived identity is deliberately retained here.
//
// The body drains an STLport list<ObjectID> at this+0x24.  Retail's 12-byte
// list-node erase and the preceding sentinel-count loop identify the list
// element width.  A live ID is looked up through the named GameLogic hash-map
// layout at TheBfmeGameLogic+0xB0; a found Object receives the named
// AICommandInterface::aiIdle(CMD_FROM_AI) call through Object+0x204 and the
// embedded command interface at +0x20.  A missing map value is removed from
// the ID list.  These are layout/ABI claims, not an invented owner semantic.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef int ObjectID;

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType commandSource); // named ILT 0x00024D70
};

class AIPrimaryRva00256B70
{
private:
	char m_pad[0x20];
};

class AIUpdateInterfaceRva00256B70
	: public AIPrimaryRva00256B70, public AICommandInterface
{
};

class ObjectRva00256B70
{
public:
	char m_pad[0x204];
	AIUpdateInterfaceRva00256B70 *m_ai; // named Object/AI layout at +0x204
};

typedef _STL::hash_map<ObjectID, ObjectRva00256B70 *,
	_STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHashRva00256B70;

class GameLogic
{
public:
	__forceinline ObjectRva00256B70 *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHashRva00256B70::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

private:
	char m_pad[0xB0];
	ObjectPtrHashRva00256B70 m_objHash;
};

extern GameLogic *TheBfmeGameLogic;

class Rva00256B70Owner
{
public:
	void clearObjectIDs();

private:
	char m_pad[0x24];
	_STL::list<ObjectID> m_objectIDs;
};

void Rva00256B70Owner::clearObjectIDs()
{
	while (m_objectIDs.size() > 0)
	{
		ObjectID id = m_objectIDs.front();
		ObjectRva00256B70 *object = TheBfmeGameLogic->findObjectByID(id);
		if (object == 0)
		{
			m_objectIDs.remove(id);
		}
		else
		{
			object->m_ai->aiIdle(CMD_FROM_AI);
		}
	}
}
