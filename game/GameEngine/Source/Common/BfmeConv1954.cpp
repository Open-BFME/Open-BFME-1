extern char g_bfmeEmptyERJ[];

struct BfmeStrDataERJ
{
	int m_bfmeRefERJ;
	int m_bfmeLenERJ;
	char m_bfmeTextERJ[1];
};

class BfmeStrERJ
{
public:
	const char *bfmeTextERJ() const
	{
		return m_bfmeDataERJ ? m_bfmeDataERJ->m_bfmeTextERJ : g_bfmeEmptyERJ;
	}

	BfmeStrDataERJ *m_bfmeDataERJ;
};

class BfmeKeyGenERJ
{
public:
	int bfmeNameToKeyERJ(const char *name);
};

extern BfmeKeyGenERJ *g_bfmeKeyGenERJ;

class BfmePlayerERJ
{
public:
	unsigned char m_bfmeHeadERJ[0x20];
	int m_bfmeKeyERJ;
};

class BfmePlayersERJ
{
public:
	BfmePlayerERJ *bfmeNthERJ(int index);
};

extern BfmePlayersERJ *g_bfmePlayersERJ;

struct BfmeEntryERJ
{
	unsigned char m_bfmeHeadERJ[8];
	void *m_bfmeValueERJ;
	unsigned char m_bfmeTailERJ[12];
};

class BfmeTableERJ
{
public:
	BfmeEntryERJ *bfmeAtERJ(int index)
	{
		if (index >= 0 && index < m_bfmeCountERJ)
			return m_bfmeEntriesERJ + index;

		return 0;
	}

	unsigned char m_bfmeHeadERJ[0x28];
	int m_bfmeCountERJ;
	BfmeEntryERJ m_bfmeEntriesERJ[1];
};

extern BfmeTableERJ *g_bfmeTableERJ;

void * __stdcall bfmeLookupERJ(BfmeStrERJ *name)
{
	int key = g_bfmeKeyGenERJ->bfmeNameToKeyERJ(name->bfmeTextERJ());

	for (int i = 0; i < g_bfmeTableERJ->m_bfmeCountERJ; ++i)
	{
		BfmePlayerERJ *player = g_bfmePlayersERJ->bfmeNthERJ(i);

		if (player != 0 && player->m_bfmeKeyERJ == key)
			return g_bfmeTableERJ->bfmeAtERJ(i)->m_bfmeValueERJ;
	}

	return 0;
}
