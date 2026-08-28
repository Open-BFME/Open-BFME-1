// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LivingWorldCampaign's constructor from a name, retail 0x003AA750,
// 94 bytes. The body carried only a machine byte-dump row; the symbols.csv pin
// names it, and the destructor at 0x003AA7F0 -- already ledgered -- fixes the
// same layout from the other end.
//
// The vtable goes in, the name is copy-constructed into +0x04, and everything
// from +0x08 to the byte at +0x1C is cleared through one zeroed register. The
// member at +0x0C, the one the destructor tears down through its own
// destructor, is a single pointer here and its construction is nothing but that
// zero, so it needs no unwind state of its own -- the only state the frame sets
// is the one covering the name.
//
// The word at +0x08 is in the initialiser list rather than the body. Assigned
// in the body it lands after the +0x0C zero, because that one comes out of a
// member constructor and those all run first.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);			// retail 0x00887B60
	~AsciiString();

private:
	char *m_data;
};

class Rva003A9860
{
public:
	Rva003A9860() { m_bfmeBody = 0; }
	~Rva003A9860();						// ILT 0x00037A4C

private:
	char *m_bfmeBody;
};

class BfmeLivingWorldCampaignBase
{
public:
	virtual void bfmeSlot0(void);
	~BfmeLivingWorldCampaignBase() {}
};

class LivingWorldCampaign : public BfmeLivingWorldCampaignBase
{
public:
	LivingWorldCampaign(const AsciiString &name);
	~LivingWorldCampaign();

private:
	AsciiString m_bfmeName;					// +0x04
	int m_bfme08;						// +0x08
	Rva003A9860 m_bfmeChapters;				// +0x0C
	int m_bfme10;						// +0x10
	int m_bfme14;						// +0x14
	int m_bfme18;						// +0x18
	bool m_bfme1C;						// +0x1C
};

// ??0LivingWorldCampaign@@QAE@ABVAsciiString@@@Z
LivingWorldCampaign::LivingWorldCampaign(const AsciiString &name) :
	m_bfmeName(name),
	m_bfme08(0)
{
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfme1C = false;
}
