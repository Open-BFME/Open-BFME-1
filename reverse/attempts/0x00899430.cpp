// ?bfmeSub1224@BfmeA1224@@QAEPAVBfmeE1224@@H@Z
// partial score=0.88 date=2026-08-30
// Open-BFME5 conversions.

class BfmeE1224;

class BfmeSub1224
{
public:
	int bfmeLen1224();
	BfmeE1224 *bfmeLen1224(int i);
	int m_bfme00;
};

class BfmeA1224
{
public:
	BfmeE1224 *bfmeAt1224(int i);
	BfmeE1224 *bfmeSub1224(int i);
	char m_bfmePad00[8];
	BfmeSub1224 m_bfme08;
	char m_bfmePad0c[0x18 - 0x0c];
	BfmeE1224 **m_bfme18;
	volatile int m_bfme1c;
	BfmeE1224 *m_bfme20;
	int m_bfme24;
	BfmeE1224 *m_bfme28;
	BfmeE1224 *m_bfme2c;
};

BfmeE1224 *BfmeA1224::bfmeSub1224(int i)
{
	int index = i;
	int count;
	if (index < (count = m_bfme1c & 0xff))
		return m_bfme18[index];
	index -= count;
	return m_bfme08.bfmeLen1224(index);
}

BfmeE1224 *BfmeA1224::bfmeAt1224(int i)
{
	int n;

	if (i == 0)
		return m_bfme20;
	if (i == 1)
		return m_bfme28;
	if (i == 2)
		return m_bfme2c;
	n = m_bfme08.bfmeLen1224() + (m_bfme1c & 0xff) + 3;
	if (i >= 3 && i < n)
		return bfmeSub1224(i - 3);
	return 0;
}
