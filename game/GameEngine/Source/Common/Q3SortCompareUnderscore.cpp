// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: comparator over four-byte AsciiString elements.  Retail
// 0x009CCAC0, 68 bytes.  Both operands whose first character is '_' compare
// greater-than; otherwise the compare is less-than.  compareNoCase is the
// StringBase<char> ILT at 0x00027471.

template <class T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &that) const;

	T *m_data;
};

struct Q3SortElem4
{
	StringBase<char> m_base;
};

struct Q3SortCompare
{
	void *m_state;

	bool operator()(const Q3SortElem4 &left, const Q3SortElem4 &right) const;
};

bool Q3SortCompare::operator()(const Q3SortElem4 &left, const Q3SortElem4 &right) const
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
