// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU calls through it using its own
// file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

class BfmeThingBTC;

class BfmeSinkBTC
{
public:
	void bfmeTwoBTC(BfmeThingBTC *what);
};

class BfmeThingBTC
{
public:
	void bfmeOneBTC(void *owner);
	unsigned char m_bfmeHead[0x214];
	void *m_bfmeOwner;
};

void bfmeGoBTC(BfmeThingBTC *what)
{
	what->bfmeOneBTC(what->m_bfmeOwner);
	((BfmeSinkBTC *)TheGameLogic)->bfmeTwoBTC(what);
}
