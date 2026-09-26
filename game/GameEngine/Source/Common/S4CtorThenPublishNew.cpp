// Four constructors -- three of 95 bytes and one of 98 -- that make two
// no-argument calls and then publish a freshly allocated object into a global:
//
//     X::X()
//     {
//         first();
//         second();
//         g = new Y;
//     }
//
// WHAT THE BYTES SHOW.  `mov esi,ecx` at the top and `mov eax,esi` at the
// bottom: `this` is saved and RETURNED, which is what makes these constructors
// rather than ordinary __thiscall members.  Nothing is pushed before either of
// the two leading calls and neither pops, so both take no arguments.  Then the
// plain MSVC `new`: size to the __cdecl allocator, null test, EH state to 0, a
// __thiscall constructor with no arguments, `xor eax,eax` on the null arm -- and
// the result, whichever arm produced it, stored straight to a fixed address.
// The store is `a3 <addr>`, an eax-to-absolute move, so the global is a plain
// pointer variable and not a member of anything.
//
// THE EH STATE NEVER LEAVES -1 FOR THE TWO LEADING CALLS.  It is driven to 0
// only across the allocation and constructor of Y.  Whatever the two calls do,
// nothing they leave behind needs unwinding -- that is the reading the state
// order gives, and it is the reason the two calls sit in the flat part of the
// body.
//
// WHAT THE BYTES CANNOT DECIDE -- AND THIS ONE WAS MEASURED.  The FIRST call
// has `this` still live in ecx, so it is equally consistent with a __cdecl free
// function and with a no-argument __thiscall BASE constructor: compiled both
// ways, MSVC 7.1 emits the same 95 bytes, because it reuses the incoming ecx
// rather than reloading it from esi.  The free-function spelling is used below
// because it asserts less -- one callee instead of one callee plus an
// inheritance relationship.  The four first-callees do cluster (0x005DEEE0,
// 0x005DEF70, 0x005DF120, 0x005DF2D0), which is suggestive of a family of base
// constructors, but suggestive is not decided.  The SECOND call is not
// ambiguous in the same way and is the SAME address in all four bodies,
// 0x005F40C0, so it is declared once.
//
// THE AXES ARE THE FIRST CALLEE, THE GLOBAL, AND THE ALLOCATED CLASS.  Retail's
// four allocation sizes are 44, 92, 44 and 416 bytes; the one that overflows an
// imm8 is the 98-byte body.  Two rows allocate 44 bytes AND call the same
// constructor 0x0090F650, so they allocate ONE class -- shared here rather than
// duplicated -- but they publish into DIFFERENT globals, so the globals stay
// four separate declarations.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; callees are
// declared, never defined, and pinned to the addresses their REL32s resolve to
// through the ILT thunks in the way.

void s4Second( void );

#define S4_MADE_CLASS( CTOR, DWORDS )                                          \
	struct S4Made##CTOR                                                        \
	{                                                                          \
		int m_storage[ DWORDS ];                                               \
		S4Made##CTOR();                                                        \
	};

S4_MADE_CLASS( 0090F650, 11 )
S4_MADE_CLASS( 00912580, 23 )
S4_MADE_CLASS( 0091A730, 104 )

#define S4_CTOR_THEN_PUBLISH( NAME, MADE )                                     \
	void s4First##NAME( void );                                                \
	extern S4Made##MADE *g_s4Made##NAME;                                       \
	struct S4Publisher##NAME                                                   \
	{                                                                          \
		S4Publisher##NAME();                                                   \
	};                                                                         \
	S4Publisher##NAME::S4Publisher##NAME()                                     \
	{                                                                          \
		s4First##NAME();                                                       \
		s4Second();                                                            \
		g_s4Made##NAME = new S4Made##MADE;                                     \
	}

S4_CTOR_THEN_PUBLISH( 005F2D80, 0090F650 )
S4_CTOR_THEN_PUBLISH( 005F36D0, 00912580 )
S4_CTOR_THEN_PUBLISH( 005F6590, 0090F650 )
S4_CTOR_THEN_PUBLISH( 005F8540, 0091A730 )
