// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LivingWorldCampaign::indexMissions, retail 0x003A73C0, 117 bytes.
// The body carried only a machine byte-dump row; the symbols.csv pin names it.
//
// The mission vector is the member at +0x0C the destructor at 0x003AA7F0 tears
// down, and this body fixes its element: the divide magic 0x094F2095 with a
// shift of three is 2^35 over that constant, which is 220, and the walk steps
// by exactly 0xDC.
//
// The index at +0x18 starts at the last mission and then moves to the first one
// whose byte at +0xD8 is set, if there is one. The length is recomputed on
// every trip rather than hoisted, so it is read from the members each time.

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_bfmeData;
};

class BfmeMission
{
public:
	char m_bfmeHead[0xD8];
	bool m_bfmeChosen;					// +0xD8
	char m_bfmeTail[0xDC - 0xD9];
};

class BfmeMissionVector
{
public:
	Int bfmeSize(void) const { return m_bfmeFinish - m_bfmeStart; }

	BfmeMission *m_bfmeStart;				// +0x00
	BfmeMission *m_bfmeFinish;				// +0x04
	BfmeMission *m_bfmeEndOfStorage;			// +0x08
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
	void indexMissions(void);

private:
	AsciiString m_bfmeName;					// +0x04
	unsigned char m_bfmePad08[0x04];			// +0x08
	BfmeMissionVector m_bfmeMissions;			// +0x0C
	Int m_bfmeCurrent;					// +0x18
};

// ?indexMissions@LivingWorldCampaign@@QAEXXZ
void LivingWorldCampaign::indexMissions(void)
{
	m_bfmeCurrent = m_bfmeMissions.bfmeSize() - 1;

	for (UnsignedInt i = 0; i < (UnsignedInt)m_bfmeMissions.bfmeSize(); ++i)
	{
		if (m_bfmeMissions.m_bfmeStart[i].m_bfmeChosen)
		{
			m_bfmeCurrent = i;
			return;
		}
	}
}
