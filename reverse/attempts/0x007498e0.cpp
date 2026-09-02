// ?d_007498e0@@YAXXZ
// partial score=0.82 date=2026-09-02
// cl: /O2

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
	BfmeBitMapWP *self = this;
	if (x < 0)
		return;
	if (y < 0)
		return;
	if (y >= self->m_h)
		return;
	if (x >= self->m_w)
		return;
	int idx = self->m_stride * y + (x >> 3);
	if (idx >= self->m_end - self->m_start)
		return;
	unsigned char *p = self->m_start + idx;
	unsigned char bit = (unsigned char)(1 << (x & 7));
	if (on)
		*p = (unsigned char)(*p | bit);
	else
		*p = (unsigned char)(*p & (unsigned char)~bit);
}
