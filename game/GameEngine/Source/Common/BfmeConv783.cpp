struct BfmeOtherDUI
{
	unsigned char m_bfmeHead[0x3c];
	void *m_bfmeField;
};

extern BfmeOtherDUI *g_bfmeDUI;

struct BfmeSubDUI
{
	unsigned char m_bfmeHead[0xa0];
	void *m_bfmeSlot;
};

struct BfmeThingDUI
{
	void bfmeGoDUI();
	void bfmeOneDUI();
	unsigned char m_bfmeHead[0x44];
	BfmeSubDUI *m_bfmeSub;
};

void BfmeThingDUI::bfmeGoDUI()
{
	bfmeOneDUI();
	BfmeSubDUI *sub = m_bfmeSub;
	if (sub)
		sub->m_bfmeSlot = g_bfmeDUI->m_bfmeField;
}
