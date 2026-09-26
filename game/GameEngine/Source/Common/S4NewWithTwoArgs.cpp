// Four bodies -- two of 96 bytes and two of 99 -- that are one line of source:
//
//     return new T( a, b );
//
// WHAT THE BYTES SHOW.  The MSVC `new` sequence is unmistakable and every part
// of it is here in order: one dword of size pushed to a __cdecl allocator, the
// result stored to a stack local, a null test, the EH state slot driven to 0,
// a __thiscall constructor with `this` in eax's copy and the two incoming
// arguments re-read from the frame in reverse, and a `xor eax,eax` arm for the
// null result.  There is NO `mov eax,<local>` before either return: the value
// returned is whatever the constructor left in eax, which is the MSVC
// convention that a constructor returns `this` -- so the source says `return
// new T(...)` and never names an intermediate variable.
//
// THE FUNCTION IS __cdecl AND TAKES EXACTLY TWO DWORDS.  `ret` pops nothing,
// ecx is never read as an object (the leading `push ecx` is the four-byte local
// the pointer lives in, not a saved `this`), and the two argument reads are at
// [esp+0x14] and [esp+0x18] with four dwords pushed -- the first and second
// argument slots, pushed to the constructor in the order that puts the FIRST
// argument first.
//
// THE EH FRAME IS NOT DECORATION.  `push -1 / push <funcinfo> / fs:[0]` plus a
// state store of 0 before the constructor is the unwind that frees the block if
// the constructor throws.  That state is never returned to -1, because both
// paths leave the function immediately after.  A body compiled with exceptions
// off has none of this and is roughly a third the size.
//
// THE AXES ARE THE ALLOCATION SIZE AND THE CONSTRUCTOR.  Retail's four sizes
// are 60, 36, 836 and 852 bytes; the two that need a full-width `push` are
// three bytes longer, which is the whole 96-to-99 spread.  The allocator is
// 0x00881F30 in all four -- the ledger's `operator new`.
//
// IDENTITY IS NOT RECOVERED.  Each class is named after the body that allocates
// it and is sized only to the byte count the `push` shows; its constructor is
// DECLARED, never defined, and pinned to the address its REL32 resolves to
// through the ILT thunk in the way.  The two arguments are spelled `int`
// because the bytes move them as untyped dwords and show nothing else.

#define S4_NEW_TWO_ARGS( NAME, DWORDS )                                        \
	struct S4New##NAME                                                         \
	{                                                                          \
		int m_storage[ DWORDS ];                                               \
		S4New##NAME( int a, int b );                                           \
	};                                                                         \
	S4New##NAME *s4new##NAME( int a, int b )                                   \
	{                                                                          \
		return new S4New##NAME( a, b );                                        \
	}

S4_NEW_TWO_ARGS( 001142A0, 15 )
S4_NEW_TWO_ARGS( 00117DC0, 9 )
S4_NEW_TWO_ARGS( 0011A680, 209 )
S4_NEW_TWO_ARGS( 0011A720, 213 )
