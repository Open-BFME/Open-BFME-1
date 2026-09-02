// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: STLport __pop_heap over a twelve-byte element, retail
// 0x00531A40, 169 bytes.  gen00531D80 calls this with (first, last-1, last-1,
// *(last-1), comp, 0).  *result = *first goes through StringBase<char>::set
// at 0x00887C90; the by-value element is then handed to __adjust_heap.

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct S4SortElem12
{
	char m_bfmeC;
	AsciiString m_bfmeName;
	int m_bfmeA;
};

void bfmeAdjustHeap00531C50(S4SortElem12 *first, int holeIndex, int len,
	S4SortElem12 value, void *comp);

void bfmePopHeap00531A40(S4SortElem12 *first, S4SortElem12 *last,
	S4SortElem12 *result, S4SortElem12 value, void *comp, int *)
{
	*result = *first;
	bfmeAdjustHeap00531C50(first, 0, last - first, value, comp);
}
