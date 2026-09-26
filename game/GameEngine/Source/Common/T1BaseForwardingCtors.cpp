// Thirty-nine two-argument constructors, 46 or 53 bytes each, that do nothing
// but hand both arguments to a base constructor and then re-stamp every vptr
// the object owns.  Retail, the 46-byte arity:
//
//     mov eax,[esp+8]            ; second argument
//     push esi / mov esi,ecx     ; this
//     mov ecx,[esp+8]            ; first argument (esp moved by the push)
//     push eax / push ecx        ; (first, second) in __thiscall order
//     mov ecx,esi / call <BASE CTOR>
//     mov [esi],   <V0>
//     mov [esi+14],<V1>
//     mov [esi+18],<V2>
//     mov eax,esi / pop esi / ret 8
//
// WHAT THE BYTES SHOW.  `this` in ecx and `ret 8` is __thiscall with two dword
// parameters; the trailing `mov eax,esi` returns `this`, which is what a
// constructor does and what a void member never does.  Neither argument is
// touched between entry and the two pushes -- they are re-pushed unchanged, in
// the order that makes the callee see (first, second) -- so the body is a
// member-initialiser forward and nothing else.  No parameter is stored into
// the object, so no member is initialised from either one here.
//
// THE CONSTANT STORES ARE VPTRS, and their count and offsets read out the
// hierarchy.  0, 0x14, 0x18 (and for the 53-byte arity a fourth at 0x1C or
// 0x20) are distinct slots, each written exactly once, in ascending order:
// that is a constructor stamping its own vftables after all base construction
// has finished.  What matters is what is NOT here -- not one base's OWN vptr
// store survives.  MSVC 7.1 kills only the PRIMARY base's store (the derived
// store to +0 kills it); a secondary base's store to +0x14 stays live even
// though the derived one overwrites the same slot.  That asymmetry is visible
// three rows below, where exactly one such store does survive.  Zero surviving
// stores therefore cannot mean "several secondary bases whose stores were
// elided"; it means there is exactly ONE base, the one the `call` constructs,
// and the several vftables are that base's own -- it is the multiply-
// inheriting class, not this one.  Its constructor is a `call` and not inlined
// code, so it is defined outside this translation unit, which is why it
// appears here as a declaration with no body.
//
// THE OFFSETS SIZE THE BASE'S SUBOBJECTS.  The first runs 0x14 wide (a vptr
// plus four dwords), the second is a bare vptr at 0x14, the third a bare vptr
// at 0x18.  The 53-byte arity adds a fourth: at 0x1C when the third subobject
// is a bare vptr, at 0x20 when it carries one extra dword.  Twelve bases take
// the 0x1C form and two the 0x20 form, and the displacement is the only thing
// that separates them.
//
// ONE BASE PER CALL TARGET, ONE DERIVED CLASS PER ROW.  Five rows call
// 0x005E3A20 and four other targets are called twice each; those rows share a
// base and are spelled against one shared declaration.  Every row's vftable
// dwords are distinct from every other row's, and a vftable address is a
// class, so no two rows can be the same derived class -- 39 addresses, 39
// classes.  The vftable dwords themselves are DIR32 operands copied from
// retail and are not evidence; what they force is only that the classes
// differ.
//
// THE THREE 46-BYTE ROWS AT THE BOTTOM ARE THE CONTRARY SHAPE, and they are
// what makes the reading above a reading rather than a guess:
//
//     call <BASE CTOR> / mov [esi+14],<VB> / mov [esi],<V0> / mov [esi+14],<V1>
//
// A slot written twice with two different addresses is a base writing its own
// vptr and the derived overwriting it.  So here there ARE two bases: a first
// at +0 whose constructor is the `call` and whose own store was eliminated,
// and a second at +0x14 whose constructor is INLINED -- it has no body to
// call, so it is implicit or trivial -- and whose store survives.  Same first
// base (all three call 0x005DD290), two distinct second bases across the three
// rows.
//
// IDENTITY IS NOT RECOVERED.  Nothing in these bodies names a class: no string
// reaches them, no RTTI is walked, and the base constructors they call are
// themselves unclaimed.  Every name below is derived from an address -- the
// row's own for a derived class, the call target's for a base, the stored
// vftable's for the two second bases -- so the rows claim their bytes without
// asserting an identity nobody has proved.  Promoting them is a mechanical
// repoint once the bases are named.

