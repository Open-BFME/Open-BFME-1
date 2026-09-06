// ??1Gen00608480@@QAE@XZ
// partial score=0.35 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x00608480 (130 B) of a class holding two
// AttributeModifierAuraUpdateModuleDataMemberB members at +0x30 and +0x3C, a
// 109-slot raw pointer array of polymorphic elements at +0x48 (explicit body
// loop deleting through vtable slot 0 and nulling the pointer) and a
// RandomSoundSelectorMap at +0x1FC destructed explicitly first.  The body
// explicitly destructs the map then loops the raw array; the two Attribute
// members are real automatic members, so their reverse-order destruction
// (AttrB then AttrA) is compiler generated after the body -- matching the
// last two EH states.  Member types are opaque address-derived shells sized
// from the offsets with out-of-line destructors.

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();

private:
	char m_body[ 0xC ];
};

class RandomSoundSelectorMap
{
public:
	~RandomSoundSelectorMap();

private:
	char m_body[ 4 ];
};

class S4Elem00608D40
{
public:
	virtual ~S4Elem00608D40();
};

class Gen00608480
{
public:
	~Gen00608480();

private:
	char m_unreconstructed00[ 0x30 ];
	AttributeModifierAuraUpdateModuleDataMemberB m_attrA30;
	AttributeModifierAuraUpdateModuleDataMemberB m_attrA3C;
	S4Elem00608D40 *m_elems[ 109 ];
	char m_map1FC[ 4 ];
};

// ??1Gen00608480@@QAE@XZ
Gen00608480::~Gen00608480()
{
	{
		reinterpret_cast< RandomSoundSelectorMap * >( m_map1FC )->~RandomSoundSelectorMap();
	}

	for( unsigned int i = 0; i != 109; ++i )
	{
		if( m_elems[ i ] )
		{
			delete m_elems[ i ];
			m_elems[ i ] = 0;
		}
	}
}
