// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LivingWorldCampaign's destructor, retail 0x003AA7F0, 86 bytes.
// The body carried only a machine byte-dump row; the symbols.csv pin names it.
//
// The class's own vtable goes down first, then the member at +0x0C through its
// own destructor and the AsciiString at +0x04, and the base's vtable goes back
// at the end -- the base destructor inlined to nothing but that store. The word
// at +0x08 has no destructor.
//
// The destructor is not virtual: the pin spells it QAE, so the base's own
// destructor cannot be virtual either, and what makes the base polymorphic is
// an ordinary virtual member. Declaring the base destructor virtual gives UAE
// and the symbol is then not found at all.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();						// retail 0x00887940

private:
	char *m_data;
};

class Rva003A9860
{
public:
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
	~LivingWorldCampaign();

private:
	AsciiString m_bfmeName;					// +0x04
	unsigned char m_bfmePad08[0x04];			// +0x08
	Rva003A9860 m_bfmeChapters;				// +0x0C
};

// ??1LivingWorldCampaign@@QAE@XZ
LivingWorldCampaign::~LivingWorldCampaign()
{
}
