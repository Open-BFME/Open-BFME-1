// Twenty-three tiny __thiscall accessors that read a pointer out of the object,
// return zero when it is null, and otherwise return ONE field of what it points
// at.  Retail, in the two encodings that occur:
//
//     mov eax,[ecx+<OFF>] / test eax,eax / je zero
//     mov eax,[eax+<FIELD>] / ret            (four-byte result)
//     zero: xor eax,eax / ret
//
//     ... mov al,[eax+<FIELD>] / ret / zero: xor al,al / ret   (one-byte result)
//
// WHAT THE BYTES SHOW.  `this` in ecx and a bare `ret`: __thiscall, no stack
// arguments.  NOTHING IS RELOCATED anywhere in any of the twenty-three bodies --
// every byte is concrete, so the comparison is total.
//
// THE RESULT WIDTH IS SOURCE EVIDENCE, not scheduling.  `mov al,[eax+F]` paired
// with `xor al,al` is a one-byte result and `mov eax,[eax+F]` paired with
// `xor eax,eax` is a four-byte one; the two differ in length and in opcode, so
// the gate separates them and the table below records which is which.  The
// one-byte form is written as bool; a one-byte integer would serve equally and
// the bytes do not choose between them.
//
// THE GUARD IS AN EARLY RETURN.  The two exits land on SEPARATE `ret`s, the
// taken arm falling out past the untaken one, which is what
// `if (p) { return p->f; } return 0;` produces.
//
// THREE MEMBERS READ THE POINTER AT A NEGATIVE DISPLACEMENT off `this`
// (-0x1C twice, -0xE0 once) and all three then read the same field at +0x168.
// A negative displacement cannot be spelled as a member, so those three are
// written the way the same construct is written in BackPointerGuardedDispatch:
// a fixed byte offset back out of the object.  THE BYTES DECIDE THE OFFSET AND
// NOTHING ELSE -- whether the source reached that pointer through a back
// reference, a multiple-inheritance base or something else is not recovered.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Three pairs are byte-identical
// (0x001BDFF0/0x001BE010, 0x0022A4F0/0x0022CFF0, 0x0063A870/0x00642C80); they
// are distinct rows in the retail image at distinct addresses and each is
// instantiated separately here.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.  The bytes name
// neither the holder, the pointee, nor the field.

// Pointee layouts named for the field they expose.  Holder class names stay
// address-derived: they are the claimed `?get@Rva...` pins.

struct IntAtCh   { char m_leading[ 0xC ];   int  m_value; };
struct IntAt14h  { char m_leading[ 0x14 ];  int  m_value; };
struct IntAt20h  { char m_leading[ 0x20 ];  int  m_value; };
struct IntAt24h  { char m_leading[ 0x24 ];  int  m_value; };
struct IntAt2Ch  { char m_leading[ 0x2C ];  int  m_value; };
struct IntAt3Ch  { char m_leading[ 0x3C ];  int  m_value; };
struct IntAt4Ch  { char m_leading[ 0x4C ];  int  m_value; };
struct IntAt50h  { char m_leading[ 0x50 ];  int  m_value; };
struct IntAt54h  { char m_leading[ 0x54 ];  int  m_value; };
struct IntAt168h { char m_leading[ 0x168 ]; int  m_value; };
struct IntAt1C8h { char m_leading[ 0x1C8 ]; int  m_value; };
struct IntAt1CCh { char m_leading[ 0x1CC ]; int  m_value; };

struct BoolAt41h  { char m_leading[ 0x41 ]; bool m_value; };
struct BoolAt50h  { char m_leading[ 0x50 ]; bool m_value; };
struct BoolAt51h  { char m_leading[ 0x51 ]; bool m_value; };
struct BoolAt52h  { char m_leading[ 0x52 ]; bool m_value; };
struct BoolAtE8h  { char m_leading[ 0xE8 ]; bool m_value; };
struct BoolAt118h { char m_leading[ 0x118 ]; bool m_value; };

