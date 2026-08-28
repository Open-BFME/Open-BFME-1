struct BfmeSubBFC
{
	unsigned char m_bfmeHead[4];
};

class BfmeSinkBFC
{
public:
	void bfmeAddBFC(BfmeSubBFC *sub);
};

extern BfmeSinkBFC *g_bfmeSinkBFC;

class BfmeThingBFC
{
public:
	void bfmeGoBFC();
	unsigned char m_bfmeHead[0xdc];
	BfmeSubBFC m_bfmeSub;
};

void BfmeThingBFC::bfmeGoBFC()
{
	g_bfmeSinkBFC->bfmeAddBFC(&m_bfmeSub);
}
