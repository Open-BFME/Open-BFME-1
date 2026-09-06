// ?Rva002E7690LuaValueLookup@@YAHPAUlua_State@@@Z
// partial score=0.75 date=2026-09-06
// Retail 135B, ours 130B (5 short). Lua binding int f(lua_State*), no id/type-1
// gate (unlike its siblings): global TheLuaScriptEngine (VA 0x00EF060C, pinned
// as ?TheLuaScriptEngine@@3PAVLuaScriptEngine@@A elsewhere) -> +0x78 -> +0xc
// gives a bitfield base; lua_gettop(state)>0; name=lua_tostring(state,1);
// idx=bfmeLookup_001c62b0(name) (0x190F1, same lookup used by 0x002E77F0/
// 0x002E6420); if idx!=-1 and bit (idx>>5,&1<<(idx&0x1f)) set at base+0x250,
// lua_pushnumber(state, g_bfmeSubB3) (double global VA 0x00C7C640, RVA
// 0x0107C640) and return 1; every other path falls through to a single tail
// lua_pushnil(state); return 1.
// WALL: retail materializes the bit test as `test [mem],reg; setne al; test al,al;
// je` (5 extra bytes) even though the result is only used for a branch, never
// passed onward -- every source shape tried (fused `if (mem & mask)`, an
// intermediate `unsigned`/`bool` local, combined `&&` condition, a `volatile`
// local) compiles the SAME toolchain (Vc7 cl.exe) down to a fused `test;je`
// (mine, 130B) except `volatile` which changes shape entirely and grows past
// retail (143B). Never found the exact shape that keeps setne+test as two
// separate steps while still using the local only for a branch. Try: compare
// against an explicit BOOL(int) typedef with an intermediate function-call
// boundary (a tiny static helper `static int testBit(unsigned*, int)` NOT
// inlined, so the caller's `test eax,eax; je` operates on the call's return
// value rather than the flags of the AND) -- that reliably forces the two-step
// shape elsewhere in this codebase (see docs/shape_levers.md row on register
// materialization order) but needs the helper kept file-static and not
// prototyped `inline`. All callees/globals already pinned: TheLuaScriptEngine
// 0x00EF060C/0x012F060C, bfmeLookup_001c62b0 0x190F1, g_bfmeSubB3 0x00C7C640/
// 0x0107C640, lua_gettop/lua_tostring/lua_pushnumber/lua_pushnil. t=30min
// model=sonnet score=0.75

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" const char *lua_tostring( lua_State *state, int index );
extern "C" void lua_pushnumber( lua_State *state, double value );
extern "C" void lua_pushnil( lua_State *state );

int bfmeLookup_001c62b0( void *name );

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
extern double g_bfmeSubB3;

int Rva002E7690LuaValueLookup( lua_State *state )
{
	void *field78 = *(void **)( (char *)TheLuaScriptEngine + 0x78 );
	if( field78 )
	{
		unsigned *esiBase = *(unsigned **)( (char *)field78 + 0xc );
		if( esiBase )
		{
			if( lua_gettop( state ) > 0 )
			{
				const char *name = lua_tostring( state, 1 );
				int idx = bfmeLookup_001c62b0( (void *)name );
				if( idx != -1 )
				{
					unsigned bit = ( esiBase[ ( (unsigned)idx >> 5 ) + ( 0x250 / 4 ) ] & ( 1u << ( idx & 0x1f ) ) ) != 0;
					if( bit != 0 )
					{
						lua_pushnumber( state, g_bfmeSubB3 );
						return 1;
					}
				}
			}
		}
	}
	lua_pushnil( state );
	return 1;
}
