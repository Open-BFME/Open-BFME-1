// A record taken out of the list it is in and put at the front of the other one
// the same holder keeps. Both ends of the old list are mended first, and the
// record that was at the front of the new list is pointed back at it.

struct BfmeNodeOJ
{
	unsigned char m_bfmeHead[0xb0];		// 0x000
	BfmeNodeOJ *m_bfmeNext;			// 0x0b0
	BfmeNodeOJ *m_bfmeBack;			// 0x0b4
};

class BfmeThingOJ
{
public:
	void bfmeFrontOJ(BfmeNodeOJ *node);

private:
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeNodeOJ *m_bfmeFrom;			// 0x10
	BfmeNodeOJ *m_bfmeTo;			// 0x14
};

void BfmeThingOJ::bfmeFrontOJ(BfmeNodeOJ *node)
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
}
