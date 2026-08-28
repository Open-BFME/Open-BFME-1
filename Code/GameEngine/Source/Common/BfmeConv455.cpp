class BfmeThingBFG
{
public:
	void bfmeTailBFG();
	void bfmeGoBFG();
	unsigned char m_bfmeHead[0x18];
	int m_bfmeWidth;
	int m_bfmeHeight;
};

void BfmeThingBFG::bfmeGoBFG()
{
	m_bfmeWidth = 0x280;
	m_bfmeHeight = 0x1e0;
	bfmeTailBFG();
}
