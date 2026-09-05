// cl: /O2 /Ob0 /MD
//
// 125B twin of bfmeHelper6320 (Rva002E6320ModelCondition.cpp, retail
// 0x002E6320): byte-identical two-lua-arg object lookup shape, only the
// applied special-model-condition constant differs (6 here, not 4).
// Address-derived name pending the real Lua-bound function name.

struct Rva00990030Value
{
	unsigned char m_padC[0xC];
	unsigned m_value;
};

struct Rva00990030Record
{
	unsigned m_type;
	unsigned m_4;
	Rva00990030Value *m_value;
	unsigned m_C;
};

struct Rva00990030Range
{
	Rva00990030Record *m_begin;
	unsigned char m_pad10[0x10 - 4];
	Rva00990030Record *m_end;
};

struct lua_State;
extern "C" int lua_type(lua_State *state, int index);
unsigned Rva00990030Lookup(Rva00990030Range *range, int index);

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

int bfmeHelper6280(lua_State *state)
{
	void *value = (void *)Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *record = (*(GameLogic **)0x012f0898)->findObjectByID((int)value);
	if (!record)
		return 0;

	value = (void *)Rva00990030Lookup((Rva00990030Range *)state, 2);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *source = (*(GameLogic **)0x012f0898)->findObjectByID((int)value);
	if (!source)
		return 0;

	record->bfmeApplySpecialModelCondition(6, source, 1);
	return 0;
}
