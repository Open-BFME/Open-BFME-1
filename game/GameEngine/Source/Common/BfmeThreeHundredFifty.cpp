extern "C" unsigned char bfmeVftTK[];

class BfmeThingTK
{
public:
	void bfmeBaseTK();
	BfmeThingTK *bfmeInitTK();
	void *m_bfmeVft;
	void *m_bfmeOne;
	void *m_bfmeTwo;
	void *m_bfmeThree;
	void *m_bfmeFour;
};

BfmeThingTK *BfmeThingTK::bfmeInitTK()
{
	m_bfmeVft = bfmeVftTK;
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	m_bfmeThree = 0;
	m_bfmeFour = 0;
	bfmeBaseTK();
	return this;
}
