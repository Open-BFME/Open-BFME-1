// cl: /EHsc
//
// Seven members that allocate one object with `new` and construct it with a
// constructor the compiler INLINED, so the vptr stamping that constructor does
// is visible in the caller.  Retail, for the two-argument form:
//
//     push <SIZE> / call operator new / add esp,4 / mov esi,eax
//     test esi,esi / je null
//     push this / push <ARG> / mov ecx,esi / call <BASE CTOR>
//     mov [esi],   <VFTABLE 0>
//     mov [esi+8], <VFTABLE 8>
//     mov [esi+0xC],<VFTABLE 0xC>
//     mov eax,esi
//   null: return eax
//
// WHY THE CONSTRUCTOR IS INLINE HERE AND OUT OF LINE IN Q4NewOwnerFactories.cpp
// and V3CloneFactories.cpp: those bodies end at the `call` because the class
// they construct has its constructor in another translation unit, so nothing of
// it is visible.  These bodies continue with vptr stores, and a caller cannot
// stamp a callee's vptrs -- only the constructor itself can.  So the constructed
// class's constructor is defined where the factory is, it forwards to a base
// constructor that is NOT (that is the surviving `call`), and the stores after
// the call are the derived class's own vptr initialisation.
//
// THE CONSTRUCTED CLASSES ARE ALREADY IN THE TREE, by their vftables.  The five
// two-argument rows stamp {0, 8, 0xC}; 0x005E7420's triple 0x011124FC /
// 0x011124F8 / 0x011124E4 is the same triple 0x005EA2E0 stamps, and the other
// four match 0x005EAA80, 0x005EB1C0, 0x005EA820 and 0x005EACE0 the same way --
// all landed in V3CopyCtorForwarders.cpp.  So each of those classes has TWO
// constructors: a copy constructor that stayed out of line, and this
// two-argument one that did not.  The 0x005ECA20 row is the same story for
// 0x005ECAB0's four-slot triple-plus-one, with the copy constructor at
// 0x005ECAB0 itself as the callee.
//
// THE SIZE IS `sizeof`, exactly, because a plain `new` takes it as its operand.
// The slot offsets account for the first 0x10, 0x1C or 0x20 bytes of each
// class; the rest is carried as a size-only member, as Q4NewOwnerFactories.cpp
// does.
//
// The fs:[0] frame comes from `-EHsc`.  The pushed handler address and funcinfo
// are DIR32 operands copied from retail and claim nothing.
//
// IDENTITY IS NOT RECOVERED.  Every name is an address.

// ---- layout pieces; none of them emits a byte of any body here -------------

class V3Slot0	{ public: virtual void s0(); virtual ~V3Slot0() {} int m_a, m_b, m_c, m_d; };
class V3Slot0N	{ public: virtual void s0(); virtual ~V3Slot0N() {} int m_a; };
class V3Slot1	{ public: virtual void s0(); virtual ~V3Slot1() {} };
class V3Slot2	{ public: virtual void s0(); virtual ~V3Slot2() {} };
class V3Slot3	{ public: virtual void s0(); virtual ~V3Slot3() {} };

// ---- the two-argument form -------------------------------------------------
//
// NAME is the factory's own address; BASE is the out-of-line constructor's.

#define V3_NEW_TWO_ARG_FACTORY( NAME, BASE, SIZE )                         \
	class V3Host##NAME;                                                    \
	class BASE : public V3Slot0N, public V3Slot1, public V3Slot2           \
	{                                                                      \
	public:                                                                \
		BASE( void *arg, V3Host##NAME *owner );                            \
	};                                                                     \
	class NAME##Object : public BASE                                       \
	{                                                                      \
	public:                                                                \
		NAME##Object( void *arg, V3Host##NAME *owner )                     \
			: BASE( arg, owner ) {}                                        \
		char m_storage[ SIZE - 0x10 ];                                     \
	};                                                                     \
	class V3Host##NAME                                                     \
	{                                                                      \
	public:                                                                \
		NAME##Object *create( void *arg );                                 \
	};                                                                     \
	NAME##Object *V3Host##NAME::create( void *arg )                        \
	{                                                                      \
		return new NAME##Object( arg, this );                              \
	}

V3_NEW_TWO_ARG_FACTORY( Rva005E7420, Rva005EE8A0, 0x5c )
V3_NEW_TWO_ARG_FACTORY( Rva005E76E0, Rva005FFAC0, 0x2c )
V3_NEW_TWO_ARG_FACTORY( Rva005E7AD0, Rva006008D0, 0x44 )
V3_NEW_TWO_ARG_FACTORY( Rva005E8150, Rva005FE010, 0x14 )
V3_NEW_TWO_ARG_FACTORY( Rva005E82A0, Rva005FED10, 0x14 )

// ---- the clone form: one argument, and it is the receiver ------------------

class Rva005EBD40 : public V3Slot0, public V3Slot1, public V3Slot2
{
public:
	Rva005EBD40( const Rva005EBD40 & );
};

class Rva005EBCC0Object : public Rva005EBD40
{
public:
	Rva005EBCC0Object( const Rva005EBCC0Object &o ) : Rva005EBD40( o ) {}
	Rva005EBCC0Object *clone() const;
	char m_storage[ 0x8e4 - 0x1c ];
};

Rva005EBCC0Object *Rva005EBCC0Object::clone() const
{
	return new Rva005EBCC0Object( *this );
}

class Rva005ECAB0 : public V3Slot0, public V3Slot1, public V3Slot2, public V3Slot3
{
public:
	Rva005ECAB0( const Rva005ECAB0 & );
};

class Rva005ECA20Object : public Rva005ECAB0
{
public:
	Rva005ECA20Object( const Rva005ECA20Object &o ) : Rva005ECAB0( o ) {}
	Rva005ECA20Object *clone() const;
	char m_storage[ 0x64 - 0x20 ];
};

Rva005ECA20Object *Rva005ECA20Object::clone() const
{
	return new Rva005ECA20Object( *this );
}
