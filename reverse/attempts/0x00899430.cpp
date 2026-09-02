// ?bfmeSub1224@BfmeA1224@@QAEPAVBfmeE1224@@H@Z
// partial score=0.97 date=2026-09-02
class BfmeE1224;

class BfmeSub1224
{
public:
	BfmeE1224 *bfmeLen1224(int i);
};

class BfmeA1224
{
public:
	BfmeE1224 *bfmeSub1224(int i);

	char m_bfmePad00[8];
	BfmeSub1224 m_bfme08;
	char m_bfmePad0c[0x18 - 0x0c];
	BfmeE1224 **m_bfme18;
	int m_bfme1c;
};

BfmeE1224 *BfmeA1224::bfmeSub1224(int i)
{
	int count = m_bfme1c & 0xff;
	if (i < count)
		return m_bfme18[i];
	return m_bfme08.bfmeLen1224(i - count);
}
