// Open-BFME5 conversions.

struct BfmeLuaVHR;

struct BfmeTagVIF
{
	char m_bfmePad[8];
	int m_bfme08;
};

struct lua_State;
extern "C" const char *__cdecl luaL_check_lstr(lua_State *L, int n, unsigned *len);
extern "C" void __cdecl lua_pushnil(lua_State *L);
// 0x00990410 is the matched row `_lua_pushnumber` from the vendored Lua 4.0.1
// (game/Libraries/Source/Lua/lapi.c) -- the C-linkage COFF spelling of
// lua_pushnumber, as already spelled by the sibling lua_ externs.
struct lua_State;
extern "C" void lua_pushnumber(lua_State *L, double n);
extern "C" void __cdecl lua_pushstring(lua_State *L, const char *s);
extern "C" void __cdecl lua_pushusertag(lua_State *L, void *u, int tag);
extern "C" void *__cdecl lua_touserdata(lua_State *L, int n);

// 0x0098FDE0 is lua_settop (game/Libraries/Source/Lua/lapi.c, vendored lua-4.0.1).
struct lua_State;
extern "C" void __cdecl lua_settop(lua_State *state, int index);

extern "C" __declspec(dllimport) void *__cdecl fopen(const char *name, const char *mode);

int __cdecl bfmeOpenVIF(BfmeLuaVHR *L)
{
	BfmeTagVIF *tag = (BfmeTagVIF *)lua_touserdata((lua_State *)L, -1);
	lua_settop((lua_State *)L, -2);
	void *fp = fopen(luaL_check_lstr((lua_State *)L, 1, 0),
		luaL_check_lstr((lua_State *)L, 2, 0));
	if (fp)
	{
		lua_pushusertag((lua_State *)L, fp, tag->m_bfme08);
		return 1;
	}
	lua_pushnil((lua_State *)L);
	lua_pushstring((lua_State *)L, "generic I/O error");
	lua_pushnumber(reinterpret_cast<lua_State *>(L), -1.0);
	return 3;
}
