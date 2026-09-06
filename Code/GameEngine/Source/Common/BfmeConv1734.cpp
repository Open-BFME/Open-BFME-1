class BfmePairAD
{
public:
	BfmePairAD(int first, float second) { m_bfmeAAD = first; m_bfmeBAD = second; }
	BfmePairAD(const BfmePairAD &other) throw()
	{
		m_bfmeAAD = other.m_bfmeAAD;
		m_bfmeBAD = other.m_bfmeBAD;
	}
	~BfmePairAD();

	int m_bfmeAAD;
	float m_bfmeBAD;
};

class Gen_00609320
{
public:
	void bfmeRunAD(void *first, BfmePairAD pair, int a, int b, int c);
};

extern Gen_00609320 *g_bfmeStateDF;

void __stdcall bfmeSendAD(void *first, const BfmePairAD *src)
{
	g_bfmeStateDF->bfmeRunAD(first, BfmePairAD(src->m_bfmeAAD, src->m_bfmeBAD), 0, 1, 1);
}
