extern "C" unsigned char bfmeVftXB[];

class BfmeThingXB
{
public:
	void bfmeSetupXB(void *one, void *two, void *three, void *four);
	BfmeThingXB *bfmeInitXB(void *one, void *two, void *three);
	void *m_bfmeVft;
	unsigned char m_bfmeGapOne[0x10];
	void *m_bfmeOne;
	unsigned char m_bfmeInner[0x80];
	int m_bfmeFlag;
};

BfmeThingXB *BfmeThingXB::bfmeInitXB(void *one, void *two, void *three)
{
	bfmeSetupXB(m_bfmeInner, &m_bfmeFlag, two, three);
	m_bfmeOne = one;
	m_bfmeFlag = 0;
	m_bfmeVft = bfmeVftXB;
	return this;
}
