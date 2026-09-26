// cl: /EHs-c-
//
// Four constructors from the 0x005E97B0..0x0060D680 slice that call nothing:
// they stamp one vftable pointer and then fill fields with constants.  With no
// call and no unwind frame there is nothing to resolve, so these are decided
// entirely by their own bytes.
//
// WHAT FIXES EACH LAYOUT.  `mov eax,ecx` ... `ret` (or `ret 4`) is __thiscall
// returning the receiver -- a constructor.  MSVC 7.1 orders a constructor as
// base subobjects, then vptrs, then members, and does not reorder straight-line
// constant stores, so the store sequence read off retail IS the declaration
// order of the fields and the position of the vftable store says which fields
// belong to a base.  Every field written is a slot the class owns, so the
// highest offset written plus its width is the class's size.
//
// TWO OF THE FOUR ARE DEFAULT CONSTRUCTORS OF CLASSES THIS SLICE ALREADY NAMES,
// and the vftable address is what ties them:
//
//   0x005FF910 stamps 0x011129B4, the vftable
//   game/GameEngine/Source/GameClient/Gen_005e9a20.cpp records for
//   Gen_005e9a20, and fills exactly the seven dwords at +0x04..+0x1C that that
//   file's copy constructor copies.  Same vftable, same field run: same class.
//
//   0x00600750 stamps 0x01112A98, which is the vftable the copy constructor at
//   0x005EA0D0 installs -- the one T4ForwardingCtorChainL2.cpp pins as
//   T4B005EA0D0 because the constructor at 0x005EA080 uses that class as a
//   base.  The copy constructor copies thirteen dwords at +0x04..+0x34; this
//   one writes the same thirteen slots.  Same vftable, same field run: same
//   class, and its default constructor.  It also SPLITS that field run: the
//   three dwords at +0x04..+0x0C are set to 1.0f BEFORE the vftable store and
//   the rest after, and only a base subobject's initialisation can precede the
//   vptr.  So T4B005EA0D0 has a three-float non-polymorphic base -- which is
//   also why its vptr sits at 0 and the base at +4 rather than the other way
//   round.
//
// 0x00604E90 is a copy constructor of the smallest shape in the slice: stamp a
// vftable, copy one dword out of the source.  It is spelled as its own class
// because its vftable address, 0x0108971C, appears nowhere else in the slice.
//
// IDENTITY IS NOT RECOVERED for T4Ctor0060CCC0 and T4Ctor00604E90; those names
// come from addresses.  Gen_005e9a20 and T4B005EA0D0 are spelled the way the
// files that already carry them spell them, so that the ledger has one name per
// class rather than a second address-derived alias.  A zero written through a
// shared register is not evidence of the field's type, so the plain-integer
// fields are spelled `int` and only the constants that decode as floats are
// spelled `float`.

typedef int Int;

// ---------------------------------------------------------------------------
// 0x005FF910 -- the default constructor of Gen_005e9a20.  The class is spelled
// as game/GameEngine/Source/GameClient/Gen_005e9a20.cpp spells it.
// ---------------------------------------------------------------------------
class Gen_005e9a20
{
public:
	Gen_005e9a20();
	Gen_005e9a20( const Gen_005e9a20 &other );
	virtual ~Gen_005e9a20();
	virtual void v1( void );
	virtual void v2( void );
	virtual void v3( void );

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
};

Gen_005e9a20::Gen_005e9a20()
	: m_field04( 0 ),
	  m_field08( 0 ),
	  m_field0C( 0 ),
	  m_field10( 0 ),
	  m_field14( 0 ),
	  m_field18( 0 ),
	  m_field1C( 1 )
{
}

// ---------------------------------------------------------------------------
// 0x00600750 -- the default constructor of T4B005EA0D0.
// ---------------------------------------------------------------------------
class T4Scale005EA0D0
{
public:
	T4Scale005EA0D0() : m_x( 1.0f ), m_y( 1.0f ), m_z( 1.0f ) {}
	float m_x;
	float m_y;
	float m_z;
};

class T4B005EA0D0 : public T4Scale005EA0D0
{
public:
	T4B005EA0D0();
	T4B005EA0D0( const T4B005EA0D0 &other );
	virtual void s0();

	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
};

T4B005EA0D0::T4B005EA0D0()
	: m_field10( 0 ),
	  m_field14( 0 ),
	  m_field18( 0 ),
	  m_field1C( 0 ),
	  m_field20( 0 ),
	  m_field24( 0 ),
	  m_field28( 0 ),
	  m_field2C( 0 ),
	  m_field30( 0 ),
	  m_field34( 1 )
{
}

// ---------------------------------------------------------------------------
// 0x00604E90 -- vftable plus one copied dword.
// ---------------------------------------------------------------------------
class T4Ctor00604E90
{
public:
	T4Ctor00604E90( const T4Ctor00604E90 &other );
	virtual void s0();
	void *m_field04;
};

T4Ctor00604E90::T4Ctor00604E90( const T4Ctor00604E90 &other )
	: m_field04( other.m_field04 )
{
}
