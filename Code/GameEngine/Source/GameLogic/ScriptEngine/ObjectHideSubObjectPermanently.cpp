// Lua callback: ObjectHideSubObjectPermanently
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);

struct Rva00990030Range;
struct Rva00990210Range;

unsigned Rva00990030Lookup(Rva00990030Range *range, int index);
unsigned Rva00990210Lookup(Rva00990210Range *range, int index);

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();
};

class S4Sink004135C0
{
public:
	void invoke(const AsciiString &name, bool a, int b, int c, int d);
};

#pragma comment(linker, "/alternatename:?invoke@S4Sink004135C0@@QAEXABVAsciiString@@_NHHH@Z=?j_000391c6@@YAXXZ")

class Drawable;

class Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual S4Sink004135C0 *getDrawable();
};

class GameLogic
{
public:
	Object *findObjectByID(int value);
};

int ObjectHideSubObjectPermanently(lua_State *state)
{
	unsigned objectID;
	Object *object;
	if (lua_gettop(state) != 3
		|| ((objectID = Rva00990030Lookup((Rva00990030Range *)state, 1)) == 0
			&& lua_type(state, 1) != 1)
		|| (object = (*(GameLogic **)0x012f0898)->findObjectByID((int)objectID)) == 0)
		return 0;

	{
		AsciiString name(lua_tostring(state, 2));
		object->getDrawable()->invoke(
			name, Rva00990210Lookup((Rva00990210Range *)state, 3) == 0, 1, 0, 0);
	}
	return 0;
}
