// EA's replacement for Lua 4.0.1's stdin-based io_debug callback.

struct lua_State;

extern void __cdecl bfmeLogMsg574(const char *message);
extern void __cdecl bfmeNotify2_574(void *state, void *parameter);

extern "C" void __cdecl io_debug(lua_State *state)
{
	bfmeLogMsg574(
		"\nEntering LUA debug mode.  Type ? for help, 'cont' to exit debug mode\n");
	bfmeNotify2_574(state, 0);
	// The helper returns with EAX cleared on every path.  Retail reuses that
	// result as this callback's Lua result count instead of clearing it again.
}
