// Open-BFME5 conversions.

class BfmeE1224;

class BfmeSub1224
{
public:
	int bfmeLen1224();
	int m_bfme00;
};

class BfmeA1224
{
public:
	BfmeE1224 *bfmeAt1224(int i);
	BfmeE1224 *bfmeSub1224(int i);
	char m_bfmePad00[8];
	BfmeSub1224 m_bfme08;
	char m_bfmePad0c[0x1c - 0x0c];
	int m_bfme1c;
	BfmeE1224 *m_bfme20;
	int m_bfme24;
	BfmeE1224 *m_bfme28;
	BfmeE1224 *m_bfme2c;
};

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
