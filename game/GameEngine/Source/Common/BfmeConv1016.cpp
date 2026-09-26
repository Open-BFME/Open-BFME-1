// Open-BFME5 conversions.

class BfmeIter1016
{
public:
	unsigned short bfmeNext1016(int a);
};

class BfmeR1016
{
public:
	BfmeR1016 &bfmeGo1016R(int a);

	BfmeIter1016 *m_bfmeIt;
	char m_bfmeOk;
};

BfmeR1016 &BfmeR1016::bfmeGo1016R(int a)
{
	int ok;

	if (m_bfmeOk != 0 && m_bfmeIt->bfmeNext1016(a) != 0xffff)
		ok = 1;
	else
		ok = 0;

	m_bfmeOk = (char)ok;
	return *this;
}

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

extern BfmeList1016 g_bfmeList1016;

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
