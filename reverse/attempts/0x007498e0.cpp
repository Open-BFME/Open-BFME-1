// ?setBit@BfmeBitMapWP@@QAEXHHE@Z
// partial score=0.85 date=2026-09-02
// cl: /O2
// ?setBit@BfmeBitMapWP@@QAEXHHE@Z

class BfmeBitMapWP
{
public:
	void setBit(int x, int y, unsigned char on);

private:
	int m_pad00;
	int m_pad04;
	int m_w;
	int m_h;
	int m_pad10[9];
	int m_stride;
	int m_pad38[6];
	unsigned char *m_start;
	unsigned char *m_end;
};

void BfmeBitMapWP::setBit(int x, int y, unsigned char on)
{
	if (x < 0 || y < 0)
		return;
	if (y >= m_h)
		return;
	if (x >= m_w)
		return;
	unsigned char *p = &m_start[m_stride * y + (x >> 3)];
	if ((unsigned)(p - m_start) >= (unsigned)(m_end - m_start))
		return;
	if (on)
		*p |= (unsigned char)(1 << (x & 7));
	else
		*p &= (unsigned char)~(1 << (x & 7));
}
