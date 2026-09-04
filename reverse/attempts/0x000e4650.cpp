// ?fixup@BfmeVec12@@QAEXXZ
// partial score=0.99 date=2026-09-04
// ?fixup@BfmeVec12@@QAEXXZ
// partial score=0.99 date=2026-09-02
// cl: /O2

struct BfmeSub12
{
	void construct();
	unsigned char m_bytes[4];
};

struct BfmeElem12
{
	void *m_ptr;
	unsigned char m_mid[4];
	BfmeSub12 m_sub;
};

class BfmeAlloc12
{
public:
	void *make(BfmeSub12 *sub);
};

extern BfmeAlloc12 *TheBfmeAlloc12;

class BfmeVec12
{
public:
	void fixup();

	BfmeElem12 *m_begin;
	BfmeElem12 *m_end;
};

void BfmeVec12::fixup()
{
	BfmeElem12 *begin = m_begin;
	BfmeElem12 *last = m_end;
	unsigned int n = last - begin;
	unsigned int i = 0;
	if (n == 0)
		return;
	unsigned int off = 0;
	do
	{
		BfmeElem12 *e = (BfmeElem12 *)(off + (unsigned int)begin);
		e->m_ptr = TheBfmeAlloc12->make(&e->m_sub);
		((BfmeElem12 *)(off + (unsigned int)m_begin))->m_sub.construct();
		begin = m_begin;
		last = m_end;
		n = last - begin;
		++i;
		off += 12;
	} while (i < n);
}
