// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads through its own file-local
// view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

struct BfmeOtherDUI
{
	unsigned char m_bfmeHead[0x3c];
	void *m_bfmeField;
};

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
		sub->m_bfmeSlot = ((BfmeOtherDUI *)TheGameLogic)->m_bfmeField;
}
