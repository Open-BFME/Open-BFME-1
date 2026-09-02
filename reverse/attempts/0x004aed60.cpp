// ?findContainedObject@ControlBar@@QAEPAVObject@@PAVGameWindow@@@Z
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// ControlBar lookup through the static ContainEntry table at 0x012F3448
// (same array resetContainData clears), then the inlined GameLogic hash_map
// findObjectByID. retail 0x004AED60, 117 bytes.
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

Object *ControlBar::findContainedObject(GameWindow *win)
{
	int i;

	for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
	{
		if (m_containData[i].control == win)
		{
			ObjectID id = m_containData[i].objectID;

			if (id)
			{
				ObjectPtrHash::iterator it = TheGameLogic->m_objHash.find(id);
				if (it != TheGameLogic->m_objHash.end())
					return (*it).second;
			}
			break;
		}
	}

	return 0;
}
