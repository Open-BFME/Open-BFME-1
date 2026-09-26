// The five byte-identical 36-byte constructors at 0x0016F640, 0x0016FE50,
// 0x001701A0, 0x001C0990 and 0x0028D8C0.  Retail:
//
//     mov eax,ecx / xor ecx,ecx / mov edx,eax
//     mov [edx],ecx / mov [edx+4],ecx / mov [edx+8],ecx / mov [edx+0xC],ecx
//     mov [edx+0x10],ecx / mov [edx+0x14],ecx / mov [edx+0x18],ecx
//     mov [edx+0x1C],ecx / mov [edx+0x20],ecx / mov [edx+0x24],ecx / ret
//
// WHAT THE BYTES SHOW.  `this` in ecx, no arguments, plain `ret`, and `this`
// copied into eax on entry and left there: a __thiscall constructor, which is
// the one shape that returns `this` while taking nothing.  Ten consecutive
// dwords from +0 to +0x24 are set to zero and nothing else happens, so the
// object is forty bytes of raw storage with no vftable (a polymorphic class
// would store its vftable pointer at +0 instead of zero).
//
// `mov edx,eax` IS THE WHOLE PUZZLE, and it is what rules out every C++ form of
// "zero the members".  A member-init list, ten assignments in the body, an
// inlined base or member-subobject constructor, an inlined free helper taking
// `this` as a pointer parameter, a `for` loop over an `int[10]`, and a
// reference alias to `*this` were all compiled: every one of them is 34 bytes
// and stores through eax (`mov [eax],ecx` / `mov [eax+4],ecx` / ...), because
// eax already holds the address and the optimiser has no reason to copy it.
// Only `memset( this, 0, 40 )` produces the extra copy -- MSVC 7.1 expands the
// intrinsic with its destination in its OWN register, which costs the two bytes
// that make retail 36 and not 34.  So the source did not name the members here;
// it cleared the object wholesale.
//
// That also explains why the count is ten and not, say, nine or eleven: the
// intrinsic unrolls a byte count, and forty bytes is what the class measures.
// The MEMBERS are not evidenced -- nothing distinguishes ten ints from five
// pointers-and-counts -- so the class below is written as the forty bytes the
// bytes actually prove, and no member layout is invented.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Five addresses across five drawers of the
// image: five classes that happen to be forty bytes and to clear themselves.
//
// IDENTITY IS NOT RECOVERED.  No caller, no vftable slot and no string reaches
// any of the five, so the names are address-derived and disclaim identity.

#include <string.h>

#define BFME_TEN_WORD_ZEROING_CONSTRUCTOR( NAME )                             \
	class NAME##Record                                                        \
	{                                                                         \
	public:                                                                   \
		char m_storage[ 40 ];                                                 \
		NAME##Record();                                                       \
	};                                                                        \
	NAME##Record::NAME##Record()                                              \
	{                                                                         \
		memset( this, 0, sizeof( *this ) );                                   \
	}

BFME_TEN_WORD_ZEROING_CONSTRUCTOR( Rva0016F640 )
BFME_TEN_WORD_ZEROING_CONSTRUCTOR( Rva0016FE50 )
BFME_TEN_WORD_ZEROING_CONSTRUCTOR( Rva001701A0 )
BFME_TEN_WORD_ZEROING_CONSTRUCTOR( Rva001C0990 )
BFME_TEN_WORD_ZEROING_CONSTRUCTOR( Rva0028D8C0 )
