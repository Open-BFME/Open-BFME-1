class BfmePlayerTF;

struct BfmeElemTF
{
	void *m_bfmeItemTF;
	unsigned char m_bfmePadTF[28];
};

class BfmeBaseTF
{
public:
	unsigned char m_bfmeHeadTF[4];
	void *m_bfmeKeyTF;
	unsigned char m_bfmeGapTF[0x24];
	BfmeElemTF m_bfmeElemsTF[1];
};

struct Rva00367E30Logic
{
	BfmePlayerTF *bfmeFindTF(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

struct Rva002EE330PlayerList
{
	char bfmeHasTF(BfmePlayerTF *player);
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class ControlBar
{
public:
	void bfmeSelectTF(void *item, int flag);
};

extern ControlBar *TheControlBar;

class BfmeOwnerTF
{
public:
	void bfmeShowTF(int unused);

	BfmeBaseTF *m_bfmeBaseTF;
	int m_bfmeIndexTF;
};

void BfmeOwnerTF::bfmeShowTF(int unused)
{
	BfmeBaseTF *base = m_bfmeBaseTF;
	void *item = base->m_bfmeElemsTF[m_bfmeIndexTF].m_bfmeItemTF;

	if (item == 0)
		return;

	BfmePlayerTF *player = TheBfmeGameLogic->bfmeFindTF(base->m_bfmeKeyTF);

	if (player != 0)
	{
		if (Rva002EE330ThePlayers == 0)
			return;

		if (!Rva002EE330ThePlayers->bfmeHasTF(player))
			return;
	}

	TheControlBar->bfmeSelectTF(item, 0);
}