// --------------------------------------------------------------- three vptrs

#define T1_BASE_3( BASE )                                                     \
	class T1P0_##BASE { public: virtual void s0(); int m_pad[ 4 ]; };         \
	class T1P1_##BASE { public: virtual void s0(); };                         \
	class T1P2_##BASE { public: virtual void s0(); };                         \
	class T1Base_##BASE                                                       \
		: public T1P0_##BASE, public T1P1_##BASE, public T1P2_##BASE          \
	{                                                                         \
	public:                                                                   \
		T1Base_##BASE( void *a, void *b );                                    \
	};

// ---------------------------------------------------------------- four vptrs

#define T1_BASE_4( BASE )                                                     \
	class T1P0_##BASE { public: virtual void s0(); int m_pad[ 4 ]; };         \
	class T1P1_##BASE { public: virtual void s0(); };                         \
	class T1P2_##BASE { public: virtual void s0(); };                         \
	class T1P3_##BASE { public: virtual void s0(); };                         \
	class T1Base_##BASE                                                       \
		: public T1P0_##BASE, public T1P1_##BASE,                             \
		  public T1P2_##BASE, public T1P3_##BASE                              \
	{                                                                         \
	public:                                                                   \
		T1Base_##BASE( void *a, void *b );                                    \
	};

// four vptrs, third subobject one dword wider, so the fourth lands at 0x20

#define T1_BASE_4W( BASE )                                                    \
	class T1P0_##BASE { public: virtual void s0(); int m_pad[ 4 ]; };         \
	class T1P1_##BASE { public: virtual void s0(); };                         \
	class T1P2_##BASE { public: virtual void s0(); int m_extra; };            \
	class T1P3_##BASE { public: virtual void s0(); };                         \
	class T1Base_##BASE                                                       \
		: public T1P0_##BASE, public T1P1_##BASE,                             \
		  public T1P2_##BASE, public T1P3_##BASE                              \
	{                                                                         \
	public:                                                                   \
		T1Base_##BASE( void *a, void *b );                                    \
	};

#define T1_FORWARDING_CTOR( ROW, BASE )                                       \
	class T1Derived_##ROW : public T1Base_##BASE                              \
	{                                                                         \
	public:                                                                   \
		T1Derived_##ROW( void *a, void *b );                                  \
	};                                                                        \
	T1Derived_##ROW::T1Derived_##ROW( void *a, void *b )                      \
		: T1Base_##BASE( a, b )                                               \
	{                                                                         \
	}

T1_BASE_3( 005E3950 )
T1_BASE_3( 005E3A20 )
T1_BASE_3( 005E3B90 )
T1_BASE_3( 005E3C90 )
T1_BASE_3( 005F2D20 )
T1_BASE_3( 005F3750 )
T1_BASE_3( 005F4E90 )
T1_BASE_3( 005F6530 )
T1_BASE_3( 005F7820 )
T1_BASE_3( 005F84E0 )

