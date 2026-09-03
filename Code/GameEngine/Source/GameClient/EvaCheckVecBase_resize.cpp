// cl: /O2

// EvaCheckVecBase::resize, retail 0x00425E40. Two-argument form the one-arg
// wrapper at 0x00426100 forwards to. Fill value is 24 bytes by value; shrink
// inlines __copy and reuses the count slot as the unused iterator-tag address.

struct EvaCheck
{
	char m_b[24];
};

struct EvaCheckCopyTag
{
};

EvaCheck *evaCheckCopy(EvaCheck *first, EvaCheck *last, EvaCheck *result,
	const EvaCheckCopyTag &, int *);

class EvaCheckVecBase
{
public:
	EvaCheck *begin() { return m_start; }
	EvaCheck *end() { return m_finish; }
	unsigned size() const { return (unsigned)(m_finish - m_start); }

	void resize(int n, EvaCheck value);
	void fillInsert(EvaCheck *pos, unsigned n, const EvaCheck &value);

	EvaCheck *m_start;
	EvaCheck *m_finish;
	EvaCheck *m_end;
};

void EvaCheckVecBase::resize(int n, EvaCheck value)
{
	if ((unsigned)n < size())
	{
		EvaCheck *dest = m_start + n;
		m_finish = evaCheckCopy(end(), end(), dest,
			*reinterpret_cast<EvaCheckCopyTag *>(&n), (int *)0);
	}
	else
		fillInsert(end(), (unsigned)n - size(), value);
}
