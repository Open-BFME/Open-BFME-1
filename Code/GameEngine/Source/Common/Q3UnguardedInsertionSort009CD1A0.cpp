// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport __unguarded_insertion_sort_aux over a four-byte
// AsciiString element.  Retail 0x009CD1A0, 53 bytes.  The matched
// final-insertion wrapper at 0x009CD6F0 (Rva009CD6F0) calls this with a
// null type tag; the element copy is StringBase<char>'s copy constructor.

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

void Gen009CCE50(Q3SortElem4 *last, Q3SortElem4 val, Q3SortCompare comp);

void Gen009CD1A0(Q3SortElem4 *first, Q3SortElem4 *last, Q3SortElem4 *,
	Q3SortCompare comp)
{
	for (Q3SortElem4 *i = first; i != last; ++i)
		Gen009CCE50(i, *i, comp);
}
