extern "C" unsigned char bfmeVftUC[];

class BfmeThingUC;

class BfmeSubUC
{
public:
	void bfmeDropUC(BfmeThingUC *who);
};

class BfmeThingUC
{
public:
	void bfmeResetUC();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	BfmeSubUC *m_bfmeSub;
};

void BfmeThingUC::bfmeResetUC()
{
	BfmeSubUC *sub = m_bfmeSub;
	m_bfmeVft = bfmeVftUC;
	if (sub != 0)
		sub->bfmeDropUC(this);
}
