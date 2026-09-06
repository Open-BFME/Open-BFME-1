// ?Rva002E60B0ObjectOverrideName@@YAHPAUlua_State@@@Z
// partial score=0.85 date=2026-09-06
// Retail 142B, ours 141B, 1-byte short. Lua binding int f(lua_State*): resolve
// object by id/type-1, then walk object->at4->at4 (both raw pointer derefs, no
// vtable) and, only if BOTH links are non-null, call BfmeSubBIA::lastNode00087A80()
// (pinned 0x000022BB, thiscall, returns BfmeAskResult*) replacing a "current node"
// register that otherwise stays == object->at4 (retail merges the p1==0 and p2==0
// early-outs into the SAME code as the ask() success path by reusing eax as the
// node pointer -- do NOT branch to a separate empty-string block for p1==0/p2==0,
// model it as `void *r = p1; if (p1) { void *p2 = ...; if (p2) r = ask(p2); }`).
// Then read *(r+0x20); nonzero -> pushstring(val+8); zero -> pushstring(g_bfmeEmptyAscii).
// WALL: the g_bfmeEmptyAscii fallback pushstring call (a lone constant-address arg,
// no ternary, no other register pressure in that block) compiles to a direct
// `push offset g_bfmeEmptyAscii` (5B) on this toolchain, while retail's older MSVC
// materializes it first (`mov eax,addr; push eax`, 6B) -- the same symbol used
// inside a ternary (see the val==0 case in the neighbouring Rva002E5FF0/Rva002E60B0
// family) DOES get the mov+push form, so a lone standalone push of the constant is
// the one shape variant not yet found. Try: an intermediate `volatile const char*`,
// or routing through the SAME ternary the sibling functions use even though retail's
// asm shows two fully separate call+epilogue blocks (duplicate the epilogue by hand
// after a ternary-fed single call, or find the /Ob/opt flag combination that stops
// this fold). All callees pinned already (bfmeFind1011 0x1F253, lastNode00087A80
// 0x22BB, lua_type/lua_tostring/lua_pushstring/lua_pushnil, TheGameLogic 0x012F0898,
// g_bfmeEmptyAscii 0x0107388B). t=30min model=sonnet score=0.85

struct lua_State;
extern "C" int lua_type( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );
extern "C" void lua_pushstring( lua_State *state, const char *str );
extern "C" const char g_bfmeEmptyAscii[];

unsigned Rva00990030Lookup( lua_State *range, int index );

class Object
{
public:
	char m_unreconstructed00[ 0x204 ];
};

class GameLogic
{
public:
	Object *bfmeFind1011( int id );
};

extern GameLogic *TheGameLogic;

struct BfmeAskResult;

class BfmeSubBIA
{
public:
	BfmeAskResult *lastNode00087A80( void );
};

int Rva002E60B0ObjectOverrideName( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 1;
	}
	Object *object = TheGameLogic->bfmeFind1011( id );
	if( object )
	{
		void *p1 = *(void **)( (char *)object + 4 );
		void *r = p1;
		if( p1 )
		{
			void *p2 = *(void **)( (char *)p1 + 4 );
			if( p2 )
				r = ( (BfmeSubBIA *)p2 )->lastNode00087A80();
		}
		void *val = *(void **)( (char *)r + 0x20 );
		if( val )
		{
			lua_pushstring( state, (const char *)val + 8 );
			return 1;
		}
		lua_pushstring( state, g_bfmeEmptyAscii );
		return 1;
	}
	lua_pushnil( state );
	return 1;
}
