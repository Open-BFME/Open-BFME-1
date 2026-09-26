// Open-BFME5 conversions.

struct BfmeCellVKF
{
	int m_bfmeArr[9];
};

class BfmeMapVKF
{
public:
	void bfmeGetVKF(int x, int y, BfmeCellVKF *out);
	char m_bfmePad00[8];
	int m_bfme08;
	char m_bfmePad0c[0x14];
	int m_bfme20;
	char m_bfmePad24[0x70];
	int *m_bfme94;
	char m_bfmePad98[0x8018];
	BfmeCellVKF *m_bfme80b0;
	char m_bfmePad80b4[0xa02c];
	int m_bfme120e0;
	int m_bfme120e4;
};

void BfmeMapVKF::bfmeGetVKF(int x, int y, BfmeCellVKF *out)
{
	int i = (m_bfme120e4 + y) * m_bfme08 + m_bfme120e0 + x;
	if (i >= 0 && i < m_bfme20)
	{
		int idx = m_bfme94[i];
		*out = m_bfme80b0[idx];
	}
}
