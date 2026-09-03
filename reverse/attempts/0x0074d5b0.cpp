// ??0BfmeShortVecWN@@QAE@I@Z
// partial score=0.92 date=2026-09-02
// cl: /O2 /Oi
// ??0BfmeShortVecWN@@QAE@I@Z

class BfmeShortVecWN
{
public:
	BfmeShortVecWN(unsigned n);
	void grow(unsigned n, void *a);

	unsigned short *m_start;
	unsigned short *m_finish;
};

BfmeShortVecWN::BfmeShortVecWN(unsigned n)
{
	unsigned count = n;
	grow(count, &n);
	unsigned short *p = m_start;
	if (count > 0)
	{
		unsigned short *q = p;
		unsigned c = count;
		for (; c > 0; --c, ++q)
			*q = 0;
		m_finish = p + count;
	}
	else
		m_finish = p;
}
