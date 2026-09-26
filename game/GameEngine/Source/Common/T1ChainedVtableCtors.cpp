// Five one-argument constructors, 32 or 39 bytes, at 0x005E9310-0x005E9780:
//
//     mov eax,[esp+4] / push esi / push eax / mov esi,ecx
//     call <BASE CTOR>
//     mov [esi],   <V0>
//     mov [esi+4], <V1>
//     mov [esi+8], <V2>          ; the 39-byte arity only
//     mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  __thiscall, one dword parameter, `mov eax,esi` at the
// end: a constructor returning `this`.  The parameter is loaded once and
// re-pushed unchanged as the base constructor's only argument -- it is never
// stored into the object, so it initialises no member here; the whole body is
// a member-initialiser forward plus vptr stores.
//
// NOT ONE BASE'S OWN VPTR STORE SURVIVES, which -- exactly as in
// T1BaseForwardingCtors.cpp, and for the same reason -- means there is a
// SINGLE base and the two or three vftables are that base's own.  MSVC 7.1
// elides only the primary base's store; a secondary base's store to +4 stays
// live even when the derived one overwrites it, as the 25-byte constructors in
// T1ArgumentTakingVtableCtors.cpp show at these very addresses.  The
// subobjects are bare vptrs, four bytes each, which puts the stores at 0, 4
// and 8.
//
// THE CHAIN IS VISIBLE IN THE CALL TARGETS.  0x005E9400 and 0x005E9640 call
// 0x005E9430 and 0x005E9670, which are the two 25-byte two-base constructors
// claimed next door -- two bases, two vftables, and these two rows re-stamp
// exactly those two slots.  The base of the 39-byte arity has three, and its
// constructors (0x005E9340, 0x005E9570, 0x005E97B0) are unclaimed, so its
// third subobject is visible here only as the store at +8.
//
// ONE BASE PER CALL TARGET, ONE DERIVED CLASS PER ROW: five distinct targets,
// five distinct vftable triples, five classes.  The vftable dwords are DIR32
// operands copied from retail and are not evidence; what they force is only
// that no two rows are the same class.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.

#define T1_BASE_2( BASE )                                                     \
	class T1P0_##BASE { public: virtual void s0(); };                         \
	class T1P1_##BASE { public: virtual void s0(); };                         \
	class T1Base_##BASE : public T1P0_##BASE, public T1P1_##BASE              \
	{                                                                         \
	public:                                                                   \
		T1Base_##BASE( void *a );                                             \
	};

#define T1_BASE_3( BASE )                                                     \
	class T1P0_##BASE { public: virtual void s0(); };                         \
	class T1P1_##BASE { public: virtual void s0(); };                         \
	class T1P2_##BASE { public: virtual void s0(); };                         \
	class T1Base_##BASE                                                       \
		: public T1P0_##BASE, public T1P1_##BASE, public T1P2_##BASE          \
	{                                                                         \
	public:                                                                   \
		T1Base_##BASE( void *a );                                             \
	};

#define T1_CHAINED_CTOR( ROW, BASE )                                          \
	class T1Derived_##ROW : public T1Base_##BASE                              \
	{                                                                         \
	public:                                                                   \
		T1Derived_##ROW( void *a );                                           \
	};                                                                        \
	T1Derived_##ROW::T1Derived_##ROW( void *a )                               \
		: T1Base_##BASE( a )                                                  \
	{                                                                         \
	}

T1_BASE_2( 005E9430 )
T1_BASE_2( 005E9670 )

T1_BASE_3( 005E9340 )
T1_BASE_3( 005E9570 )
T1_BASE_3( 005E97B0 )

T1_CHAINED_CTOR( 005E9400, 005E9430 )
T1_CHAINED_CTOR( 005E9640, 005E9670 )
T1_CHAINED_CTOR( 005E9310, 005E9340 )
T1_CHAINED_CTOR( 005E9540, 005E9570 )
T1_CHAINED_CTOR( 005E9780, 005E97B0 )
