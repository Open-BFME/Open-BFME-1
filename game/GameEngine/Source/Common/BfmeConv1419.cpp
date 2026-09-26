// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

static const unsigned &bfmeMaxVLT(const unsigned &a, const unsigned &b)
{
	return a < b ? b : a;
}

class BfmeStrVLT
{
public:
	BfmeStrVLT *bfmeAppendVLT(unsigned n, char c);
	void bfmeReserveVLT(unsigned n);
	char *m_bfme00;
	char *m_bfme04;
	char *m_bfme08;
};

BfmeStrVLT *BfmeStrVLT::bfmeAppendVLT(unsigned n, char c)
{
	if ((unsigned)(m_bfme04 - m_bfme00) + n > (unsigned)(m_bfme08 - m_bfme00) - 1)
		bfmeReserveVLT((unsigned)(m_bfme04 - m_bfme00)
			+ bfmeMaxVLT((unsigned)(m_bfme04 - m_bfme00), n));
	if (n > 0)
	{
		memset(m_bfme04 + 1, (unsigned char)c, n - 1);
		m_bfme04[n] = 0;
		m_bfme04[0] = c;
		m_bfme04 += n;
	}
	return this;
}
