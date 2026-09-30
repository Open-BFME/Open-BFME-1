// EA's replacement for Lua 4.0.1's stdin-based io_debug callback.

struct lua_State;

extern void __cdecl bfmeLogMsg574(const char *message);
extern int __cdecl bfmeNotify2_574(void *state, void *parameter);

extern "C" int __cdecl io_debug(lua_State *state)
{
	bfmeLogMsg574(
		"\nEntering LUA debug mode.  Type ? for help, 'cont' to exit debug mode\n");
	return bfmeNotify2_574(state, 0);
}
