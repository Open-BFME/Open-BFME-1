// cl: /O2 /Ob0 /MD

// The registration table at 0x002EC990 binds the name ObjectEnterAlertState to
// the ILT thunk at 0x0002F24D, which jumps here to 0x002E63C0: the body pushed
// by lua_pushcclosure is the one the next lua_setglobal names. The callback
// resolves one object and enables special model condition 9.

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
	void bfmeApplySpecialModelCondition(int condition, const void *value,
		int enabled);
};

class GameLogic
{
public:
	Object *findObjectByID(int value);
};

int ObjectEnterAlertState(lua_State *state)
{
	void *value = (void *)Rva00990030Lookup((Rva00990030Range *)state, 1);
	if (!value)
	{
		if (lua_type(state, 1) != 1)
			return 0;
	}

	Object *object = (*(GameLogic **)0x012f0898)->findObjectByID((int)value);
	if (object)
		object->bfmeApplySpecialModelCondition(9, 0, 1);
	return 0;
}
