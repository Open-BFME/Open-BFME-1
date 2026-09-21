// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// The two-argument constructor at retail 0x005F84E0.  reverse/symbols.csv
// already pins the name ??0T1Base_005F84E0@@QAE@PAX0@Z here because the
// forwarding constructor at 0x005E2530 calls it; this is the body.
//
// WHAT THE BYTES SHOW.  Both arguments are re-pushed unchanged and the matched
// ParticleModule005F2CA0 constructor at 0x005F2CA0 is called with them, so that
// class is the primary base and neither argument initialises a member here.
// Four vftable stores follow: +0x18 first with one address, then +0x00, +0x14
// and +0x18 again.  The lone early store is a second base's own vptr going in
// during its construction, which MSVC 7.1 keeps live even though the derived
// class overwrites that slot; the base's three subobjects therefore sit at
// 0x00, 0x14 and 0x18, exactly the layout T1BaseForwardingCtors.cpp assumes
// for this address.
//
// IDENTITY IS NOT RECOVERED.  The name is address-derived and the vftable
// dwords are DIR32 operands copied from retail.

class T1A1_005DD290
{
public:
	T1A1_005DD290( void *first, void *second );
	virtual void primarySlot();
	virtual ~T1A1_005DD290();

private:
	unsigned int m_storage[ 4 ];
};

class ParticleModuleInterface005F2CA0
{
public:
	virtual void interfaceSlot();
};

class ParticleModule005F2CA0
	: public T1A1_005DD290,
	  public ParticleModuleInterface005F2CA0
{
public:
	ParticleModule005F2CA0( void *first, void *second );
	virtual void moduleSlot();
};

class T1P2_005F84E0
{
public:
	virtual void s0();
};

class T1Base_005F84E0
	: public ParticleModule005F2CA0,
	  public T1P2_005F84E0
{
public:
	T1Base_005F84E0( void *a, void *b );
	virtual void derivedSlot();
};

// ??0T1Base_005F84E0@@QAE@PAX0@Z
T1Base_005F84E0::T1Base_005F84E0( void *a, void *b )
	: ParticleModule005F2CA0( a, b )
{
}
