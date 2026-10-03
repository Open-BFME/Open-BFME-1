// EA's replacement for Lua 4.0.1's stdin-based io_debug callback.

struct lua_State;

extern int __cdecl bfmeNotify2_574(void *state, void *parameter);

// Retail's 0x0003EBAD game-logger thunk is defined under its address-derived ILT
// name (game/gen_small/thunks_030.cpp), the only defined spelling of it, so the
// call is spelled that way here too -- the same convention luaB_print uses.
extern "C" void __identifier("?j_0003ebad@@YAXXZ")(const char *message);

extern "C" int __cdecl io_debug(lua_State *state)
{
	__identifier("?j_0003ebad@@YAXXZ")(
		"\nEntering LUA debug mode.  Type ? for help, 'cont' to exit debug mode\n");
	return bfmeNotify2_574(state, 0);
}
