// ?bfmeBestA2@BfmeStoreA2@@QAEMXZ
// partial score=0.95 date=2026-09-09
extern const float BfmeZeroRange;

struct BfmeElemA2
{
	int m_bfme00A2;
	unsigned char m_bfmeGapA2[4];
	float m_bfme08A2;
	unsigned char m_bfmeMidA2[0x20 - 0xc];
	unsigned char m_bfme20A2;
	unsigned char m_bfmeTailA2[3];
};

__forceinline const float &bfmeMaxA2(const float &a, const float &b)
{
	return a > b ? a : b;
}

class BfmeStoreA2
{
public:
	float bfmeBestA2();

	unsigned char m_bfmeHeadA2[0x2c];
	BfmeElemA2 *m_bfme2CA2;
	BfmeElemA2 *m_bfme30A2;
};

float BfmeStoreA2::bfmeBestA2()
{
	float best = BfmeZeroRange;

	BfmeElemA2 *e = m_bfme2CA2;
	BfmeElemA2 *end = m_bfme30A2;

	while (e != end)
	{
		if (e->m_bfme20A2)
		{
			float cand = e->m_bfme00A2 ? BfmeZeroRange : e->m_bfme08A2;

			best = bfmeMaxA2(cand, best);
		}

		++e;
	}

	return best;
}
