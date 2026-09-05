// LuaScriptEngine Lua callback: CurDrawableSetTransitionAnimState(state)
// Sets the current drawable's transition anim state from the first Lua string argument.
// cl: /DNDEBUG /DWIN32 /MD /O2

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" const char *lua_tostring(lua_State *state, int index);

class AsciiString
{
public:
	void set(const char *text);

private:
	void *m_data;
};

struct LuaTargetOwner;

struct LuaDrawableLink
{
	char m_transitionPad[0x04];
	AsciiString m_transitionAnimState;
	char m_ownerPad[0x04];
	LuaTargetOwner *m_owner;
};

struct LuaDrawableState
{
	char m_drawablePad[0x78];
	LuaDrawableLink *m_drawable;
};

extern LuaDrawableState *g_obj12F060C;

int CurDrawableSetTransitionAnimState(lua_State *state)
{
	if (g_obj12F060C->m_drawable != 0) {
		if (lua_gettop(state) > 0) {
			g_obj12F060C->m_drawable->m_transitionAnimState.set(lua_tostring(state, 1));
			return 0;
		}
	}
	return 0;
}
