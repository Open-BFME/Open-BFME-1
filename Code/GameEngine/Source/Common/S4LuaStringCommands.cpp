// Four 145-byte Lua-callable commands.  Each reads a global, walks two pointers,
// checks that the script passed an argument, and forwards it as an AsciiString
// with two flags:
//
//     int command( lua_State *L )
//     {
//         Sink *s;
//         Holder *h = g_registry->m_holder;
//         if ( h == 0 || ( s = h->m_sink ) == 0 || lua_gettop( L ) <= 0 )
//             return 0;
//         AsciiString name( lua_tostring( L, 1 ) );
//         s->invoke( name, A, B, 0, 0 );
//         return 0;
//     }
//
// FOUR OF THE SIX CALLEES ARE RECOVERED, and between them they name the shape.
// 0x0098FDD0 and 0x00990250 are the matched rows `_lua_gettop` and
// `_lua_tostring` from the vendored Lua 4.0.1 -- so the parameter is a
// `lua_State *`, the `> 0` test is a script argument count, and the `push 1`
// ahead of the second call is stack index 1.  0x00888BC0 and 0x00887940 are
// `??0AsciiString@@QAE@PBD@Z` and `??1AsciiString@@QAE@XZ` (both already pinned
// at those folded addresses), so what the returned `const char *` is wrapped in
// is an AsciiString, constructed and destroyed around one call.
//
// THE STRING IS A NAMED LOCAL, NOT A TEMPORARY.  Its address reaches the call as
// `lea ecx,[esp+0x18] / push ecx`, recomputed rather than reused: spelled as a
// temporary argument, MSVC pushes the constructor's returned `this` in eax
// instead, and the body is a byte shorter there.  The EH state is 0 only between
// the constructor and the destructor, which is the local's whole lifetime.
//
// THE GUARD IS ONE `||` CHAIN WITH AN EARLY RETURN, AND THAT IS FORCED BY BLOCK
// ORDER.  Retail saves BOTH esi and edi between the first `test` and its `je`,
// and every failing test jumps to ONE shared epilogue that pops them.  Written
// as nested `if`s -- two levels or three, with or without a local for the sink
// -- MSVC 7.1 sinks each `push` into the branch that needs it and grows a
// separate exit for each level; the instruction sequence is otherwise identical
// and the length still comes out 145.  Only `if ( a || b || c ) return 0;`
// followed by the body puts the saves above the first branch.
//
// THE ONLY AXIS IS TWO IMMEDIATES.  All four bodies read the same global, walk
// the same two offsets (+0x78 then +0xC), and call the same six addresses; the
// four differ solely in the second and third arguments to `invoke`, which take
// the four combinations of 0 and 1.  Two independent flags is the obvious
// reading and the arguments are spelled `int` rather than `bool` because a
// `push 0` / `push 1` shows the value and not the type.  The last two arguments
// are 0 in all four.
//
// IDENTITY IS NOT RECOVERED for the global, the two structures it is walked
// through, or the sink method: those are named after this family, the method is
// DECLARED and pinned to the address its REL32 resolves to through the ILT thunk
// in the way, and the global is an extern whose ADDRESS is all the bytes show.
// WHICH script command each of the four is cannot be read out of these bytes --
// nothing here touches a name or a string literal.

struct lua_State;
extern "C" int lua_gettop( lua_State *L );
extern "C" const char *lua_tostring( lua_State *L, int index );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *s );
	~AsciiString();

private:
	char *m_data;
};

struct S4Sink004135C0
{
	void invoke( const AsciiString &name, int a, int b, int c, int d );
};

struct S4Holder
{
	char m_pad[ 0xC ];
	S4Sink004135C0 *m_sink;
};

struct S4Registry
{
	char m_pad[ 0x78 ];
	S4Holder *m_holder;
};

extern S4Registry *g_s4Registry;

#define S4_LUA_STRING_COMMAND( NAME, A, B )                                    \
	int s4lua##NAME( lua_State *L )                                            \
	{                                                                          \
		S4Sink004135C0 *s;                                                     \
		S4Holder *h = g_s4Registry->m_holder;                                  \
		if ( h == 0 || ( s = h->m_sink ) == 0 || lua_gettop( L ) <= 0 )        \
			return 0;                                                          \
		AsciiString name( lua_tostring( L, 1 ) );                              \
		s->invoke( name, ( A ), ( B ), 0, 0 );                                 \
		return 0;                                                              \
	}

S4_LUA_STRING_COMMAND( 002E3450, 0, 0 )
S4_LUA_STRING_COMMAND( 002E3510, 1, 0 )
S4_LUA_STRING_COMMAND( 002E35D0, 0, 1 )
S4_LUA_STRING_COMMAND( 002E3690, 1, 1 )
