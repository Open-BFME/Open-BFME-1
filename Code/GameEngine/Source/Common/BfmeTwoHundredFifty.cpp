// A record taken out of the list it is in, put at the front of the other list
// the same holder keeps, and then wound back to its resting state.

struct BfmeNodeOM
{
	unsigned char m_bfmeHead[0xc];		// 0x0000
	int m_bfmeFirst;			// 0x000c
	int m_bfmeSecond;			// 0x0010
	int m_bfmeThird;			// 0x0014
	unsigned char m_bfmeGap[0x12cc];	// 0x0018
	int m_bfmeFourth;			// 0x12e4
	int m_bfmeFifth;			// 0x12e8
	unsigned char m_bfmeOff;		// 0x12ec
	unsigned char m_bfmeGap2[0xc];		// 0x12ed
	unsigned char m_bfmeOn;			// 0x12f9
	unsigned char m_bfmeGap3[2];		// 0x12fa
	BfmeNodeOM *m_bfmeNext;			// 0x12fc
	BfmeNodeOM *m_bfmeBack;			// 0x1300
};

class BfmeThingOM
{
public:
	void bfmeDropOM(BfmeNodeOM *node);

private:
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeNodeOM *m_bfmeFrom;			// 0x10
	BfmeNodeOM *m_bfmeTo;			// 0x14
};

void BfmeThingOM::bfmeDropOM(BfmeNodeOM *node)
{
	if (node == 0)
		return;

	if (node->m_bfmeNext != 0)
		node->m_bfmeNext->m_bfmeBack = node->m_bfmeBack;

	if (node->m_bfmeBack != 0)
		node->m_bfmeBack->m_bfmeNext = node->m_bfmeNext;
	else
		m_bfmeFrom = node->m_bfmeNext;

	node->m_bfmeBack = 0;

	node->m_bfmeNext = m_bfmeTo;

	if (m_bfmeTo != 0)
		m_bfmeTo->m_bfmeBack = node;

	m_bfmeTo = node;

	node->m_bfmeOff = 0;
	node->m_bfmeOn = 1;
	node->m_bfmeFifth = 0;
	node->m_bfmeFourth = 0;
	node->m_bfmeFirst = 0;
	node->m_bfmeSecond = 0;
	node->m_bfmeThird = 0;
}
