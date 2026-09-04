// cl: /DNDEBUG /MD /EHsc

// FILE: LivingWorldCampaign.cpp ///////////////////////////////////////////////
//
// The LivingWorldCampaign record: its constructor from a name (retail
// 0x003AA750), destructor (0x003AA7F0) and the post-parse indexMissions pass
// (0x003A73C0). BFME-only; the INI side lives in INI/INILivingWorldCampaign.cpp,
// which builds the record from the block name, runs indexMissions and hands it
// to the manager.
//
// The member at +0x0C is an STLport vector of 0xDC-byte missions. The
// destructor tears it down through the ILT thunk 0x00037A4C, whose body
// 0x003A9860 the ledger already owns as _STL::vector<Gen003A9860>'s destructor
// (R5VectorDtorEHFramedPolymorphic.cpp, element 0xDC), and indexMissions walks
// it in steps of exactly 0xDC: its divide magic 0x094F2095 with a shift of
// three is 2^35 over 220. That thunk is pinned under the address-derived name
// Rva003A9860 in reverse/symbols.csv, so the vector stand-in keeps that name
// here -- spelled as the real vector, the destructor call would resolve to the
// body instead of the thunk retail calls through.
//
// The word at +0x08 is in the initialiser list rather than the body: assigned
// in the body it would land after the vector's member construction, and retail
// stores it before. That construction throws nothing, so the frame's only
// unwind state is the one covering the name.
//
// The destructor is not virtual: the pin spells it QAE, so the base's cannot
// be virtual either, and what makes the base polymorphic is an ordinary
// virtual member. Declaring the base destructor virtual gives UAE and the
// symbol is then not found at all.
//
// indexMissions starts at the last mission and moves to the first one whose
// flag at +0xD8 is set. The length is recomputed on every trip rather than
// hoisted, so it is read from the members each time.
//
///////////////////////////////////////////////////////////////////////////////

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);			// retail 0x00887B60
	~AsciiString();						// retail 0x00887940

private:
	char *m_data;
};

// One campaign mission; only the flag indexMissions reads is modelled.
class BfmeMission
{
public:
	char m_head[0xD8];
	bool m_chosen;						// +0xD8
	char m_tail[0xDC - 0xD9];
};

// _STL::vector<BfmeMission>, under the name its destructor is pinned by.
class Rva003A9860
{
public:
	Rva003A9860() { m_start = 0; }
	~Rva003A9860();						// ILT 0x00037A4C

	Int size(void) const { return m_finish - m_start; }

	BfmeMission *m_start;					// +0x00
	BfmeMission *m_finish;					// +0x04
	BfmeMission *m_endOfStorage;				// +0x08
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

	void indexMissions(void);

private:
	AsciiString m_name;					// +0x04
	Int m_field08;						// +0x08
	Rva003A9860 m_missions;					// +0x0C
	Int m_current;						// +0x18
	bool m_flag1C;						// +0x1C
};

// ??0LivingWorldCampaign@@QAE@ABVAsciiString@@@Z
LivingWorldCampaign::LivingWorldCampaign(const AsciiString &name) :
	m_name(name),
	m_field08(0)
{
	m_missions.m_finish = 0;
	m_missions.m_endOfStorage = 0;
	m_current = 0;
	m_flag1C = false;
}

// ??1LivingWorldCampaign@@QAE@XZ
LivingWorldCampaign::~LivingWorldCampaign()
{
}

// ?indexMissions@LivingWorldCampaign@@QAEXXZ
void LivingWorldCampaign::indexMissions(void)
{
	m_current = m_missions.size() - 1;

	for (UnsignedInt i = 0; i < (UnsignedInt)m_missions.size(); ++i)
	{
		if (m_missions.m_start[i].m_chosen)
		{
			m_current = i;
			return;
		}
	}
}
