// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ControlBar::findContainedObject, retail RVA 0x004AED60 / 117 bytes.
// Its identity is established by the retail static ContainEntry
// table at 0x012F3448, the reference ControlBar::ContainEntry declaration,
// and the matching ControlBarCommand population and object-map lookup code.
//
// Keep the BFME object-map view local: this body inlines the STLport hash-map
// lookup rather than calling the later named findObjectByID body.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

enum { MAX_COMMANDS_PER_SET = 20 };

class Object;
class GameWindow;
typedef int ObjectID;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogicFrameSlice
{
public:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogicFrameSlice *TheGameLogic;

struct ContainEntry
{
	GameWindow *control;
	ObjectID objectID;
};

class ControlBar
{
public:
	Object *findContainedObject(GameWindow *win);

	static ContainEntry m_containData[MAX_COMMANDS_PER_SET];
};

#pragma optimize("t", on)
Object *ControlBar::findContainedObject(GameWindow *win)
{
	int i;
	ObjectID id = 0;

	for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
	{
		if (m_containData[i].control == win)
		{
			id = m_containData[i].objectID;
			break;
		}
	}

	if (!id)
		return 0;

	ObjectPtrHash::iterator it = TheGameLogic->m_objHash.find(id);
	if (it == TheGameLogic->m_objHash.end())
		goto contained_not_found;
	return (*it).second;

contained_not_found:
	return 0;
}
#pragma optimize("", on)
