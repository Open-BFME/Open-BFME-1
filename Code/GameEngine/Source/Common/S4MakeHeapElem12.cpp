// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __make_heap over a twelve-byte element, retail
// 0x00531C50, 118 bytes.  The zero-tail forwarder at 0x00531BE0-adjacent
// calls this as gen00531C50(first, last, comp, 0, 0).  The 0x2AAAAAAB
// multiply is (last-first)/12; the loop is STLport's parent = (len-2)/2
// countdown through __adjust_heap.

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

	friend struct S4SortElem12;
};

struct S4SortElem12
{
	char m_bfmeC;
	StringBase<char> m_bfmeName;
	int m_bfmeA;

	S4SortElem12(const S4SortElem12 &other) :
		m_bfmeC(other.m_bfmeC),
		m_bfmeName(other.m_bfmeName),
		m_bfmeA(other.m_bfmeA)
	{
	}
	~S4SortElem12(void) {}
	S4SortElem12 &operator=(const S4SortElem12 &other)
	{
		m_bfmeC = other.m_bfmeC;
		m_bfmeName = other.m_bfmeName;
		m_bfmeA = other.m_bfmeA;
		return *this;
	}
};

void bfmeAdjustHeap00531C50(S4SortElem12 *first, int holeIndex, int len,
	S4SortElem12 value, void *comp);

void gen00531C50(void *a, void *b, void *c, int, int)
{
	S4SortElem12 *first = (S4SortElem12 *)a;
	S4SortElem12 *last = (S4SortElem12 *)b;
	int len = last - first;
	if (len < 2)
		return;
	int parent = (len - 2) / 2;
	for (;;)
	{
		bfmeAdjustHeap00531C50(first, parent, len, *(first + parent), c);
		if (parent == 0)
			return;
		--parent;
	}
}
