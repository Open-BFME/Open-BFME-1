// The four byte-identical 20-byte sentinel returners at 0x0083FF10, 0x0083FF30,
// 0x00840010 and 0x00840030 -- four bodies 0x20 bytes apart in one drawer.
// Retail:
//
//     mov eax,[esp+4] / mov dword ptr [eax],0xFFFFFFFF
//     mov dword ptr [eax+4],0 / ret 0x10
//
// WHAT THE BYTES SHOW.  The only thing read off the stack is [esp+4], and it is
// used as an ADDRESS -- so that slot is the hidden return-value pointer MSVC
// pushes last for a result returned in memory, and it is already in eax at the
// `ret`, which is where the caller expects it back.  `ret 0x10` pops sixteen
// bytes: the hidden pointer plus TWELVE BYTES OF ARGUMENTS THAT ARE NEVER READ.
// Callee cleanup rules out __cdecl.
//
// THE RESULT IS NON-POD, and that is forced.  An eight-byte plain struct comes
// back in edx:eax -- `or eax,-1 / xor edx,edx / ret 0xC`, eight bytes, no
// hidden pointer at all -- so a POD pair cannot produce this shape.  Giving the
// pair a user-declared constructor puts it in memory but writes it through a
// scratch register (`or ecx,-1 / xor edx,edx / mov [eax],ecx / mov [eax+4],edx`,
// 17 bytes).  What lands the retail twenty is constructing the result DIRECTLY
// in the return slot from two literals: MSVC 7.1 then stores both immediates to
// memory with no register in between, which is exactly `mov [eax],-1` and
// `mov [eax+4],0`.  So the source returns a freshly built value, not a local it
// filled in and then copied.
//
// A pair whose first word is -1 and whose second is zero, handed back from a
// function that reads none of its arguments, is a sentinel: the "no such thing"
// value of some two-field handle.  What the two fields MEAN is not evidenced.
//
// THE ARGUMENTS ARE NOT EVIDENCED EITHER, beyond totalling twelve bytes -- no
// instruction touches them, so three dwords, a twelve-byte value, and a `this`
// plus eight bytes are indistinguishable here.  Three unnamed dwords are
// written below because that is the least the bytes allow anyone to assume.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four addresses; four instantiations that
// coincide because a sentinel is a sentinel.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names any of the four, so
// the names are address-derived and disclaim identity.

#define BFME_SENTINEL_PAIR_RETURNER( NAME )                                   \
	struct NAME##Pair                                                         \
	{                                                                         \
		int m_first;                                                          \
		int m_second;                                                         \
		NAME##Pair( int first, int second )                                   \
			: m_first( first ), m_second( second ) {}                         \
	};                                                                        \
	NAME##Pair __stdcall NAME##Invalid( int arg0, int arg1, int arg2 );       \
	NAME##Pair __stdcall NAME##Invalid( int arg0, int arg1, int arg2 )        \
	{                                                                         \
		return NAME##Pair( -1, 0 );                                           \
	}

BFME_SENTINEL_PAIR_RETURNER( Rva0083FF10 )
BFME_SENTINEL_PAIR_RETURNER( Rva0083FF30 )
BFME_SENTINEL_PAIR_RETURNER( Rva00840010 )
BFME_SENTINEL_PAIR_RETURNER( Rva00840030 )
