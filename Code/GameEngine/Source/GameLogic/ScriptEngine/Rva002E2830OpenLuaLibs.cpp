// cl: /DNDEBUG /DWIN32 /MD /O2

struct lua_State;

extern "C" void lua_baselibopen(lua_State *state);
extern "C" void lua_iolibopen(lua_State *state);
extern "C" void lua_strlibopen(lua_State *state);
extern "C" void lua_mathlibopen(lua_State *state);
extern "C" void lua_dblibopen(lua_State *state);

static void openLuaLibraries(lua_State *state)
{
	lua_baselibopen(state);
	lua_iolibopen(state);
	lua_strlibopen(state);
	lua_mathlibopen(state);
	lua_dblibopen(state);
}

void invokeOpenLuaLibraries(lua_State *state)
{
	openLuaLibraries(state);
}
