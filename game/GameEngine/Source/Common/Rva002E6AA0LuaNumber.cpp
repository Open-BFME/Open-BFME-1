// cl: /O2 /Ob0 /MD

struct lua_State;
extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" double lua_tonumber(lua_State *state, int index);

unsigned Rva00990030Lookup(lua_State *range, int index);

class Object
{
private:
	char m_bfmePad[0x18c];

public:
	float m_bfmeValue;
};

class GameLogic
{
public:
	Object *findObjectByID(int value);
};

extern GameLogic *TheGameLogic;

int bfmeHelper6AA0(lua_State *state)
{
	if (lua_gettop(state) < 2)
		return 0;

	unsigned value = Rva00990030Lookup(state, 1);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *object = TheGameLogic->findObjectByID((int)value);
	if (!object)
		return 0;

	int requested = (int)lua_tonumber(state, 2);
	int current = (int)object->m_bfmeValue;
	object->m_bfmeValue = (float)*(requested > current ? &requested : &current);
	return 1;
}
