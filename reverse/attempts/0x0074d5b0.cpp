// ?d_0074d5b0@@YAXXZ
// partial score=0.8 date=2026-09-02
// cl: /O2 /Oi

class BfmeShortVecWN
{
public:
	BfmeShortVecWN(unsigned n);
	void grow(unsigned n, void *a);

	wchar_t *m_start;
	wchar_t *m_finish;
};

BfmeShortVecWN::BfmeShortVecWN(unsigned n)
{
	grow(n, &n);
	wchar_t *p = m_start;
	if (n)
	{
		for (unsigned i = 0; i < n; ++i)
			p[i] = 0;
		m_finish = p + n;
	}
	else
		m_finish = p;
}
