// cl: /O2 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// The registration table at 0x002EC990 pushes ILT thunk 0x0003D4BF, which
// jumps here to 0x002E6420, and the next lua_setglobal names it
// ObjectEnterUncontrollableCowerState. The callback resolves two objects and
// sets special model condition 5 on the first, with the second as its value.
//
// GameLogic::findObjectByID is the inline header function Zero Hour still has
// in GameLogic.h; BFME's body is the hash_map lookup landed at 0x0009A510
// (GameLogicFindObjectByID.cpp). The call stays out of line, but its body
// being visible tells MSVC 7.1 that it writes no memory, so TheGameLogic is
// loaded once after the first argument push and kept in EDI across both
// calls. With only a declaration the global has to be cached in a local,
// which is loaded before the push and takes ESI instead.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
unsigned Rva00990030Lookup(lua_State *state, int index);

// Lua 4.0.1 lua.h
const int LUA_TNIL = 1;

class Object
{
public:
	void bfmeApplySpecialModelCondition(int condition, const void *value, int enabled);
};

typedef int ObjectID;
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// ABI slice matching GameLogicFindObjectByID.cpp: the bucket vector sits at
// this+0xB4, the offset retail's findObjectByID reads.
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;

	ObjectPtrHash::iterator it = m_objHash.find(id);
	if (it == m_objHash.end())
		return 0;

	return (*it).second;
}

extern GameLogic *TheGameLogic;

int ObjectEnterUncontrollableCowerState(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup(state, 1);
	if (!objectID && lua_type(state, 1) != LUA_TNIL)
		return 0;
	// Retail checks argument 1 again here, not argument 2.
	unsigned otherID = Rva00990030Lookup(state, 2);
	if (!otherID && lua_type(state, 1) != LUA_TNIL)
		return 0;

	Object *object = TheGameLogic->findObjectByID(objectID);
	Object *other = TheGameLogic->findObjectByID(otherID);
	if (object && other)
		object->bfmeApplySpecialModelCondition(5, other, 1);
	return 0;
}
