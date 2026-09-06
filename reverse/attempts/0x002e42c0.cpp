// ?dispatchGlobalById@Rva002E42C0Engine@@QAE?AVRva002E32A0AsciiString@@PBURva002E32A0IdOwner@@@Z
// partial score=0.35 date=2026-09-06
// Retail 217B, SEH-protected (fs:[0] frame) member returning Rva002E32A0AsciiString
// by value (hidden inline RVO slot directly in the stack arg area, matched already by
// Rva002E32A0ObjectIdAsStr/Rva002E32A0Caller in Rva002E32A0ObjectIdAsStr.cpp) from a
// wrapper whose lua_State* lives at this+8. Null-owner early exit: lua_pushnil(state)
// then return an UNCONSTRUCTED result (retail never calls the AsciiString ctor/dtor on
// that path -- no SEH unwind state increment). Otherwise: Rva002E32A0Caller(owner,&result);
// int ownerId = owner->m_id (+0x74); lua_getglobal(state, result.str()); idx=lua_gettop(state);
// if (lua_type(state,idx)==1 || ownerId != Rva00990030Lookup(state,idx)) { lua_settop(state,idx);
// lua_pushnil(state); } return result; releaseBuffer(&result) runs in the epilogue.
// WALL: written as an ordinary non-static C++ member returning AsciiString by value, our
// compiler treats the return slot as an indirect hidden-pointer parameter (extra
// mov dword ptr[esp+4],ptr store plus a copy-back "mov [eax],esi" at the tail) instead of
// retail's direct in-place construction at the caller's stack arg slot -- ours 248B vs
// retail 217B, diverges from +0. Static linkage was required for the sibling
// Rva002E32A0ObjectIdAsStr to get the same in-place slot (see that file's own note); try
// declaring this as a TU-local static free function taking an explicit ecx/this-shaped
// first argument (not a real C++ member) with the caller-supplied AsciiString slot as the
// literal hidden first stack parameter, matching Rva002E32A0Caller's own ABI rather than
// wrapping it in a class method. t=35min model=sonnet score=0.35

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );
extern "C" void lua_getglobal( lua_State *state, const char *name );
extern "C" void lua_settop( lua_State *state, int index );

unsigned Rva00990030Lookup( lua_State *range, int index );

struct Rva002E32A0IdOwner
{
	unsigned char pad00[ 0x74 ];
	int m_id;
};

class Rva002E32A0AsciiString
{
public:
	Rva002E32A0AsciiString() { m_text = 0; }
	~Rva002E32A0AsciiString();

	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}

private:
	void *m_text;
};

void Rva002E32A0Caller( const Rva002E32A0IdOwner *p, Rva002E32A0AsciiString *out );

class Rva002E42C0Engine
{
public:
	Rva002E32A0AsciiString dispatchGlobalById( const Rva002E32A0IdOwner *owner );

	char m_unreconstructed00[ 8 ];
	lua_State *m_state;
};

Rva002E32A0AsciiString Rva002E42C0Engine::dispatchGlobalById( const Rva002E32A0IdOwner *owner )
{
	if( !owner )
	{
		lua_pushnil( m_state );
		return Rva002E32A0AsciiString();
	}
	Rva002E32A0AsciiString result;
	Rva002E32A0Caller( owner, &result );
	int ownerId = owner->m_id;
	lua_State *state = m_state;
	lua_getglobal( state, result.str() );
	int idx = lua_gettop( state );
	if( lua_type( state, idx ) == 1 || ownerId != (int)Rva00990030Lookup( state, idx ) )
	{
		lua_settop( state, idx );
		lua_pushnil( state );
	}
	return result;
}
