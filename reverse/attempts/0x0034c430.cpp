// ?bfmeFindAAT@BfmeHostAAT@@QAEPAURva002EE330Player@@XZ
// partial score=0.95 date=2026-09-16
struct Rva002EE330Player
{
	unsigned char m_bfmeHeadAAT[0x2c];
	int m_bfme2CAAT;
};

struct Rva002EE330PlayerList
{
	unsigned char m_bfmeHeadLAAT[0x10];
	int m_bfmeCountAAT;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

Rva002EE330Player *__stdcall Rva002EF110GetPlayer(int index);

class BfmeSubAAT
{
public:
	Rva002EE330Player *bfmeCheckAAT();
};

class BfmeHostAAT
{
public:
	Rva002EE330Player *bfmeFindAAT();

	unsigned char m_bfmeHeadHAAT[0x170ac];
	BfmeSubAAT *m_bfme170ACAAT;
};

Rva002EE330Player *BfmeHostAAT::bfmeFindAAT()
{
	BfmeSubAAT *s = m_bfme170ACAAT;

	if (s == 0)
		return 0;

	Rva002EE330Player *r = s->bfmeCheckAAT();

	if (r != 0)
		return r;

	for (int i = 0; i < Rva002EE330ThePlayers->m_bfmeCountAAT; ++i)
	{
		Rva002EE330Player *p = Rva002EF110GetPlayer(i);

		if (p->m_bfme2CAAT == 0)
			return p;
	}

	return 0;
}
