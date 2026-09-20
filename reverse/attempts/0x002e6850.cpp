// ?d_002e6850@@YAXXZ
// partial score=0.994 date=2026-09-20
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME7: the carved 0x002E6850 body is a Lua audio-event binding.  Its
// caller and callee inventory prove the Lua argument checks, GameLogic
// object lookup, AudioEventRTS construction, and result push, but no public
// semantic name. Address-derived where identity is unknown.

struct lua_State;
extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushnumber(lua_State *state, double value);

typedef int Int;
extern float g_bfmeUint32Scale; // retail 0x01075358 (2^32 conversion fixup)

enum ObjectID
{
	INVALID_OBJECT_ID = -1
};

unsigned Rva00990030Lookup(lua_State *state, Int index);

#include "ascii_string.h"

class BfmeStringLiteralBase
{
	friend class BFMERetailAsciiString;

private:
	BfmeStringLiteralBase(const char *text);
};

class BFMERetailAsciiString : private BfmeStringLiteralBase
{
public:
	BFMERetailAsciiString(const char *text) : BfmeStringLiteralBase(text) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class Object
{
public:
	unsigned char m_unreconstructed[0x74];
	ObjectID m_id;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class BfmeAudioEventRTS
{
public:
	BfmeAudioEventRTS(const AsciiString &name, ObjectID owner);
	~BfmeAudioEventRTS();

private:
	unsigned char m_unreconstructed[0x70];
};

class AudioClientUpdate
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Int addAudioEvent(BfmeAudioEventRTS *event) = 0;
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheAudioClientUpdate (*(AudioClientUpdate **)0x012ED668)

// ?Rva002E6850@@YAHPAUlua_State@@@Z
int Rva002E6850(lua_State *state)
{
	if (lua_gettop(state) < 2 || TheAudioClientUpdate == 0)
		return 0;

	unsigned objectID = Rva00990030Lookup(state, 1);
	if (objectID == 0 && lua_type(state, 1) != 1)
		return 0;

	Object *object = TheBfmeGameLogic->findObjectByID(objectID);
	if (object == 0)
		return 0;

	{
		BfmeAudioEventRTS event(
			*(const AsciiString *)&BFMERetailAsciiString(lua_tostring(state, 2)),
			object->m_id);
		unsigned result = TheAudioClientUpdate->addAudioEvent(&event);
		if (result >= 5)
		{
			lua_pushnumber(state, (double)(float)result);
		}
		else
		{
			lua_pushnil(state);
		}
	}

	return 1;
}
