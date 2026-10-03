class BfmeAETF;

// Retail calls both members through their ILT thunks (RVA 0x0001DA34 and
// RVA 0x0003C2E5); the bodies behind them are not recovered yet. Naming the
// thunks keeps the references resolvable at link time and still encodes each
// call as retail's call rel32.
extern void j_0001da34();
extern void j_0003c2e5();

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

static __forceinline char bfmeMatchETF(BfmeMatcherETF *matcher, BfmeAETF *item, int mode)
{
	union
	{
		void (*raw)();
		char (BfmeMatcherETF::*member)(BfmeAETF *, int);
	} call;

	call.raw = j_0001da34;
	return (matcher->*call.member)(item, mode);
}

static __forceinline char bfmeTestETF(BfmeTesterETF *tester, BfmeRangeETF *first, BfmeRangeETF *second)
{
	union
	{
		void (*raw)();
		char (BfmeTesterETF::*member)(BfmeRangeETF *, BfmeRangeETF *);
	} call;

	call.raw = j_0003c2e5;
	return (tester->*call.member)(first, second);
}

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
		if (!bfmeMatchETF(&m_bfme08ETF, a, 0) ||
			!bfmeTestETF(&a->m_bfme110ETF, &m_bfme10ETF, &m_bfme38ETF))
			return 0;
	}

	if (b == 0 ||
		(bfmeMatchETF(&m_bfme0cETF, b, 0) &&
		bfmeTestETF(&b->m_bfme110ETF, &m_bfme60ETF, &m_bfme88ETF)))
		return 1;

	return 0;
}
