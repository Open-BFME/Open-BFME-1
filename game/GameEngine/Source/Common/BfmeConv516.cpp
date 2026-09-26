struct BfmeSubBRB
{
	unsigned char m_bfmeHead[4];
};

class BfmeSinkBRB
{
public:
	void bfmeDoBRB(BfmeSubBRB *sub, void *what);
};

extern BfmeSinkBRB *g_bfmeSinkBRB;

class BfmeThingBRB
{
public:
	void bfmeGoBRB(void *what);
	unsigned char m_bfmeHead[0x274];
	BfmeSubBRB m_bfmeSub;
};

void BfmeThingBRB::bfmeGoBRB(void *what)
{
	if (g_bfmeSinkBRB != 0)
		g_bfmeSinkBRB->bfmeDoBRB(&m_bfmeSub, what);
}
