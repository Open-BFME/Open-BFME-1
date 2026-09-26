// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: LivingWorldRegion destructor, retail 0x0061A780 (164 B).
// Its vtable 0x1117258 is installed at entry and restored to 0x1073744 at
// exit -- lever 4's inline
// empty-virtual-destructor intermediate). Members destroy in reverse
// declaration order: a pointer at +0xec (freed via the already-pinned
// non-virtual ??1Gen_dtor_0061a440 then operator delete), an
// AttributeModifierAuraUpdateModuleDataMemberB at +0xd4, a
// BFMERetailAsciiString at +0xb8, and two more opaque shells at +0x9c and
// +4 (Gen_uwm_00023a7e / Gen_uwm_0004178b).

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class Gen_dtor_0061a440
{
public:
	virtual ~Gen_dtor_0061a440();
};

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();
};

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

	void *m_data;

private:
	void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	~BFMERetailAsciiString() {}
};

class Gen_uwm_00023a7e
{
public:
	~Gen_uwm_00023a7e();
};

class Gen_uwm_0004178b
{
public:
	~Gen_uwm_0004178b();
};

void __cdecl operator delete( void *block );

class LivingWorldRegion : public BfmeBaseVUQ
{
public:
	~LivingWorldRegion();

private:
	Gen_uwm_0004178b m_field04;			// +0x04
	char m_unreconstructed05[ 0x9c - 5 ];
	Gen_uwm_00023a7e m_field9c;			// +0x9c
	char m_unreconstructed9d[ 0xb8 - 0x9d ];
	BFMERetailAsciiString m_fieldB8;		// +0xb8
	char m_unreconstructedBC[ 0xd4 - 0xbc ];
	AttributeModifierAuraUpdateModuleDataMemberB m_fieldD4;	// +0xd4
	char m_unreconstructedD5[ 0xec - 0xd5 ];
	Gen_dtor_0061a440 *m_ptrEC;			// +0xec
};

// ??1LivingWorldRegion@@UAE@XZ
LivingWorldRegion::~LivingWorldRegion()
{
	Gen_dtor_0061a440 *p = m_ptrEC;
	if ( p )
	{
		p->Gen_dtor_0061a440::~Gen_dtor_0061a440();
		operator delete( p );
	}
	m_ptrEC = 0;
}
