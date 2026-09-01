// Open-BFME5 conversions.

struct BfmeHdrVKK
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
	unsigned short m_bfme04;
	unsigned short m_bfme06;
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
	BfmeStrVKK *bfmeReverseVKK();
	void bfmeReserveVKK(unsigned a, int b, unsigned c, int d, unsigned e);
	BfmeHdrVKK *m_bfme00;
};

void BfmeStrVKK::bfmeTruncVKK(unsigned n)
{
	unsigned len = m_bfme00->m_bfme02;
	if (len > n)
		len = n;
	bfmeReserveVKK(n, 0, len, 1, len);
}

BfmeStrVKK *BfmeStrVKK::bfmeReverseVKK()
{
	unsigned len = m_bfme00->m_bfme02;
	bfmeReserveVKK(len, 0, len, 1, len);
	unsigned n = m_bfme00->m_bfme02;
	if (n > 1)
	{
		char *a = (char *)m_bfme00 + 8;
		char *b = a + n - 1;
		if (a < b)
		{
			do
			{
				char x = *b;
				char y = *a;
				*a = x;
				++a;
				*b = y;
				--b;
			} while (a < b);
		}
		m_bfme00->m_bfme06 = 0;
	}
	return this;
}
