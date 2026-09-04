// cl: /O2 /Oi

class BfmeShortVecWN
{
public:
	BfmeShortVecWN(unsigned n);
	void grow(unsigned n, void *a);

	unsigned short *m_start;
	unsigned short *m_finish;
};

template <class Output, class Size, class Value>
static inline Output bfmeFillN(Output first, Size count, const Value &value)
{
	for (; count > 0; --count, ++first)
		*first = value;
	return first;
}

template <class Forward, class Size, class Value>
static inline Forward bfmeUninitializedFillN(
	Forward first, Size count, const Value &value)
{
	return bfmeFillN(first, count, value);
}

BfmeShortVecWN::BfmeShortVecWN(unsigned n)
{
	unsigned count = n;
	grow(count, &n);
	unsigned short *p = m_start;
	if (count > 0)
		m_finish = bfmeUninitializedFillN(p, count, unsigned short());
	else
		m_finish = p;
}
