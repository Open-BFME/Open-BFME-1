// cl: /O2 /Ob0 /MD

// The registration table at 0x002EC990 binds the name ObjectEnterAlertState to
// the ILT thunk at 0x0002F24D, which jumps here to 0x002E63C0: the body pushed
// by lua_pushcclosure is the one the next lua_setglobal names. The callback
// resolves one object and enables special model condition 9.

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
unsigned Rva00990030Lookup(lua_State *range, int index);

class Object
{
public:
	void bfmeApplySpecialModelCondition(int condition, const void *value,
		int enabled);
};

class GameLogic
{
public:
	Object *findObjectByID(int value);
};

extern GameLogic *TheGameLogic;

int ObjectEnterAlertState(lua_State *state)
{
	void *value = (void *)Rva00990030Lookup(state, 1);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *object = TheGameLogic->findObjectByID((int)value);
	if (object)
		object->bfmeApplySpecialModelCondition(9, 0, 1);
	return 0;
}
