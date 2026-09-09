// ?bfmeAllocABD@BfmeHostABD@@QAEHPBDPAX11@Z
// cl: /DNDEBUG /MD /EHsc

void *Rva00807920(const char *name, int cap);

class Rva00803080;

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *entry);
};

struct Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void registerService(const char *a, const char *b, int c);
};

Rva007EB810Diag *Rva007EB810Get(void);

extern const char g_bfmeNameABD[];
extern const char g_bfmeKindABD[];

struct BfmeSlotABD
{
	void *m_bfme00ABD;
	void *m_bfme04ABD;
	void *m_bfme08ABD;
	void *m_bfme0CABD;
};

class BfmeHostABD
{
public:
	int bfmeAllocABD(const char *name, void *a, void *b, void *c);

	unsigned char m_bfmeHeadABD[4];
	Rva00803080 *m_bfme04ABD;
	BfmeSlotABD m_bfmeSlotsABD[4];
	int m_bfme48ABD;
	Rva007EAServiceList *m_bfme4CABD;
};

int BfmeHostABD::bfmeAllocABD(const char *name, void *a, void *b, void *c)
{
	if (m_bfme48ABD < 4)
	{
		int idx;

		for (int i = 0; i < 4; ++i)
		{
			if (m_bfmeSlotsABD[i].m_bfme00ABD == 0)
			{
				idx = i;
				goto selected;
			}
		}
		idx = -1;

	selected:
		if (idx == -1)
			Rva007EB810Get()->registerService(g_bfmeNameABD, g_bfmeKindABD, 0x60);

		m_bfmeSlotsABD[idx].m_bfme00ABD = b;
		m_bfmeSlotsABD[idx].m_bfme04ABD = c;
		m_bfmeSlotsABD[idx].m_bfme08ABD = a;
		m_bfmeSlotsABD[idx].m_bfme0CABD = Rva00807920(name, 0x2710);

		++m_bfme48ABD;

		m_bfme4CABD->add((Rva00803080 *)&m_bfme04ABD);

		return 0;
	}

	return -1;
}
