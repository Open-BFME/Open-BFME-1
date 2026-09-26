// The nine byte-identical 14-byte bodies at 0x002B2FB0-0x002C7C90.
//
//     test ecx,ecx / je null / lea eax,[ecx+0x340] / ret
//     null: xor eax,eax / ret
//
// WHAT THE BYTES SHOW.  A pointer arrives in ECX, is tested against null, and on
// the non-null path has a constant 0x340 added to it with `lea` -- no load, no
// store, no call.  Adding a fixed displacement to a pointer while mapping null
// to null is the definition of an UPCAST to a base subobject that does not sit
// at offset zero: `&p->base` would be a plain `lea` with no test (taking an
// address cannot fault), and a member LOAD would be `mov`, not `lea`.  The
// null-preserving branch is the language rule that a null pointer converts to a
// null pointer, and MSVC emits exactly this three-instruction shape for it.
//
// The pointer is in ecx and there is no stack argument and no stack cleanup, so
// this is __fastcall, not __thiscall: a __thiscall member would have `this` in
// ecx and could not have been given a null `this` to check.  MSVC 7.1 never
// picks __fastcall on its own at any optimisation level, so the declaration said
// so.  That is what makes these free conversion helpers rather than members.
//
// 0x340 is 832 bytes, so the derived class carries at least that much before the
// base being converted to -- a large object, and the conversion was worth a
// callable helper rather than an inline `lea` because its ADDRESS was needed:
// the shape of a conversion entry in a table.
//
// The layout below reproduces the offset with an explicit padding base; the
// bytes fix 0x340 and say nothing about how the original spelled the members
// that fill it.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Nine distinct addresses in three drawers,
// and in each drawer they come in ADJACENT PAIRS 0x20 apart (0x002B4410 and
// 0x002B4430; 0x002B67F0 and 0x002B6810; 0x002C5650 and 0x002C5670; 0x002C7C70
// and 0x002C7C90) -- two conversions emitted side by side, over and over, which
// is a table of conversions per type rather than one function copied per
// translation unit.  Nothing here defeats inlining, so the per-TU COMDAT reading
// that would justify an alias does not apply.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names either class, so the
// names are address-derived.

class CastPadding
{
public:
	int m_pad[208];
};

class CastBase
{
public:
	int m_value;
};

#define BFME_FASTCALL_BASE_CAST( NAME, DERIVED )                              \
	class DERIVED : public CastPadding, public CastBase                       \
	{                                                                         \
	public:                                                                   \
		int m_tail;                                                           \
	};                                                                        \
	CastBase *__fastcall NAME( DERIVED *p )                                   \
	{                                                                         \
		return p;                                                             \
	}

BFME_FASTCALL_BASE_CAST( rva2b2fb0, Rva002B2FB0Derived )
BFME_FASTCALL_BASE_CAST( rva2b4410, Rva002B4410Derived )
BFME_FASTCALL_BASE_CAST( rva2b4430, Rva002B4430Derived )
BFME_FASTCALL_BASE_CAST( rva2b67f0, Rva002B67F0Derived )
BFME_FASTCALL_BASE_CAST( rva2b6810, Rva002B6810Derived )
BFME_FASTCALL_BASE_CAST( rva2c5650, Rva002C5650Derived )
BFME_FASTCALL_BASE_CAST( rva2c5670, Rva002C5670Derived )
BFME_FASTCALL_BASE_CAST( rva2c7c70, Rva002C7C70Derived )
BFME_FASTCALL_BASE_CAST( rva2c7c90, Rva002C7C90Derived )
