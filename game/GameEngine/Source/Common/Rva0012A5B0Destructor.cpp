// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x0012A5B0 (160 B).  Non-virtual (the
// literal "vftable" store 0x01073744 at [this+0] happens LAST, right before
// the epilogue, not first as a real C++ virtual dtor would) -- BFME's
// manual function-table-pointer idiom (see BfmeConv881.cpp's m_bfmeVft
// fields), modelled as a plain first member whose inline destructor writes
// the literal back.  Reverse member unwind: six matched AudioEventRTS
// members 0x70 bytes apart at +0x70/+0xE0/+0x150/+0x1C0/+0x230/+0x2A0, one
// opaque address-derived member at +0x64 (0xC bytes, the generic
// AttributeModifierAuraUpdateModuleDataMemberB pin), then the manual
// vft-slot restore.  Member types are opaque address-derived shells sized
// from the offsets with out-of-line destructors except AudioEventRTS which
// resolves by its real matched name.

struct BfmeVftSlot0012A5B0
{
	~BfmeVftSlot0012A5B0()
	{
		m_p = (void *)0x01073744;
	}

	void *m_p;
};

class AudioEventRTS
{
public:
	~AudioEventRTS();

private:
	char m_body[ 0x70 ];
};

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();

private:
	char m_body[ 0xC ];
};

class Rva0012A5B0
{
public:
	~Rva0012A5B0();

private:
	BfmeVftSlot0012A5B0 m_vft;
	unsigned char m_unreconstructed04[ 0x64 - 4 ];
	AttributeModifierAuraUpdateModuleDataMemberB m_member64;
	AudioEventRTS m_audio70;
	AudioEventRTS m_audioE0;
	AudioEventRTS m_audio150;
	AudioEventRTS m_audio1C0;
	AudioEventRTS m_audio230;
	AudioEventRTS m_audio2A0;
};

// ??1Rva0012A5B0@@QAE@XZ
Rva0012A5B0::~Rva0012A5B0()
{
}
