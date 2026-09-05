// cl: /DNDEBUG /MD /EHsc
//
// Rva003C1A50::start, retail 0x003C1AD0, 306 bytes.
//
// After the sibling reset at 0x003C1A50: GameLogic +0x1A0 FP-guard, then
// TheWritableGlobalData +0x94 campaign name or MordorCampaign/GondorCampaign
// from the bool argument, then owner notify/clear.

template <typename T>
class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text)
		: StringBase<char>(text)
	{
	}
	AsciiString(const AsciiString &other)
		: StringBase<char>(other)
	{
	}
	~AsciiString() {}
	void *data() const { return m_data; }
};

class GameLogicFp
{
public:
	char m_pad[0x1A0];
	int m_fp;
};

extern GameLogicFp *TheBfmeGameLogic;
extern void setFPMode();

class Glo012ED5C8Type
{
public:
	char m_pad00[0x8E];
	unsigned char m_at8E;
	char m_pad8F[0x94 - 0x8F];
	AsciiString m_at94;
};

extern Glo012ED5C8Type *TheWritableGlobalData;

class Glo012F1024Type
{
public:
	void setCampaign(AsciiString *name);
};

extern Glo012F1024Type *TheLivingWorldCampaignManager;

class Glo012F1028Sub
{
public:
	void first();
	void bfmeNotify();
};

class Glo012F4B98Type
{
public:
	void after();
};

extern Glo012F4B98Type *Glo012F4B98;

class Rva003C1A50
{
public:
	void run();
	void start(unsigned char mordor);
	void refreshEntries003BEC30();

private:
	char m_pad00[0x28];
	Glo012F1028Sub *m_at28;
};

static int stringLive(void *data)
{
	if (!data)
		return 0;
	if (*(short *)((char *)data + 4) == 0)
		return 0;
	return 1;
}

void Rva003C1A50::start(unsigned char mordor)
{
	run();

	GameLogicFp *logic = TheBfmeGameLogic;
	int *fp = &logic->m_fp;
	if (*fp == 0)
		setFPMode();
	++*fp;

	Glo012ED5C8Type *gd = TheWritableGlobalData;
	AsciiString *slot = &gd->m_at94;
	if (stringLive(slot->data()))
		TheLivingWorldCampaignManager->setCampaign(slot);
	else if (mordor)
	{
		AsciiString name("MordorCampaign");
		TheLivingWorldCampaignManager->setCampaign(&name);
	}
	else
	{
		AsciiString name("GondorCampaign");
		TheLivingWorldCampaignManager->setCampaign(&name);
	}

	gd = TheWritableGlobalData;
	if (!gd->m_at8E)
	{
		if (!stringLive(gd->m_at94.data()))
			m_at28->first();
	}
	m_at28->bfmeNotify();
	refreshEntries003BEC30();
	Glo012F4B98->after();
	--TheBfmeGameLogic->m_fp;
}
