// cl: /DNDEBUG /MD /EHsc

extern "C" int memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

template <class T>
class StringBase
{
    friend class AsciiString;
private:
	struct Header
	{
		int m_bfmeRefCount;
		unsigned short m_bfmeLength;
		unsigned short m_bfmeCapacity;
		T m_bfmeData[1];
	};

	Header *m_bfmeHeader;

public:
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	void set(const StringBase<T> &other);
	friend struct S4SortElem20;
};


// Retail S4+0 is the AsciiString wrapper. Its four-byte StringBase subobject
// keeps the 20-byte record layout, while cleanup resolves the distinct QAE
// AsciiString destructor (RVA 0x005EE90 / ILT 0x0000D828), not the private
// StringBase<char> destructor.
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other)
        : StringBase<char>(other) {}
    ~AsciiString();
    void set(const AsciiString &other)
    {
        StringBase<char>::set(other);
    }
    AsciiString &operator=(const AsciiString &other)
    {
        set(other);
        return *this;
    }

};

struct BfmeSortTailElement12;

class BfmeSortElem20Tail
{
public:
	BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
	~BfmeSortElem20Tail();
	void set(const BfmeSortElem20Tail &other);

private:
	BfmeSortTailElement12 *m_begin;
	BfmeSortTailElement12 *m_end;
	BfmeSortTailElement12 *m_capacity;
};

struct S4SortElem20
{
	AsciiString m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;
};

namespace _STL
{

// ?__adjust_heap absent-from-retail
template <class RandomAccessIterator, class Distance, class Tp, class Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex,
	Distance len, Tp val, Compare comp);

}

namespace _STL
{

template <class RandomAccessIterator, class Tp, class Compare, class Distance>
void __pop_heap(RandomAccessIterator, RandomAccessIterator,
    RandomAccessIterator, Tp, Compare, Distance *);

template <>
void __pop_heap<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0, int>(
    S4SortElem20 *first, S4SortElem20 *last, S4SortElem20 *result,
    S4SortElem20 value, S4Cmp002EB8E0 comp, int *)
{
    S4SortElem20 *source = first;
    result->m_bfmeName = source->m_bfmeName;
    result->m_bfmeFlag = source->m_bfmeFlag;
    result->m_bfmeTail.set(source->m_bfmeTail);
    __adjust_heap(first, 0, (int)(((char *)last - (char *)first) / 20),
        value, comp);
}

}
