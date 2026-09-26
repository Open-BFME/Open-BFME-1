// cl: /DNDEBUG /MD /EHsc

class BfmeTagZBRefCounted
{
public:
	virtual void Delete_This(unsigned int);
	int m_refs;
};

class BfmeTagZB
{
public:
	BfmeTagZB() : m_bfmeTagZB(0) {}
	BfmeTagZB(const BfmeTagZB &other) throw()
		: m_bfmeTagZB(other.m_bfmeTagZB)
	{
		if (m_bfmeTagZB)
			++((BfmeTagZBRefCounted *)m_bfmeTagZB)->m_refs;
	}
	~BfmeTagZB()
	{
		BfmeTagZBRefCounted *p = (BfmeTagZBRefCounted *)m_bfmeTagZB;
		if (p && --p->m_refs <= 0)
			p->Delete_This(1);
	}
	BfmeTagZBRefCounted *m_bfmeTagZB;
};

extern void j_0004782a();

void __cdecl bfmeSendZB(void *first, void *second, void *third, BfmeTagZB tag)
{
	((void (__cdecl *)(void *, void *, void *, BfmeTagZB, BfmeTagZB))j_0004782a)(
		first, second, third, tag, BfmeTagZB());
}

void __cdecl bfmeMakeZB(void *first, void *second, void *third)
{
	bfmeSendZB(first, second, third, BfmeTagZB());
}
