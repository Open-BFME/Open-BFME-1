// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __pop_heap_aux over a twelve-byte element, retail
// 0x00531D80, 66 bytes.  The 26-byte zero-third forwarder at 0x00532210 calls
// this as gen00531D80(first, last, 0, comp).  The element copy goes through
// StringBase<char>'s copy constructor at 0x00887B60; the trailing typed-null
// is STLport's Distance tag on __pop_heap.

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

void bfmePopHeap00531A40(S4SortElem12 *first, S4SortElem12 *last,
	S4SortElem12 *result, S4SortElem12 value, void *comp, int *);

void gen00531D80(void *a, void *b, int n, void *c)
{
	bfmePopHeap00531A40((S4SortElem12 *)a,
		(S4SortElem12 *)b - 1,
		(S4SortElem12 *)b - 1,
		*((S4SortElem12 *)b - 1),
		c,
		(int *)0);
}
