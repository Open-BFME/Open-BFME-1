class BfmeThingBTC;

class BfmeSinkBTC
{
public:
	void bfmeTwoBTC(BfmeThingBTC *what);
};

extern BfmeSinkBTC *g_bfmeSinkBTC;

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
	g_bfmeSinkBTC->bfmeTwoBTC(what);
}
