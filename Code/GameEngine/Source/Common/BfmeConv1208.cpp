// Open-BFME5 conversions.

struct BfmeM1208
{
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14;
};

void bfmeMul1208(const BfmeM1208 *a, const BfmeM1208 *b, BfmeM1208 *out)
{
	BfmeM1208 x = *a;
	BfmeM1208 y = *b;

	out->m_bfme00 = y.m_bfme00 * x.m_bfme00 + y.m_bfme04 * x.m_bfme08;
	out->m_bfme04 = x.m_bfme04 * y.m_bfme00 + x.m_bfme0c * y.m_bfme04;
	out->m_bfme08 = x.m_bfme00 * y.m_bfme08 + x.m_bfme08 * y.m_bfme0c;
	out->m_bfme0c = x.m_bfme04 * y.m_bfme08 + x.m_bfme0c * y.m_bfme0c;
	out->m_bfme10 = x.m_bfme00 * y.m_bfme10 + x.m_bfme08 * y.m_bfme14 + x.m_bfme10;
	out->m_bfme14 = x.m_bfme04 * y.m_bfme10 + x.m_bfme0c * y.m_bfme14 + x.m_bfme14;
}
