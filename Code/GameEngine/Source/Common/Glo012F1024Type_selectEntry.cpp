// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Glo012F1024Type::setCampaign, retail 0x003B41A0, 131 bytes.
// Same campaign-manager layout as step at 0x003B3900. Address-derived method
// name: no caller recovered a source identifier.

class AsciiString { public: unsigned short *m_data; };

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_bfmeHead[0x8E];
	Bool m_flag8E;
	char m_pad8F[0x94 - 0x8F];
	AsciiString m_at94;
};

extern GlobalData *TheWritableGlobalData;

class GameLogic
{
public:
	void invoke(void);
};

extern GameLogic *TheBfmeGameLogic;

class Glo012F1028Sub
{
public:
	void consume(AsciiString *key);
	void refresh003CAD90(void);
};

class Glo012F1028Type
{
public:
	char m_bfmeHead[0x28];
	Glo012F1028Sub *m_bfmeSub;
};

extern Glo012F1028Type *Glo012F1028;

class Glo012F1024Entry
{
public:
	void stepFlag(void);
	char m_head[0x1C];
	unsigned char m_flag;
	char m_tail[0x03];
};

class BfmeEntryVector
{
public:
	Glo012F1024Entry *m_bfmeStart;
	Glo012F1024Entry *m_bfmeFinish;
};

class Glo012F1024Type
{
public:
	void setCampaign(AsciiString *key);
	int lookup(AsciiString *key);

private:
	char m_pad00[0x0C];
	Int m_bfmeIndex;
	BfmeEntryVector m_bfmeEntries;
	char m_pad18[0x1C - 0x18];
	unsigned char m_at1C;
};

// ?setCampaign@Glo012F1024Type@@QAEXPAVAsciiString@@@Z
void Glo012F1024Type::setCampaign(AsciiString *key)
{
	Glo012F1028Sub *sub = Glo012F1028->m_bfmeSub;
	if (sub != 0)
	{
		sub->consume(key);
		sub->refresh003CAD90();
	}

	TheBfmeGameLogic->invoke();

	if (TheWritableGlobalData->m_flag8E
		|| (TheWritableGlobalData->m_at94.m_data != 0 && TheWritableGlobalData->m_at94.m_data[2] != 0))
	{
		int n = lookup(key);
		m_bfmeIndex = n;
		if (n != -1)
		{
			Glo012F1024Entry *start = m_bfmeEntries.m_bfmeStart;
			m_at1C = start[n].m_flag;
			start[n].stepFlag();
		}
		else
			m_at1C = 0;
	}
}
