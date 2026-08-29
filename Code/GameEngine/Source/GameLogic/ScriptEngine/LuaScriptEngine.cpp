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
	char m_targetPad[0x2B4];
	int m_targetID;
};

struct LuaTargetOwner
{
	char m_targetPad[0xFC];
	LuaTargetRecord *m_target;
};

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
