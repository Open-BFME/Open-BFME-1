// cl: /EHs-c-
// Four 31-byte __thiscall const predicates over one packed dword at +4.  Retail
// (the four differ only in the compared immediate, which runs 0x13, 0x0C, 0x0F
// and 0x11):
//
//     mov eax,[ecx+4]
//     mov ecx,eax ; and ecx,0x3F ; cmp cl,<K> ; jne fail
//     shr eax,0xF ; not al ; test al,1 ; jne fail
//     mov eax,1 ; ret
//   fail:
//     xor eax,eax ; ret
//
// WHAT THE BYTES SHOW.  ecx is the base and no argument slot is read, so these
// are const member functions of no arguments; 1 or 0 in a full dword makes the
// return type the four-byte Bool.  0x3F masked and compared as a BYTE is a
// six-bit field at bit 0; bit 15 is tested separately.  Returning 1 needs bit 15
// SET -- `not al` inverts it before the test, so the `jne` fires when it is
// clear.
//
// THE `not` IS IN THE SOURCE AND IT IS BYTE-WIDE.  Every natural spelling of
// "bit 15 is set" folds away: `( bits & 0x8000 ) != 0`, `( bits >> 15 ) & 1`,
// `!!( ( bits >> 15 ) & 1 )` and a one-bit bitfield ALL compile to
// `test ah,ah / jns` in 26 bytes, five short.  Only a byte-wide complement --
// `!( (UnsignedByte)~( bits >> 15 ) & 1 )` -- emits `not al / test al,1`, and
// `F6 D0` rather than `F7 D0` says the complement is on a byte, not a dword.
// So the source tests the NEGATION of a byte-typed flag, which is what an
// inline "is not ..." accessor reads like at its call site.
//
// FOUR ROWS, FOUR CONSTANTS, ONE LAYOUT.  Nothing in these bytes distinguishes
// the class at 0x008A0F20 from the one at 0x008AD030; they are spelled as one
// class here because the field offset, the mask and the tested bit are all the
// same, not because anything proves it.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses.  Nothing relocates:
// all 31 bytes of every row are concrete.

typedef int Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class Rva008A0F20Header
{
public:
	Int m_unreconstructed_00;
	UnsignedInt m_bits04;

	Bool isKind13(void) const;
	Bool isKind0C(void) const;
	Bool isKind0F(void) const;
	Bool isKind11(void) const;
};

#define RVA_KIND_PREDICATE( NAME, KIND )                                  \
	Bool Rva008A0F20Header::NAME(void) const                              \
	{                                                                     \
		return ( m_bits04 & 0x3f ) == KIND                                \
				&& !( (UnsignedByte)~( m_bits04 >> 15 ) & 1 );            \
	}

RVA_KIND_PREDICATE( isKind13, 0x13 )
RVA_KIND_PREDICATE( isKind0C, 0x0c )
RVA_KIND_PREDICATE( isKind0F, 0x0f )
RVA_KIND_PREDICATE( isKind11, 0x11 )
