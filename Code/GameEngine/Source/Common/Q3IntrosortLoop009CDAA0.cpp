// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport __introsort_loop over a four-byte AsciiString element.
// Retail 0x009CDAA0, 152 bytes.  The matched sort driver at 0x009CDB40
// (Rva009CDB40) calls this with a null type tag and depth = 2*lg(n).

template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend struct Q3SortElem4;
};

struct Q3SortElem4
{
	Q3SortElem4(const Q3SortElem4 &other) : m_base(other.m_base) {}
	~Q3SortElem4(void) {}

	StringBase<char> m_base;
};

struct Q3SortCompare
{
	void *m_state;
};

Q3SortElem4 *Gen009CCB60(Q3SortElem4 *first, Q3SortElem4 *mid,
	Q3SortElem4 *last, Q3SortCompare comp);
Q3SortElem4 *Gen009CCC50(Q3SortElem4 *first, Q3SortElem4 *last,
	Q3SortElem4 pivot, Q3SortCompare comp);
void Gen009CD980(Q3SortElem4 *first, Q3SortElem4 *middle, Q3SortElem4 *last,
	Q3SortElem4 *, Q3SortCompare comp);

void Gen009CDAA0(Q3SortElem4 *first, Q3SortElem4 *last, Q3SortElem4 *,
	int depth, Q3SortCompare comp)
{
	while (last - first > 16)
	{
		if (depth == 0)
		{
			Gen009CD980(first, last, last, (Q3SortElem4 *)0, comp);
			return;
		}
		--depth;
		Q3SortElem4 *cut = Gen009CCC50(first, last,
			*Gen009CCB60(first, first + (last - first) / 2, last - 1, comp),
			comp);
		Gen009CDAA0(cut, last, (Q3SortElem4 *)0, depth, comp);
		last = cut;
	}
}
