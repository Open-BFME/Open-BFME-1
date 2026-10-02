// Open-BFME5 conversions.

struct BfmeLuaVHR;

struct BfmeTagVIF
{
	char m_bfmePad[8];
	int m_bfme08;
};

const char *__cdecl bfmeCheckStrVHR(BfmeLuaVHR *L, int n, unsigned *len);
void __cdecl bfmePushNilVHR(BfmeLuaVHR *L);
// 0x00990410 is the matched row `_lua_pushnumber` from the vendored Lua 4.0.1
// (game/Libraries/Source/Lua/lapi.c) -- the C-linkage COFF spelling of
// lua_pushnumber, as already spelled by the sibling lua_ externs.
struct lua_State;
extern "C" void lua_pushnumber(lua_State *L, double n);
void __cdecl bfmePushStrVHR(BfmeLuaVHR *L, const char *s);
void __cdecl bfmePushUserVHR(BfmeLuaVHR *L, void *u, int tag);
void *__cdecl bfmeToUserVIF(BfmeLuaVHR *L, int n);
void __cdecl bfmeSetTopVIF(BfmeLuaVHR *L, int n);

extern "C" __declspec(dllimport) void *__cdecl fopen(const char *name, const char *mode);

int __cdecl bfmeOpenVIF(BfmeLuaVHR *L)
{
	BfmeTagVIF *tag = (BfmeTagVIF *)bfmeToUserVIF(L, -1);
	bfmeSetTopVIF(L, -2);
	void *fp = fopen(bfmeCheckStrVHR(L, 1, 0), bfmeCheckStrVHR(L, 2, 0));
	if (fp)
	{
		bfmePushUserVHR(L, fp, tag->m_bfme08);
		return 1;
	}
	bfmePushNilVHR(L);
	bfmePushStrVHR(L, "generic I/O error");
	lua_pushnumber(reinterpret_cast<lua_State *>(L), -1.0);
	return 3;
}
