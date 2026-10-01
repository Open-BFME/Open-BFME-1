// TU-local view of the canonical GameLogic (GameLogic.cpp); the real class is
// only forward declared here, so every field read casts through this view.
struct BfmeGlobalCHE
{
	unsigned char m_bfmeHead[0x3c];
	unsigned int m_bfmeNow;
};

class GameLogic;

extern GameLogic *TheGameLogic;

class BfmeThingCHE
{
public:
	void bfmeUpdateCHE();
	int bfmeGoCHE();
	unsigned char m_bfmeHead[0x98];
	unsigned int m_bfmeNext;
	int m_bfmeCached;
};

int BfmeThingCHE::bfmeGoCHE()
{
	unsigned int now = ((BfmeGlobalCHE *)TheGameLogic)->m_bfmeNow;
	if (now >= m_bfmeNext)
	{
		m_bfmeNext = now + 0x19;
		bfmeUpdateCHE();
	}
	return m_bfmeCached;
}
