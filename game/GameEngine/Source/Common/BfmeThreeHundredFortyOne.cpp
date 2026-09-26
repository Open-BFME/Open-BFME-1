extern "C" unsigned char bfmeVftTB[];

class BfmeThingTB
{
public:
	void bfmeBaseTB(int one, int two);
	BfmeThingTB *bfmeInitTB();
	void *m_bfmeVft;
};

BfmeThingTB *BfmeThingTB::bfmeInitTB()
{
	bfmeBaseTB(0x1e, 8);
	m_bfmeVft = bfmeVftTB;
	return this;
}
