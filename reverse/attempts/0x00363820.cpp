// ?handle@Gen00363820@@QAEXPAX0@Z
// partial score=0.72 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Gen00363820Elem
{
public:
	virtual void destroy(int flags);

private:
	unsigned char m_data[0xB4];
};

Gen00363820Elem *bfmePartition(void *a, Gen00363820Elem *end, void *key, void *out, int zero);

class Gen00363820
{
public:
	void handle(void *key, void *scratch);

private:
	void *m_unused0;
	Gen00363820Elem *m_end;
};

void Gen00363820::handle(void *key, void *scratch)
{
	void *first = key;
	Gen00363820Elem *newEnd = bfmePartition(scratch, m_end, first, &first, 0);
	Gen00363820Elem *end = m_end;
	Gen00363820Elem *p = newEnd;
	if (p != end)
	{
		do
		{
			p->destroy(0);
			++p;
		} while (p != end);
	}
	m_end = newEnd;
}
