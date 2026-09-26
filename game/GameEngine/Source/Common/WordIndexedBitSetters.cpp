#include <string.h>

// The four byte-identical 64-byte bit setters at 0x000D00C0, 0x000FE0E0,
// 0x0015FC10 and 0x001C6100.  Retail:
//
//     mov eax,ecx / mov ecx,[esp+8] / test ecx,ecx / mov ecx,[esp+4]
//     mov edx,ecx / je clear
//     shr edx,5 / lea eax,[eax+edx*4] / and ecx,0x1F
//     mov edx,1 / shl edx,cl / or [eax],edx / ret 8
//     clear: shr edx,5 / lea eax,[eax+edx*4] / and ecx,0x1F
//     mov edx,1 / shl edx,cl / mov ecx,[eax] / not edx / and ecx,edx
//     mov [eax],ecx / ret 8
//
// WHAT THE BYTES SHOW.  `this` in ecx, two stack arguments, `ret 8`: a
// __thiscall member function taking an index and a flag.  `shr index,5` picks
// a word, `lea eax,[eax+word*4]` addresses it from `this` with no displacement,
// and `and index,0x1F` picks the bit within it -- the standard word-indexed bit
// address, so the word array is the first member of the class.  One arm ORs the
// bit in, the other ANDs its complement out: set-or-clear on a flag.
//
// THE INDEX IS UNSIGNED.  `shr edx,5` is a logical shift; a signed index
// compiles to `sar edx,5` (`c1 fa 05`), two bytes that differ.  So the source
// parameter is an unsigned integer, and `>> 5` and `/ 32` are indistinguishable
// here -- both fold to the same shift.
//
// THE FLAG IS INT-SIZED, NOT `bool`.  Retail loads it with `mov ecx,[esp+8]`
// and tests the full dword.  A `bool` parameter compiles to `mov cl,[esp+8]` /
// `test cl,cl` (`8a 4c 24 08` / `84 c9`) -- same length, different bytes.  So
// the parameter is an `int`-width truth value, which in this codebase is what a
// `Bool`/`BOOL` typedef gives you, not C++ `bool`.
//
// BOTH ARMS RECOMPUTE THE ADDRESS, and that is the compiler's doing, not the
// source's.  `shr`/`lea`/`and`/`mov edx,1`/`shl` appear twice, identically,
// because each arm of the if/else holds the whole expression and MSVC 7.1 does
// not hoist the common prefix out of the branch; only `mov edx,ecx` -- the
// copy of the index made before the branch -- is shared.  Writing it as one
// computed address followed by a branch does not produce these bytes.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four addresses in four different drawers
// of the image; four classes whose bit array happens to start at offset zero.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names any of the four, and
// the EXTENT of the word array is not evidenced by these bytes at all -- no
// bound is checked and none is loaded -- so the array is written with an
// arbitrary extent that the code generation does not depend on.  The names are
// address-derived and disclaim identity.

#define BFME_WORD_INDEXED_BIT_SETTER( NAME )                                  \
	class NAME##BitSet                                                        \
	{                                                                         \
	public:                                                                   \
		unsigned m_words[ 8 ];                                                \
		void setBit( unsigned index, int value );                             \
	};                                                                        \
	void NAME##BitSet::setBit( unsigned index, int value )                    \
	{                                                                         \
		if ( value )                                                          \
		{                                                                     \
			m_words[ index >> 5 ] |= ( 1 << ( index & 0x1F ) );               \
		}                                                                     \
		else                                                                  \
		{                                                                     \
			m_words[ index >> 5 ] &= ~( 1 << ( index & 0x1F ) );              \
		}                                                                     \
	}

BFME_WORD_INDEXED_BIT_SETTER( Rva000D00C0 )
BFME_WORD_INDEXED_BIT_SETTER( Rva000FE0E0 )
BFME_WORD_INDEXED_BIT_SETTER( Rva0015FC10 )
BFME_WORD_INDEXED_BIT_SETTER( Rva001C6100 )

// Retail zeroes ten words and then sets one indexed bit.  The first argument
// is present in the calling convention but does not participate in the body;
// neither its meaning nor the owning type's identity is recoverable here.
class Rva00170C70BitSet
{
public:
	Rva00170C70BitSet( void *unused, unsigned index );

	unsigned m_words[ 10 ];
};

Rva00170C70BitSet::Rva00170C70BitSet( void *, unsigned index )
{
	memset( m_words, 0, sizeof( m_words ) );
	m_words[ index >> 5 ] |= ( 1U << ( index & 0x1F ) );
}
