struct BfmeSubBRB
{
	unsigned char m_bfmeHead[4];
};

class BfmeSinkBRB
{
public:
	void bfmeDoBRB(BfmeSubBRB *sub, void *what);
};

class LightPointSystem;
extern LightPointSystem *TheLightPointSystem;

class BfmeThingBRB
{
public:
	void bfmeGoBRB(void *what);
	unsigned char m_bfmeHead[0x274];
	BfmeSubBRB m_bfmeSub;
};

void BfmeThingBRB::bfmeGoBRB(void *what)
{
	if (((BfmeSinkBRB *)TheLightPointSystem) != 0)
		((BfmeSinkBRB *)TheLightPointSystem)->bfmeDoBRB(&m_bfmeSub, what);
}
