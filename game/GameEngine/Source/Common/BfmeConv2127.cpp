extern float g_bfmeScaleBC;

struct BfmeNodeABA
{
	unsigned char m_bfmeHeadABA[0x14];
	unsigned int m_bfme14ABA;
};

struct BfmeIterABA
{
	BfmeNodeABA *m_bfmeNodeABA;
};

class BfmeListABA
{
public:
	void bfmeRangeABA(BfmeIterABA *first, BfmeIterABA *last);

	BfmeNodeABA *m_bfmeHeadABA;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadLABA[0x3c];
	unsigned int m_bfme3CABA;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

struct BfmeOwnerABA
{
	unsigned char m_bfmeHeadOABA[0x164];
	unsigned int m_bfme164ABA;
};

class BfmeHostABA
{
public:
	int bfmeProgressABA(BfmeIterABA last);
};

int BfmeHostABA::bfmeProgressABA(BfmeIterABA last)
{
	BfmeOwnerABA *o = *(BfmeOwnerABA **)((char *)this - 0x1c);
	BfmeListABA *l = (BfmeListABA *)((char *)this + 0xa8);
	BfmeIterABA first;

	l->bfmeRangeABA(&first, &last);

	if (first.m_bfmeNodeABA == l->m_bfmeHeadABA)
		return 100;

	unsigned int elapsed = TheBfmeGameLogic->m_bfme3CABA - first.m_bfmeNodeABA->m_bfme14ABA;
	unsigned int limit = o->m_bfme164ABA;

	if (elapsed > limit)
		return 100;

	if (elapsed == 0)
		return 0;

	if (limit != 0)
		return (int)((float)elapsed / (float)limit * g_bfmeScaleBC);

	return 100;
}
