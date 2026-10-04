// Lua callback: ObjectHideSubObject
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);

unsigned Rva00990030Lookup(lua_State *range, int index);
unsigned Rva00990210Lookup(lua_State *range, int index);

#include "ascii_string.h"

class S4Sink004135C0
{
public:
	void invoke(const AsciiString &name, bool a, int b, int c, int d);
};

extern void j_000391c6();

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

extern GameLogic *TheGameLogic;

int ObjectHideSubObject(lua_State *state)
{
	unsigned objectID;
	Object *object;
	if (lua_gettop(state) != 3
		|| ((objectID = Rva00990030Lookup(state, 1)) == 0
			&& lua_type(state, 1) != 1)
		|| (object = TheGameLogic->findObjectByID((int)objectID)) == 0)
		return 0;

	{
		AsciiString name(lua_tostring(state, 2));
		typedef void (S4Sink004135C0::*Invoke)(const AsciiString &, bool, int, int, int);
		union { void (*fn)(); Invoke call; } u = { j_000391c6 };
		(object->getDrawable()->*u.call)(
			name, Rva00990210Lookup(state, 3) == 0, 0, 0, 0);
	}
	return 0;
}