#define R2_GUARDED_FIELD_GET( NAME, OFF, POINTEE, TYPE )  \
	class NAME                                          \
	{                                                   \
	public:                                             \
		char m_leading[ OFF ];                          \
		POINTEE *m_pointee;                             \
		TYPE get();                                     \
	};                                                  \
	TYPE NAME::get()                                    \
	{                                                   \
		if ( m_pointee )                                \
		{                                               \
			return m_pointee->m_value;                  \
		}                                               \
		return 0;                                       \
	}

#define R2_GUARDED_FIELD_GET_HEAD( NAME, POINTEE, TYPE )  \
	class NAME                                          \
	{                                                   \
	public:                                             \
		POINTEE *m_pointee;                             \
		TYPE get();                                     \
	};                                                  \
	TYPE NAME::get()                                    \
	{                                                   \
		if ( m_pointee )                                \
		{                                               \
			return m_pointee->m_value;                  \
		}                                               \
		return 0;                                       \
	}

#define R2_GUARDED_FIELD_GET_BACK( NAME, BACK, POINTEE, TYPE )  \
	class NAME                                                \
	{                                                         \
	public:                                                   \
		TYPE get();                                           \
	};                                                        \
	TYPE NAME::get()                                          \
	{                                                         \
		POINTEE *pointee =                                    \
			*(POINTEE **)( (char *)this - BACK );             \
		if ( pointee )                                        \
		{                                                     \
			return pointee->m_value;                          \
		}                                                     \
		return 0;                                             \
	}

R2_GUARDED_FIELD_GET( Rva001BDFF0, 0x204, IntAt1CCh, int )
R2_GUARDED_FIELD_GET( Rva001BE010, 0x204, IntAt1CCh, int )
R2_GUARDED_FIELD_GET( Rva001BE3B0, 0x1EC, IntAt24h, int )
R2_GUARDED_FIELD_GET( Rva001EB140, 0x4, BoolAtE8h, bool )
R2_GUARDED_FIELD_GET( Rva00267FA0, 0x4, BoolAt118h, bool )
R2_GUARDED_FIELD_GET( Rva003BCBF0, 0x28, IntAt3Ch, int )
R2_GUARDED_FIELD_GET( Rva003C6360, 0x4, IntAt4Ch, int )
R2_GUARDED_FIELD_GET( Rva003C6380, 0x4, IntAt50h, int )
R2_GUARDED_FIELD_GET_HEAD( Rva003D4A50, IntAt14h, int )
R2_GUARDED_FIELD_GET_HEAD( Rva003D4AA0, IntAtCh, int )
R2_GUARDED_FIELD_GET( Rva004C1160, 0x8, IntAt1C8h, int )
R2_GUARDED_FIELD_GET( Rva005C3530, 0x1CC, IntAt20h, int )
R2_GUARDED_FIELD_GET( Rva0063A850, 0x64, BoolAt52h, bool )
R2_GUARDED_FIELD_GET( Rva0063A870, 0x64, BoolAt51h, bool )
R2_GUARDED_FIELD_GET( Rva0063A8A0, 0x64, IntAt54h, int )
R2_GUARDED_FIELD_GET( Rva00642C80, 0x64, BoolAt51h, bool )
R2_GUARDED_FIELD_GET( Rva00642CA0, 0x64, BoolAt50h, bool )
R2_GUARDED_FIELD_GET_HEAD( Rva00694900, IntAt2Ch, int )
R2_GUARDED_FIELD_GET_HEAD( Rva00694AA0, BoolAt41h, bool )
R2_GUARDED_FIELD_GET_HEAD( Rva00694AD0, IntAt3Ch, int )

// The three back-reference members.

R2_GUARDED_FIELD_GET_BACK( Rva0022A4F0, 0x1C, IntAt168h, int )
R2_GUARDED_FIELD_GET_BACK( Rva0022CFF0, 0x1C, IntAt168h, int )
R2_GUARDED_FIELD_GET_BACK( Rva00234020, 0xE0, IntAt168h, int )
