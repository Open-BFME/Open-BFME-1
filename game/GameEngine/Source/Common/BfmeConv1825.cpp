class BfmePlayerVK;

struct BfmeSetVK
{
	unsigned char m_bfmeRawVK[4];
};

class BfmeListVK
{
public:
	void bfmeAddPlayerVK(BfmePlayerVK *player, int flag);
	void bfmeAddSetVK(BfmeSetVK *set, int flag);
};

class BfmeUnitVK
{
public:
	unsigned char m_bfmeHeadVK[0x20];
	BfmeListVK m_bfmeListVK;
};

class BfmeHolderVK
{
public:
	unsigned char m_bfmeHeadVK[0x204];
	BfmeUnitVK *m_bfmeUnitVK;
};

struct Rva00367E30Logic
{
	BfmePlayerVK *bfmeFindVK(void *key);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeOwnerVK
{
public:
	void bfmeApplyVK(void);

	unsigned char m_bfmeHeadVK[8];
	BfmeHolderVK *m_bfmeHolderVK;
	unsigned char m_bfmeGapVK[0xa0];
	void *m_bfmeKeyVK;
	BfmeSetVK m_bfmeSetVK;
};

void BfmeOwnerVK::bfmeApplyVK(void)
{
	BfmeUnitVK *unit = m_bfmeHolderVK->m_bfmeUnitVK;

	if (unit == 0)
		return;

	BfmeSetVK *set = &m_bfmeSetVK;
	BfmePlayerVK *player = TheBfmeGameLogic->bfmeFindVK(m_bfmeKeyVK);

	if (player != 0)
		unit->m_bfmeListVK.bfmeAddPlayerVK(player, 2);
	else if (set != 0)
		unit->m_bfmeListVK.bfmeAddSetVK(set, 2);
}