T1_FORWARDING_CTOR( 005E24B0, 005F3750 )
T1_FORWARDING_CTOR( 005E2530, 005F84E0 )
T1_FORWARDING_CTOR( 005E25B0, 005F6530 )
T1_FORWARDING_CTOR( 005E2630, 005F2D20 )
T1_FORWARDING_CTOR( 005E26B0, 005F7820 )
T1_FORWARDING_CTOR( 005E2740, 005F4E90 )
T1_FORWARDING_CTOR( 005E3B10, 005E3A20 )
T1_FORWARDING_CTOR( 005E4F60, 005E3950 )
T1_FORWARDING_CTOR( 005E4FE0, 005E3A20 )
T1_FORWARDING_CTOR( 005E5060, 005E3A20 )
T1_FORWARDING_CTOR( 005E50E0, 005E3B90 )
T1_FORWARDING_CTOR( 005E5160, 005E3C90 )
T1_FORWARDING_CTOR( 005E6580, 005E3950 )
T1_FORWARDING_CTOR( 005E6670, 005E3A20 )
T1_FORWARDING_CTOR( 005E6760, 005E3A20 )
T1_FORWARDING_CTOR( 005E6850, 005E3B90 )
T1_FORWARDING_CTOR( 005E6940, 005E3C90 )

T1_BASE_4( 005E3390 )
T1_BASE_4( 005E3480 )
T1_BASE_4( 005E35B0 )
T1_BASE_4( 005E36C0 )
T1_BASE_4( 005E37C0 )
T1_BASE_4( 005EEBC0 )
T1_BASE_4( 005EFD60 )
T1_BASE_4( 005FBBE0 )
T1_BASE_4( 005FDE80 )
T1_BASE_4( 005FEAD0 )
T1_BASE_4( 005FFDB0 )
T1_BASE_4( 00600BE0 )

T1_BASE_4W( 005FC920 )
T1_BASE_4W( 005FD550 )

T1_FORWARDING_CTOR( 005E2EF0, 005EFD60 )
T1_FORWARDING_CTOR( 005E2FA0, 005FDE80 )
T1_FORWARDING_CTOR( 005E3060, 005FEAD0 )
T1_FORWARDING_CTOR( 005E30F0, 005FC920 )
T1_FORWARDING_CTOR( 005E3180, 005FD550 )
T1_FORWARDING_CTOR( 005E3210, 005FBBE0 )
T1_FORWARDING_CTOR( 005E51E0, 005E3390 )
T1_FORWARDING_CTOR( 005E5270, 005E3480 )
T1_FORWARDING_CTOR( 005E5300, 005E35B0 )
T1_FORWARDING_CTOR( 005E5390, 005E36C0 )
T1_FORWARDING_CTOR( 005E5420, 005E37C0 )
T1_FORWARDING_CTOR( 005E6A30, 005E3390 )
T1_FORWARDING_CTOR( 005E6B30, 005E3480 )
T1_FORWARDING_CTOR( 005E6C30, 005E35B0 )
T1_FORWARDING_CTOR( 005E6D30, 005E36C0 )
T1_FORWARDING_CTOR( 005E6E30, 005E37C0 )
T1_FORWARDING_CTOR( 005E72C0, 005EEBC0 )
T1_FORWARDING_CTOR( 005E7580, 005FFDB0 )
T1_FORWARDING_CTOR( 005E78A0, 00600BE0 )

// ------------------------------------------ two bases, the second's own vptr

class T1A1_005DD290
{
public:
	T1A1_005DD290( void *a, void *b );
	virtual void s0();
	int m_pad[ 4 ];
};

#define T1_SECOND_BASE( VT )                                                  \
	class T1A2_##VT { public: virtual void s0(); };

#define T1_FORWARDING_CTOR_2( ROW, VT )                                       \
	class T1Derived_##ROW : public T1A1_005DD290, public T1A2_##VT            \
	{                                                                         \
	public:                                                                   \
		T1Derived_##ROW( void *a, void *b );                                  \
	};                                                                        \
	T1Derived_##ROW::T1Derived_##ROW( void *a, void *b )                      \
		: T1A1_005DD290( a, b )                                               \
	{                                                                         \
	}

T1_SECOND_BASE( 0110F9AC )
T1_SECOND_BASE( 0110F9CC )

T1_FORWARDING_CTOR_2( 005DEC00, 0110F9AC )
T1_FORWARDING_CTOR_2( 005DEC40, 0110F9CC )
T1_FORWARDING_CTOR_2( 005E38E0, 0110F9CC )
