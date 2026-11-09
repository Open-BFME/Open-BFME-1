// Open-BFME5 conversions.

struct BfmeNode1016
{
	char m_bfmePad[4];
	int m_bfmeCount;
	BfmeNode1016 *m_bfmeNext;
	BfmeNode1016 *m_bfmePrev;
};

class BfmeList1016
{
public:
	void bfmeErase1016(int n);

	BfmeNode1016 *m_bfmeHead;
	int m_bfmeSize;
};

BfmeList1016 g_bfmeList1016;

void bfmeGo1016T(void)
{
	if (g_bfmeList1016.m_bfmeSize != 0) {
		g_bfmeList1016.bfmeErase1016(g_bfmeList1016.m_bfmeHead->m_bfmeCount);
		g_bfmeList1016.m_bfmeHead->m_bfmeNext = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeHead->m_bfmeCount = 0;
		g_bfmeList1016.m_bfmeHead->m_bfmePrev = g_bfmeList1016.m_bfmeHead;
		g_bfmeList1016.m_bfmeSize = 0;
	}
}
