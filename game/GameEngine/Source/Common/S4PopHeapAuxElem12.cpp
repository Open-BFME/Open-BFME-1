// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __pop_heap_aux over a twelve-byte element, retail
// 0x00531D80, 66 bytes.  The 26-byte zero-third forwarder at 0x00532210 calls
// this as gen00531D80(first, last, 0, comp).  The element copy goes through
// StringBase<char>'s copy constructor at 0x00887B60; the trailing typed-null
// is STLport's Distance tag on __pop_heap.

struct S4Name;

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
	void releaseBuffer(void);
	T *m_data;

	friend struct S4Name;
	friend struct S4SortElem12_00532740;
};

// Same S4Name view as the WWLib S4Cmp00532740 sort layers (89d88dcd24), so
// the inline S4SortElem12_00532740 special members are one COMDAT body.
struct S4Name
{
	S4Name(const S4Name &other) : m_base(other.m_base) {}
	~S4Name(void) { m_base.releaseBuffer(); }

	StringBase<char> m_base;
};

struct S4SortElem12_00532740
{
	bool m_bfmeA;
	S4Name m_bfmeName;
	int m_bfmeC;
};

void bfmePopHeap00531A40(S4SortElem12_00532740 *first, S4SortElem12_00532740 *last,
	S4SortElem12_00532740 *result, S4SortElem12_00532740 value, void *comp, int *);

void gen00531D80(void *a, void *b, int n, void *c)
{
	bfmePopHeap00531A40((S4SortElem12_00532740 *)a,
		(S4SortElem12_00532740 *)b - 1,
		(S4SortElem12_00532740 *)b - 1,
		*((S4SortElem12_00532740 *)b - 1),
		c,
		(int *)0);
}
