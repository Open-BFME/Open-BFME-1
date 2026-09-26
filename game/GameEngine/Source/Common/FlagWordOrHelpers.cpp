// The four byte-identical 15-byte helpers at 0x00694C10, 0x00694C30, 0x006958C0
// and 0x006958E0 -- two adjacent pairs, 0x20 apart within each pair.
//
//     mov eax,[esp+4] / mov edx,[eax] / mov ecx,[esp+8] / or edx,ecx
//     mov [eax],edx / ret
//
// WHAT THE BYTES SHOW.  No `this`, no stack cleanup, two dword arguments:
// __cdecl.  The first argument is dereferenced for both a read and a write and
// is never itself modified, so it is a pointer to a single dword; the second is
// used directly as the operand of the OR, so it is a value.  The whole body is
// `*mask |= bits;` and it returns nothing -- eax is left holding the pointer
// only because that is where it was loaded, and nothing after the store touches
// it.
//
// A helper this small exists out of line at four addresses because it is passed
// around, not because it was called: a two-instruction OR would have been
// inlined at any call site the compiler could see.  The pairing supports that --
// each of the two drawers holds two of them a fixed 0x20 apart, the layout of a
// small table of same-signature functions.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four distinct addresses in two separate
// stretches; nothing here defeats inlining, so there is no per-translation-unit
// COMDAT reading to justify asserting they are one function.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the helper or says what
// the bits mean, so the names are address-derived.

#define BFME_FLAG_WORD_OR( NAME )                                             \
	void NAME( int *mask, int bits )                                          \
	{                                                                         \
		*mask |= bits;                                                        \
	}

BFME_FLAG_WORD_OR( rva694c10 )
BFME_FLAG_WORD_OR( rva694c30 )
BFME_FLAG_WORD_OR( rva6958c0 )
BFME_FLAG_WORD_OR( rva6958e0 )
