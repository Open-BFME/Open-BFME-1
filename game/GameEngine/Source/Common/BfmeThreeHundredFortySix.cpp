extern "C" unsigned char bfmeVftTG[];

class BfmeThingTG
{
public:
	void bfmeBaseTG(int one, int two);
	BfmeThingTG *bfmeInitTG();
	void *m_bfmeVft;
	unsigned char m_bfmeGap[0x1c];
	int m_bfmeOne;
};

BfmeThingTG *BfmeThingTG::bfmeInitTG()
{
	bfmeBaseTG(0x23, 8);
	m_bfmeVft = bfmeVftTG;
	m_bfmeOne = 0;
	return this;
}
