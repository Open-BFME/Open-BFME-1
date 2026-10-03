// cl: /O2 /Ob0 /MD

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

int bfmeHelper6320(lua_State *state)
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

	record->bfmeApplySpecialModelCondition(4, source, 1);
	return 0;
}
