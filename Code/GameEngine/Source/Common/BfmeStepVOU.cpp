// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: STLport __pop_heap_aux over a four-byte AsciiString element.
// Retail 0x009CD630, 45 bytes.  The matched sort_heap wrapper at 0x009CD910
// (bfmeSortVOU) calls this with a literal-zero type tag; the element copy
// goes through StringBase<char>'s copy constructor at 0x00887B60, and the
// assignment *result = *first lives in the out-of-line __pop_heap.

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend struct BfmeElemVOU;
};

struct BfmeElemVOU
{
	BfmeElemVOU(const BfmeElemVOU &other) : m_base(other.m_base) {}
	~BfmeElemVOU(void) {}
	BfmeElemVOU &operator=(const BfmeElemVOU &other)
	{
		m_base = other.m_base;
		return *this;
	}

	StringBase<char> m_base;
};

void bfmeAdjustHeapVOU(BfmeElemVOU *first, int holeIndex, int len,
	BfmeElemVOU value, void *comp);

void bfmePopHeapVOU(BfmeElemVOU *first, BfmeElemVOU *last, BfmeElemVOU *result,
	BfmeElemVOU value, void *comp, int *)
{
	*result = *first;
	bfmeAdjustHeapVOU(first, 0, last - first, value, comp);
}

void bfmeStepVOU(void *a, void *b, int n, void *c)
{
	bfmePopHeapVOU((BfmeElemVOU *)a,
		(BfmeElemVOU *)b - 1,
		(BfmeElemVOU *)b - 1,
		*((BfmeElemVOU *)b - 1),
		c,
		(int *)0);
}

void bfmeMakeHeapVOU(BfmeElemVOU *first, BfmeElemVOU *last, void *comp)
{
	int len = last - first;
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	for (;;)
	{
		bfmeAdjustHeapVOU(first, parent, len, *(first + parent), comp);
		if (parent == 0)
			return;
		--parent;
	}
}
