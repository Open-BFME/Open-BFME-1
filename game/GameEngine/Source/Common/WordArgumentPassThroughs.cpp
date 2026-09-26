// The four byte-identical 8-byte bodies at 0x00523A20, 0x00549FE0, 0x0054AF20
// and 0x0056B220.
//
//     mov ax,word ptr [esp+8] / ret 8
//
// WHAT THE BYTES SHOW.  Eight bytes of stack argument cleaned by the callee is
// __stdcall with two dword parameters.  The first is never read at all.  The
// second is read SIXTEEN BITS WIDE into ax and left there as the return value,
// so both the parameter and the return type are 16-bit; a 32-bit parameter
// returned unchanged would have been `mov eax,[esp+8]`, one byte shorter, and a
// widening conversion would have been a movzx or movsx.  The upper half of eax
// is left holding whatever the caller had, which only a 16-bit return type
// permits.
//
// So each of these is `unsigned short f(<something>, unsigned short v) { return
// v; }` -- a two-argument function that ignores its first argument and hands
// back its second unchanged.  That is the shape of a default or identity
// implementation plugged into a table of translation callbacks: the signature is
// dictated by the table, the body does nothing.  Four of them exist out of line
// and unreferenced because their addresses, not their code, were what mattered.
//
// The bytes cannot tell signed from unsigned for either the parameter or the
// return -- nothing in an 8-byte body extends anything -- so the spelling below
// picks one and the claim rests on the width, which the bytes do fix.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four distinct addresses spread across four
// unrelated stretches of .text; nothing defeats inlining here, so there is no
// COMDAT-per-translation-unit reading to justify asserting they are one.
//
// IDENTITY IS NOT RECOVERED.  No table in the image is known to point at them
// and nothing names them, so the names are address-derived.

#define BFME_WORD_PASS_THROUGH( NAME )                                        \
	unsigned short __stdcall NAME( int unused, unsigned short value )         \
	{                                                                         \
		return value;                                                         \
	}

BFME_WORD_PASS_THROUGH( rva523a20 )
BFME_WORD_PASS_THROUGH( rva549fe0 )
BFME_WORD_PASS_THROUGH( rva54af20 )
BFME_WORD_PASS_THROUGH( rva56b220 )
