class BfmePlayerTG;

struct BfmeElemTG
{
	void *m_bfmeItemTG;
	unsigned char m_bfmePadTG[28];
};

class BfmeBaseTG
{
public:
	unsigned char m_bfmeHeadTG[4];
	void *m_bfmeKeyTG;
	unsigned char m_bfmeGapTG[0x24];
	BfmeElemTG m_bfmeElemsTG[1];
};

struct Rva00367E30Logic
{
	BfmePlayerTG *bfmeFindTG(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

struct Rva002EE330PlayerList
{
	char bfmeHasTG(BfmePlayerTG *player);
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class ControlBar
{
public:
	void bfmeSelectTG(void *item, int flag);
};

extern ControlBar *TheControlBar;

class BfmeOwnerTG
{
public:
	void bfmeShowTG(int unused);

	unsigned char m_bfmeOwnHeadTG[8];
	BfmeBaseTG *m_bfmeBaseTG;
	int m_bfmeIndexTG;
};

void BfmeOwnerTG::bfmeShowTG(int unused)
{
	BfmeBaseTG *base = m_bfmeBaseTG;
	void *item = base->m_bfmeElemsTG[m_bfmeIndexTG].m_bfmeItemTG;

	if (item == 0)
		return;

	BfmePlayerTG *player = TheBfmeGameLogic->bfmeFindTG(base->m_bfmeKeyTG);

	if (player != 0)
	{
		if (Rva002EE330ThePlayers == 0)
			return;

		if (!Rva002EE330ThePlayers->bfmeHasTG(player))
			return;
	}

	TheControlBar->bfmeSelectTG(item, 0);
}
