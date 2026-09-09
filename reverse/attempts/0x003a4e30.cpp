// ?bfmePopCB@BfmeHostCB@@QAEDXZ
// partial score=0.90 date=2026-09-09
extern const float BfmeZeroRange;
extern "C" const float _bfmeScaleCB;

struct BfmeUniBufCB
{
	unsigned char m_bfmeHeadCB[4];
	unsigned short m_bfmeChCB;
};

class UnicodeString
{
public:
	void set(const UnicodeString &o);

	BfmeUniBufCB *m_bfmeDataCB;
};

struct BfmeTagCB
{
};

struct BfmeElemCB
{
	BfmeElemCB(const BfmeElemCB &o);
	~BfmeElemCB();

	int m_bfme00CB;
	int m_bfme04CB;
	UnicodeString m_bfme08CB;
	UnicodeString m_bfme0CCB;
	float m_bfme10CB;
};

void bfmeShiftCB(BfmeElemCB *first, BfmeElemCB *last, BfmeElemCB *dst, BfmeTagCB *tag, int flag);

class BfmeHostCB
{
public:
	char bfmePopCB();
	void bfmeApplyCB(const UnicodeString &s);

	unsigned char m_bfmeHeadCB[0x14];
	int m_bfme14CB;
	int m_bfme18CB;
	unsigned char m_bfme1CCB;
	unsigned char m_bfmeGapCB[3];
	float m_bfme20CB;
	unsigned char m_bfmeGap2CB[4];
	BfmeElemCB *volatile m_bfme28CB;
	BfmeElemCB *m_bfme2CCB;
	unsigned char m_bfmeGap3CB[4];
	UnicodeString m_bfme34CB;
};

char BfmeHostCB::bfmePopCB()
{
	BfmeElemCB *begin = m_bfme28CB;

	if (m_bfme2CCB - begin != 0)
	{
		BfmeElemCB e(*m_bfme28CB);

		m_bfme18CB = e.m_bfme04CB;
		m_bfme14CB = e.m_bfme00CB;

		if (e.m_bfme08CB.m_bfmeDataCB != 0 && e.m_bfme08CB.m_bfmeDataCB->m_bfmeChCB != 0)
			m_bfme34CB.set(e.m_bfme08CB);

		if (e.m_bfme0CCB.m_bfmeDataCB != 0 && e.m_bfme0CCB.m_bfmeDataCB->m_bfmeChCB != 0)
			bfmeApplyCB(e.m_bfme0CCB);

		if (e.m_bfme10CB != BfmeZeroRange)
			m_bfme20CB = e.m_bfme10CB * _bfmeScaleCB;

		BfmeElemCB *first = m_bfme28CB;
		BfmeElemCB *last = m_bfme2CCB;

		if (first + 1 != last)
		{
			BfmeTagCB tag;

			bfmeShiftCB(first + 1, last, first, &tag, 0);
		}

		--m_bfme2CCB;

		m_bfme2CCB->~BfmeElemCB();

		m_bfme1CCB = 1;

		return 1;
	}

	return 0;
}
