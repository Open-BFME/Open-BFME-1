// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AttributeModifierAuraUpdateModuleDataMemberD's destructor, retail
// 0x00129C80, 90 bytes. The body carried only a machine byte-dump row; the
// symbols.csv pin names it, and AttributeModifierAuraUpdateModuleData's own
// destructor -- already ledgered -- is what holds this class as its last
// member.
//
// Three members at +0x30, +0x3C and +0x48, destroyed in that order, which is
// reverse declaration order. They are contiguous and twelve bytes apart, so
// each is twelve bytes wide; the pin added with this row spells the shared
// destructor at that width. There is no vptr store and no base call.

class Rva00026AB2Vec12
{
public:
	~Rva00026AB2Vec12();					// ILT 0x00026AB2

private:
	char *m_bfmeStart;
	char *m_bfmeFinish;
	char *m_bfmeEnd;
};

class AttributeModifierAuraUpdateModuleDataMemberD
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberD();

private:
	unsigned char m_bfmeHead[0x30];
	Rva00026AB2Vec12 m_bfmeFirst;				// +0x30
	Rva00026AB2Vec12 m_bfmeSecond;				// +0x3C
	Rva00026AB2Vec12 m_bfmeThird;				// +0x48
};

// ??1AttributeModifierAuraUpdateModuleDataMemberD@@QAE@XZ
AttributeModifierAuraUpdateModuleDataMemberD::~AttributeModifierAuraUpdateModuleDataMemberD()
{
}
