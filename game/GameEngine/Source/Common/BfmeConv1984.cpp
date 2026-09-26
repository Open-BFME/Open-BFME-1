class BfmeAETF;

struct BfmeRangeETF
{
	unsigned char m_bfmeBodyETF[0x28];
};

class BfmeMatcherETF
{
public:
	char bfmeMatchETF(BfmeAETF *item, int mode);

	unsigned char m_bfmeBodyETF[4];
};

class BfmeTesterETF
{
public:
	char bfmeTestETF(BfmeRangeETF *first, BfmeRangeETF *second);
};

class BfmeAETF
{
public:
	unsigned char m_bfmeHeadETF[0x110];
	BfmeTesterETF m_bfme110ETF;
};

class BfmeHostETF
{
public:
	char bfmeCheckETF(BfmeAETF *a, BfmeAETF *b);

	unsigned char m_bfmeHeadETF[8];
	BfmeMatcherETF m_bfme08ETF;
	BfmeMatcherETF m_bfme0cETF;
	BfmeRangeETF m_bfme10ETF;
	BfmeRangeETF m_bfme38ETF;
	BfmeRangeETF m_bfme60ETF;
	BfmeRangeETF m_bfme88ETF;
};

char BfmeHostETF::bfmeCheckETF(BfmeAETF *a, BfmeAETF *b)
{
	if (a != 0)
	{
		if (!m_bfme08ETF.bfmeMatchETF(a, 0) ||
			!a->m_bfme110ETF.bfmeTestETF(&m_bfme10ETF, &m_bfme38ETF))
			return 0;
	}

	if (b == 0 ||
		(m_bfme0cETF.bfmeMatchETF(b, 0) &&
		b->m_bfme110ETF.bfmeTestETF(&m_bfme60ETF, &m_bfme88ETF)))
		return 1;

	return 0;
}
