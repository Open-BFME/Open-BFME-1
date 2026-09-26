// Fourteen 22-byte __thiscall members that fill the object's first dword from a
// pointer it already holds, falling back to one call when that pointer's target
// is null, and return `this`:
//
//     push esi / mov esi,ecx / mov eax,[esi] / mov eax,[eax] / test eax,eax
//     jne +5 / call <REL32> / mov [esi],eax / mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  A bare `ret` with ecx read once and no stack argument
// consumed is __thiscall with no arguments.  The object's first dword is a
// POINTER: it is loaded and then dereferenced again, and the second load is what
// the test examines.  `jne` skips exactly the five bytes of the call, so the
// call runs only when that second dword is null, and its result and the
// non-null value both flow into the same store back to the object's first
// dword.  Nothing is pushed before the call, so the callee takes no arguments;
// nothing adjusts esp after it, so it pops nothing either.  `mov eax,esi`
// returns `this`.
//
// `test`/`jne` is an inequality against zero.  Spelling the guard the other way
// round emits the opposite branch and does not reproduce these bytes.
//
// THE ONLY AXIS IS THE REL32 TARGET: fourteen members over eleven callees.
// Three callees are reached by two members each; those pairs compile to the
// same twenty-two bytes and are separate functions at separate addresses, not
// aliases of one another.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

#define BFME_CACHED_FILL_CALLEE( ADDR )                                   \
	void *gen##ADDR();                                                    \

#define BFME_CACHED_FILL( NAME, CALLEE )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void **m_slot;                                                    \
		NAME *fill();                                                     \
	};                                                                    \
	NAME *NAME::fill()                                                    \
	{                                                                     \
		void *value = *m_slot;                                            \
		if ( value == 0 )                                                 \
		{                                                                 \
			value = CALLEE();                                             \
		}                                                                 \
		*(void **)this = value;                                           \
		return this;                                                      \
	}

BFME_CACHED_FILL_CALLEE( 000D6FB0 )
BFME_CACHED_FILL_CALLEE( 003442B0 )
BFME_CACHED_FILL_CALLEE( 0038EEA0 )
BFME_CACHED_FILL_CALLEE( 0038EF00 )
BFME_CACHED_FILL_CALLEE( 00424E90 )
BFME_CACHED_FILL_CALLEE( 005A83F0 )
BFME_CACHED_FILL_CALLEE( 00614DA0 )
BFME_CACHED_FILL_CALLEE( 006A0EF0 )
BFME_CACHED_FILL_CALLEE( 00785F30 )
BFME_CACHED_FILL_CALLEE( 00785F80 )
BFME_CACHED_FILL_CALLEE( 009EE320 )

BFME_CACHED_FILL( Rva000D83F0, gen000D6FB0 )
BFME_CACHED_FILL( Rva000D8430, gen000D6FB0 )
BFME_CACHED_FILL( Rva003477F0, gen003442B0 )
BFME_CACHED_FILL( Rva00390880, gen0038EEA0 )
BFME_CACHED_FILL( Rva003908A0, gen0038EF00 )
BFME_CACHED_FILL( Rva004251C0, gen00424E90 )
BFME_CACHED_FILL( Rva005A8620, gen005A83F0 )
BFME_CACHED_FILL( Rva005CAA60, gen003442B0 )
BFME_CACHED_FILL( Rva00615350, gen00614DA0 )
BFME_CACHED_FILL( Rva006A3D90, gen006A0EF0 )
BFME_CACHED_FILL( Rva00786870, gen00785F30 )
BFME_CACHED_FILL( Rva00786890, gen00785F80 )
BFME_CACHED_FILL( Rva009EE7D0, gen009EE320 )
BFME_CACHED_FILL( Rva009EE7F0, gen009EE320 )
