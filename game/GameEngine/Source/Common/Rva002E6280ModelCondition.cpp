// cl: /O2 /Ob0 /MD
//
// 125B twin of bfmeHelper6320 (Rva002E6320ModelCondition.cpp, retail
// 0x002E6320): byte-identical two-lua-arg object lookup shape, only the
// applied special-model-condition constant differs (6 here, not 4).
// Address-derived name pending the real Lua-bound function name.

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
unsigned Rva00990030Lookup(lua_State *range, int index);

class Object
{
public:
	void bfmeApplySpecialModelCondition(int condition, const void *value, int enabled);
};

class GameLogic
{
public:
	Object *findObjectByID(int value);
};

extern GameLogic *TheGameLogic;

int bfmeHelper6280(lua_State *state)
{
	void *value = (void *)Rva00990030Lookup(state, 1);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *record = TheGameLogic->findObjectByID((int)value);
	if (!record)
		return 0;

	value = (void *)Rva00990030Lookup(state, 2);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *source = TheGameLogic->findObjectByID((int)value);
	if (!source)
		return 0;

	record->bfmeApplySpecialModelCondition(6, source, 1);
	return 0;
}
