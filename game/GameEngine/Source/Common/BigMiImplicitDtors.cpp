// cl: /DNDEBUG /MD
// Sixteen 50-byte __thiscall destructors, one shape.  Retail:
//
//     eax = this ? this + <OFF3> : 0 ; [eax]      = <VFTABLE 3>
//     if (this) { [this+8] = <VFTABLE 2>; [this] = <VFTABLE 1>; return; }
//     eax = 0;     [eax]   = <VFTABLE 2>; [this] = <VFTABLE 1>;
//
// WHAT THE BYTES SHOW.  Three vptr stores at offsets <OFF3>, 8 and 0, in that
// order -- descending, which is reverse subobject order and therefore a
// DESTRUCTOR, not a constructor (the matching constructor stores them
// ascending).  Two of the three addresses are computed by a NULL-PROPAGATING
// derived-to-base conversion (test/je/lea/jmp/xor), which is what a pointer
// conversion to a base at a non-zero offset compiles to; a member subobject's
// address is never null and gets a bare displacement instead.  So this is a
// class with THREE polymorphic bases at 0, 8 and <OFF3>.
//
// THE DESTRUCTOR IS COMPILER-GENERATED.  A user-written `~D() {}` over the same
// three bases compiles to 35 bytes of bare `mov [ecx+N],<vftable>` with no
// guards at all -- the front end inlines each base destructor at a known
// displacement.  Only the IMPLICIT destructor, emitted because a local of the
// class is destroyed, keeps the guarded conversions and reproduces all 50
// bytes.  That is the whole reason this file declares no destructor and forces
// emission with a throwaway local instead.
//
// TWO AXES: the third base's offset (0x0C or 0x10, i.e. whether the second base
// carries a data member) and the three vftable addresses.  The offset-0 and
// third vftables are the same address in all sixteen members; the second
// varies over six values.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  All three
// vftables are DIR32 relocation sites the byte gate takes from the target.

class BigMiHead      { public: virtual ~BigMiHead() {} int m_pad; };
class BigMiWide      { public: virtual ~BigMiWide() {} int m_pad; };
// RETAIL STORES FIVE DIFFERENT VFTABLE ADDRESSES ACROSS THESE TWELVE BODIES,
// so they are five classes, not one.  A single class here still byte-gates --
// a vftable address rides a DIR32 relocation and the gate copies those four
// bytes from retail -- but it makes one symbol resolve to five addresses, which
// is exactly what verify_dir32_consistency exists to catch.  The split is not
// cosmetic: it is the difference between claiming one class and claiming five.
class BigMiNarrowA   { public: virtual ~BigMiNarrowA() {} };
class BigMiNarrowB   { public: virtual ~BigMiNarrowB() {} };
class BigMiNarrowC   { public: virtual ~BigMiNarrowC() {} };
class BigMiNarrowD   { public: virtual ~BigMiNarrowD() {} };
class BigMiNarrowE   { public: virtual ~BigMiNarrowE() {} };
class BigMiTail      { public: virtual ~BigMiTail() {} };

#define BFME_MI_IMPLICIT_DTOR( NAME, SECOND )                             \
	class NAME : public BigMiHead, public SECOND, public BigMiTail        \
	{                                                                     \
	public:                                                               \
		int m_v;                                                          \
	};                                                                    \
	void use##NAME()                                                      \
	{                                                                     \
		NAME t;                                                           \
		t.m_v = 1;                                                        \
	}

BFME_MI_IMPLICIT_DTOR( Rva005E56A0, BigMiWide )
BFME_MI_IMPLICIT_DTOR( Rva005E5F80, BigMiNarrowA )
BFME_MI_IMPLICIT_DTOR( Rva005E6460, BigMiWide )
BFME_MI_IMPLICIT_DTOR( Rva005E7540, BigMiNarrowB )
BFME_MI_IMPLICIT_DTOR( Rva005E7860, BigMiNarrowD )
BFME_MI_IMPLICIT_DTOR( Rva005E7C50, BigMiNarrowD )
BFME_MI_IMPLICIT_DTOR( Rva005E8260, BigMiNarrowC )
BFME_MI_IMPLICIT_DTOR( Rva005E83B0, BigMiNarrowE )
BFME_MI_IMPLICIT_DTOR( Rva005EA3C0, BigMiNarrowB )
BFME_MI_IMPLICIT_DTOR( Rva005EA680, BigMiNarrowA )
BFME_MI_IMPLICIT_DTOR( Rva005EA8E0, BigMiNarrowC )
BFME_MI_IMPLICIT_DTOR( Rva005EAB40, BigMiNarrowD )
BFME_MI_IMPLICIT_DTOR( Rva005EADA0, BigMiNarrowE )
BFME_MI_IMPLICIT_DTOR( Rva005EB010, BigMiWide )
BFME_MI_IMPLICIT_DTOR( Rva005EB280, BigMiNarrowD )
BFME_MI_IMPLICIT_DTOR( Rva005EB3C0, BigMiWide )
