// The twelve byte-identical iterator-arithmetic helpers at 0x000696C0-0x00069BA0
// and 0x00472D60-0x004733C0.  They occur in six ADJACENT PAIRS, each pair 0x20
// apart, and each pair holds one of each shape:
//
//   distance (16 bytes)
//     mov eax,[esp+8] / mov ecx,[esp+4] / mov eax,[eax] / sub eax,[ecx]
//     sar eax,4 / ret
//
//   advance (18 bytes)
//     mov eax,[esp+4] / mov ecx,[esp+8] / mov edx,[eax] / shl ecx,4
//     add edx,ecx / mov [eax],edx / ret
//
// WHAT THE BYTES SHOW.  Nothing in ecx on entry and a plain `ret`: __cdecl,
// caller-cleaned.  Each argument that names an iterator is dereferenced once
// before use (`mov eax,[eax]`, `mov edx,[eax]`), so the iterator arrives BY
// ADDRESS -- by reference -- and its whole representation is the single pointer
// at offset 0.
//
// `sar eax,4` on a pointer difference and `shl ecx,4` on a count are the same
// fact stated twice: the element is SIXTEEN BYTES.  That is the one axis these
// twelve share, and it is the reason both shapes live in the same file.
//
// THE ARGUMENT ORDER IS OPPOSITE BETWEEN THE TWO, and that is a signature fact
// rather than scheduling noise.  distance reads its SECOND argument first and
// subtracts the first from it, so it returns `last - first`; advance writes
// through its FIRST argument and scales its second, so the mutated iterator is
// the leading parameter.  Neither order can be swapped without changing which
// operand is dereferenced for writing.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Six pairs at six addresses, each pair
// generated for a different container whose element happens to be sixteen bytes
// wide.  They are separate instantiations that compile identically, so they are
// written as distinct bodies.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the containers or the
// helpers, so the names are address-derived and disclaim identity.

#define BFME_SIXTEEN_BYTE_ITERATOR( PAIR, DISTANCE, ADVANCE )                 \
	struct PAIR##Element                                                      \
	{                                                                         \
		int m_word0;                                                          \
		int m_word1;                                                          \
		int m_word2;                                                          \
		int m_word3;                                                          \
	};                                                                        \
	struct PAIR##Iterator                                                     \
	{                                                                         \
		PAIR##Element *m_current;                                             \
	};                                                                        \
	int DISTANCE( const PAIR##Iterator &first, const PAIR##Iterator &last );  \
	int DISTANCE( const PAIR##Iterator &first, const PAIR##Iterator &last )   \
	{                                                                         \
		return last.m_current - first.m_current;                              \
	}                                                                         \
	void ADVANCE( PAIR##Iterator &it, int count );                            \
	void ADVANCE( PAIR##Iterator &it, int count )                             \
	{                                                                         \
		it.m_current += count;                                                \
	}

BFME_SIXTEEN_BYTE_ITERATOR( Rva000696C0, Rva000696C0Distance, Rva000696E0Advance )
BFME_SIXTEEN_BYTE_ITERATOR( Rva00069710, Rva00069710Distance, Rva00069730Advance )
BFME_SIXTEEN_BYTE_ITERATOR( Rva00069B00, Rva00069B00Distance, Rva00069B20Advance )
BFME_SIXTEEN_BYTE_ITERATOR( Rva00069B80, Rva00069B80Distance, Rva00069BA0Advance )
BFME_SIXTEEN_BYTE_ITERATOR( Rva00472D60, Rva00472D60Distance, Rva00472D80Advance )
BFME_SIXTEEN_BYTE_ITERATOR( Rva004733A0, Rva004733A0Distance, Rva004733C0Advance )
