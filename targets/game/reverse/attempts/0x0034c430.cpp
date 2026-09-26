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

	int getPlayerCount()
	{
		return m_bfmeCountAAT;
	}

	Rva002EE330Player *getNthPlayer(int index);
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

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
	if (m_bfme170ACAAT != 0)
	{
		Rva002EE330Player *r = m_bfme170ACAAT->bfmeCheckAAT();

		if (r != 0)
			return r;

		for (int i = 0; i < Rva002EE330ThePlayers->getPlayerCount(); ++i)
		{
			Rva002EE330Player *p = Rva002EE330ThePlayers->getNthPlayer(i);

			if (p->m_bfme2CAAT == 0)
				return p;
		}
	}

	return 0;
}
