// cl: /DNDEBUG /MD /EHsc

struct Gen00370200Range
{
	void **m_begin;
	void **m_end;
};

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
// stlport
#include <hash_map>

class BfmeGlobFEA
{
public:
	void bfmeCallFEA(void *value, int argument);
};

class Object;
typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
	public:
	__forceinline Object *findObjectByIDInline(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objectMap.find(id);
		if (it == m_objectMap.end())
			return 0;

		return (*it).second;
	}

	private:
	unsigned char m_pad00[0xb0];
	ObjectPtrHash m_objectMap;
};

void __stdcall gen00370200Process(Gen00370200Range *range, void *argument)
{
	register Gen00370200Range *list = range;
	ObjectID *it = (ObjectID *)list->m_begin;
	if (it != (ObjectID *)list->m_end) {
		GameLogic *logic =
			(GameLogic *)*(BfmeGlobFEA **)0x012f0898;
		do {
			Object *value = logic->findObjectByIDInline(*it);
			if (value != 0) {
				((BfmeGlobFEA *)logic)->bfmeCallFEA(value, (int)argument);
				logic =
					(GameLogic *)*(BfmeGlobFEA **)0x012f0898;
			}
			++it;
		} while (it != (ObjectID *)list->m_end);
	}
}
