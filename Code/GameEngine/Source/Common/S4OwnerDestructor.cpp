// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x00464E20 (140 B) of S4Owner (see
// S4DrainStringVector.cpp for the four already-matched drain methods, called
// here on `this` with no offset adjustment -- the same object).  The body
// installs S4Owner's own vtable (0x010F7114, also installed by the matched
// constructor Rva00464B20Ctor.cpp) then drains each of the four
// vector<AsciiString> members through its matched drain method before the
// compiler-generated reverse member unwind destroys the four vectors
// (opaque address-derived shells sized 0xC, the STLport vector destructor
// ILT already pinned as AttributeModifierAuraUpdateModuleDataMemberB).

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();

private:
	char m_body[ 0xC ];
};

class S4Owner
{
public:
	virtual ~S4Owner();

private:
	void s4drain00464B60( void );
	void s4drain00464C10( void );
	void s4drain00464CC0( void );
	void s4drain00464D70( void );

	AttributeModifierAuraUpdateModuleDataMemberB m_vec0;
	AttributeModifierAuraUpdateModuleDataMemberB m_vec1;
	AttributeModifierAuraUpdateModuleDataMemberB m_vec2;
	AttributeModifierAuraUpdateModuleDataMemberB m_vec3;
};

// ??1S4Owner@@UAE@XZ
S4Owner::~S4Owner()
{
	s4drain00464B60();
	s4drain00464C10();
	s4drain00464CC0();
	s4drain00464D70();
}
