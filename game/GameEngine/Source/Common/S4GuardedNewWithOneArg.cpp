// Five bodies -- three of 103 bytes and two of 100 -- that read one global, bail
// out if it is already set, and otherwise allocate and construct:
//
//     if ( g ) return 0;
//     return new T( a );
//
// WHAT THE BYTES SHOW.  The global is read into eax at the very top and the
// `jne` past everything lands on the SAME `xor eax,eax` epilogue the failed
// allocation uses, so the two failure paths are one block in the source's
// shape as well as in the code: a single `return 0` reached two ways.  The
// guard is a plain truth test on one dword -- no member load, no call -- which
// is why the global is spelled as a `void *` here and nothing narrower.
//
// The rest is MSVC's `new`: size to a __cdecl allocator, result to a stack
// local, null test, EH state driven to 0 for the unwind that would free the
// block, then a __thiscall constructor taking ONE dword re-read from
// [esp+0x14] -- the first and only argument slot with four dwords pushed.  As
// in the sibling two-argument family, neither return reloads the local: the
// value handed back is the `this` the constructor leaves in eax.
//
// FIVE DISTINCT GLOBALS, FIVE DISTINCT CONSTRUCTORS, FIVE DISTINCT SIZES.  The
// globals are five different addresses, so they are five different objects and
// get five separate declarations -- collapsing them onto one name would have
// left one symbol resolving to five bases, which is exactly the discrepancy
// `verify_dir32_consistency` exists to catch.  Retail's sizes are 176, 64, 188,
// 124 and 496 bytes; the three that overflow an imm8 are the three 103-byte
// bodies.  The allocator is 0x00881F30 in all five.
//
// WHAT THE BYTES CANNOT DECIDE.  What the guard global IS -- only that one dword
// at a fixed address decides whether the allocation happens.  Whether the
// argument is an int, a pointer or a handle; it is moved as an untyped dword and
// never touched here.
//
// IDENTITY IS NOT RECOVERED.  Every class, global and constructor is named after
// the body that uses it; the constructors are DECLARED, never defined, and
// pinned to the addresses their REL32s resolve to through the ILT thunks in the
// way.

#define S4_GUARDED_NEW( NAME, DWORDS )                                         \
	struct S4Guarded##NAME                                                     \
	{                                                                          \
		int m_storage[ DWORDS ];                                               \
		S4Guarded##NAME( int a );                                              \
	};                                                                         \
	extern void *g_s4Guard##NAME;                                              \
	S4Guarded##NAME *s4mk##NAME( int a )                                       \
	{                                                                          \
		if ( g_s4Guard##NAME )                                                 \
			return 0;                                                          \
		return new S4Guarded##NAME( a );                                       \
	}

S4_GUARDED_NEW( 0055BA20, 44 )

struct BfmeAptScreenOnlineHome
{
	int m_storage[ 16 ];
	BfmeAptScreenOnlineHome( int a );
};

extern void *g_s4Guard0055BAA0;

BfmeAptScreenOnlineHome *s4mk0055BAA0( int a )
{
	if ( g_s4Guard0055BAA0 )
		return 0;
	return new BfmeAptScreenOnlineHome( a );
}

S4_GUARDED_NEW( 0055BB20, 47 )

class BfmeAptScreenOnlineQuickMatch
{
public:
	BfmeAptScreenOnlineQuickMatch( int a );

private:
	int m_storage[ 31 ];
};

extern void *g_s4Guard0055BC20;

BfmeAptScreenOnlineQuickMatch *s4mk0055BC20( int a )
{
	if ( g_s4Guard0055BC20 )
		return 0;
	return new BfmeAptScreenOnlineQuickMatch( a );
}

S4_GUARDED_NEW( 0055BCA0, 124 )
