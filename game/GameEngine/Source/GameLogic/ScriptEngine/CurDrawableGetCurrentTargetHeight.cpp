// LuaScriptEngine callback: CurDrawableGetCurrentTargetHeight.

// cl: /DNDEBUG /DWIN32 /MD /O2

typedef float Real;

struct lua_State;

extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" void lua_pushnil(lua_State *state);

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

int CurDrawableGetCurrentTargetHeight(lua_State *state)
{
	LuaDrawableLink *drawable = g_obj12F060C->m_drawable;
	if (drawable != 0) {
		LuaTargetOwner *owner = drawable->m_owner;
		if (owner != 0) {
			if (owner->m_target != 0) {
				lua_pushnumber(state, owner->m_target->m_targetHeight
					- owner->m_target->m_currentHeight);
				return 1;
			}
		}
	}
	lua_pushnil(state);
	return 1;
}
