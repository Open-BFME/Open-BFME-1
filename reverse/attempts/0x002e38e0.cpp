// ?CurDrawableGetCurrentTargetHeight@@YAHPAUlua_State@@@Z
// partial score=0.98 date=2026-08-28
// cl: /DNDEBUG /DWIN32 /MD /O2

typedef float Real;

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushboolean(lua_State *state, int value);

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

enum KindOfType { KINDOF_INVALID = -1 };

template<int Bits> class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing {};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

struct LuaTargetRecord
{
	char m_heightPad[0x40];
	Real m_currentHeight;
	char m_targetPad[0x26C];
	Real m_targetHeight;
	int m_targetID;
};

struct LuaTargetOwner
{
	char m_targetPad[0xFC];
	LuaTargetRecord *m_target;
};

struct LuaDrawableLink
{
	char m_ownerPad[0x0C];
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
			int kind = BitFlags<17>::getSingleBitFromName(lua_tostring(state, 1));
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

int CurDrawableGetCurrentTargetHeight(lua_State *state)
{
	LuaDrawableLink *drawable = g_obj12F060C->m_drawable;
	if (drawable != 0 && drawable->m_owner != 0 && drawable->m_owner->m_target != 0) {
		LuaTargetRecord *target = drawable->m_owner->m_target;
		lua_pushnumber(state, target->m_targetHeight - target->m_currentHeight);
	} else {
		lua_pushnil(state);
	}
	return 1;
}
