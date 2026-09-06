// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport __median for Q3SortElem4 at retail 0x009CCB60.
// Q3IntrosortLoop009CDAA0.cpp names this body as the median callee, and the
// comparator implementation at 0x009CCAC0 supplies the five comparison sites.

template <class T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &that) const;

	T *m_data;

	friend struct Q3SortElem4;
};

struct Q3SortElem4
{
	StringBase<char> m_base;
};

struct Q3SortCompare
{
	void *m_state;

	bool operator()(const Q3SortElem4 &left,
		const Q3SortElem4 &right) const;
};

bool Q3SortCompare::operator()(const Q3SortElem4 &left,
	const Q3SortElem4 &right) const
{
	char *a = left.m_base.m_data;
	const Q3SortElem4 *r = &right;
	if (a)
	{
		if (a[8] == '_')
		{
			char *b = r->m_base.m_data;
			if (b)
			{
				if (b[8] == '_')
					return left.m_base.compareNoCase(r->m_base) > 0;
			}
		}
	}
	return left.m_base.compareNoCase(r->m_base) < 0;
}

Q3SortElem4 *Gen009CCB60(Q3SortElem4 *first, Q3SortElem4 *middle,
	Q3SortElem4 *last, Q3SortCompare comp)
{
	if (comp(*first, *middle))
		if (comp(*middle, *last))
			return middle;
		else if (comp(*first, *last))
			return last;
		else
			return first;
	else if (comp(*first, *last))
		return first;
	else if (comp(*middle, *last))
		return last;
	else
		return middle;
}
