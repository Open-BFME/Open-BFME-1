// cl: /DNDEBUG /DWIN32 /MD /O2

typedef float Real;

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushboolean(lua_State *state, int value);
extern "C" void lua_pushstring(lua_State *state, const char *value);

extern Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);

int GetClientRandomNumberReal(lua_State *state)
{
	if (lua_gettop(state) <= 1) {
		lua_pushnumber(state, 0.0);
	} else {
		Real low = (Real)lua_tonumber(state, 1);
		Real high = (Real)lua_tonumber(state, 2);
#line 1744 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\LuaScriptEngine.cpp"
		lua_pushnumber(state, GetGameClientRandomValueReal(low, high, __FILE__, __LINE__));
	}
	return 1;
}
#line 30

enum KindOfType { KINDOF_INVALID = -1 };

template<int Bits> class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

struct LuaTargetRecord
{
	char m_targetPad[0x2B4];
	int m_targetID;
};

struct LuaTargetOwner
{
	char m_targetPad[0xFC];
	LuaTargetRecord *m_target;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	struct Data
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_text[1];
	};

public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
	const char *str() const { return m_data->m_text; }

private:
	Data *m_data;
};

struct LuaDrawableLink
{
	AsciiString m_previousAnimationState;
	AsciiString m_transitionAnimationState;
	AsciiString m_previousAnimation;
	LuaTargetOwner *m_owner;
};

struct LuaDrawableState
{
	char m_drawablePad[0x78];
	LuaDrawableLink *m_drawable;
};

extern LuaDrawableState *g_obj12F060C;

int CurDrawableIsCurrentTargetKindof(lua_State *state)
{
	LuaDrawableLink *drawable = g_obj12F060C->m_drawable;
	if (drawable != 0 && drawable->m_owner != 0 && drawable->m_owner->m_target != 0) {
		Object *target = TheGameLogic->findObjectByID(drawable->m_owner->m_target->m_targetID);
		if (target != 0 && lua_gettop(state) > 0) {
			int kind = BitFlags<181>::getSingleBitFromName(lua_tostring(state, 1));
			if (target->isKindOf((KindOfType)kind)) {
				lua_pushboolean(state, 1);
				return 1;
			}
		}
	} else {
		lua_pushnil(state);
	}

	lua_pushboolean(state, 0);
	return 1;
}

int CurDrawablePrevAnimationState(lua_State *state)
{
	AsciiString previousState;
	LuaDrawableLink *drawable = g_obj12F060C->m_drawable;
	if (drawable != 0) {
		previousState = drawable->m_previousAnimationState;
	}

	if (!previousState.isEmpty()) {
		lua_pushstring(state, previousState.str());
	} else {
		lua_pushnil(state);
	}
	return 1;
}

int CurDrawablePrevAnimation(lua_State *state)
{
	AsciiString previousAnimation;
	LuaDrawableLink *drawable = g_obj12F060C->m_drawable;
	if (drawable != 0) {
		previousAnimation = drawable->m_previousAnimation;
	}

	if (!previousAnimation.isEmpty()) {
		lua_pushstring(state, previousAnimation.str());
	} else {
		lua_pushnil(state);
	}
	return 1;
}

typedef unsigned char Bool;

extern double g_bfmeSubB3;

// The status word this binding tests sits at +0x90 of the target record, inside
// the run LuaTargetRecord already declares as padding, so reading it through an
// accessor keeps that layout and the rows above it unchanged.
class LuaTargetStatus
{
public:
	Bool test(int bit) const
	{
		return (Bool)((m_bits[(unsigned int)bit >> 5] & (1u << (bit & 31))) != 0);
	}

	Bool isKindOf(int bit) const
	{
		return test(bit);
	}

private:
	unsigned int m_lead[0x24];
	unsigned int m_bits[2];
};

// ?rva002E7740@@YAHPAUlua_State@@@Z
int rva002E7740(lua_State *state)
{
	LuaDrawableLink *drawable = g_obj12F060C->m_drawable;
	if (drawable != 0) {
		LuaTargetOwner *owner = drawable->m_owner;
		if (owner != 0 && lua_gettop(state) > 0) {
			Bool hit = 0;
			const char *name = lua_tostring(state, 1);
			LuaTargetStatus *status = (LuaTargetStatus *)owner->m_target;
			int bit = BitFlags<86>::getSingleBitFromName(name);
			if (bit != -1)
				hit = status->isKindOf(bit);

			if (hit) {
				lua_pushnumber(state, g_bfmeSubB3);
				return 1;
			}
		}
	}

	lua_pushnil(state);
	return 1;
}

#define LUA_API extern "C"
#include "../../../../Libraries/Source/Lua/luadebug.h"
#undef LUA_API
#include <string.h>

// The body pin and matched callers identify the Lua debug console callback.
class BfmeAwakenDebug
{
public:
#define SLOT(n) virtual void slot##n() = 0;
SLOT(00) SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C)
SLOT(20) SLOT(24) SLOT(28) SLOT(2C) SLOT(30) SLOT(34) SLOT(38) SLOT(3C)
SLOT(40) SLOT(44) SLOT(48) SLOT(4C) SLOT(50) SLOT(54) SLOT(58) SLOT(5C)
SLOT(60) SLOT(64) SLOT(68) SLOT(6C) SLOT(70) SLOT(74) SLOT(78) SLOT(7C)
SLOT(80) SLOT(84) SLOT(88) SLOT(8C) SLOT(90)
#undef SLOT
	virtual int slot94(char *buffer, int size, bool *inputAvailable) = 0;
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void *g_activeObj12F0610;
extern "C" void __identifier("?j_0003ebad@@YAXXZ")(const char *message);
extern void __cdecl bfmeNotify1_574(void *state, void *activation);

int __cdecl bfmeNotify2_574(void *state, void *parameter)
{
	lua_Debug activation;
	char command[250];
	bool inputAvailable = false;
	if (parameter == 0) {
		parameter = &activation;
		lua_getstack((lua_State *)state, 1, &activation);
	}

	__identifier("?j_0003ebad@@YAXXZ")("> ");
readCommand:
	if (TheBfmeAwakenDebug->slot94(command, 250, &inputAvailable) > 0) {
		if (strcmp(command, "cont") == 0) {
			__identifier("?j_0003ebad@@YAXXZ")("cont - Exiting LUA debug mode.\n");
			g_activeObj12F0610 = 0;
			return 0;
		}
		if (strcmp(command, "step") == 0) {
			__identifier("?j_0003ebad@@YAXXZ")("step\n");
			g_activeObj12F0610 = state;
			return 0;
		}
		if (strcmp(command, "where") == 0) {
			bfmeNotify1_574(state, parameter);
			__identifier("?j_0003ebad@@YAXXZ")("> ");
		} else if (strncmp(command, "?", 1) == 0) {
			__identifier("?j_0003ebad@@YAXXZ")("cont - continue, step - single step script, where - describe current execution point.\n");
			__identifier("?j_0003ebad@@YAXXZ")("Any other text is passed to the LUA interpreter.  Try print('something')\n");
			__identifier("?j_0003ebad@@YAXXZ")("> ");
		} else {
			__identifier("?j_0003ebad@@YAXXZ")(command);
			__identifier("?j_0003ebad@@YAXXZ")("\n");
			lua_dostring((lua_State *)state, command);
			lua_settop((lua_State *)state, 0);
			__identifier("?j_0003ebad@@YAXXZ")("> ");
		}
	}
	if (inputAvailable)
		goto readCommand;
	__identifier("?j_0003ebad@@YAXXZ")("No console input devices.  Exiting LUA debug mode.\n");
	return 0;
}
