// cl: /DNDEBUG /MD /EHsc
// STLport 4.5.3 _algo.c lines 1049-1075, with the canonical S4 heap owners
// external. The 12-byte tail facade is a truthful three-pointer view.

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
    StringBase(const StringBase<T> &other);
    ~StringBase();

public:
    void set(const StringBase<T> &other);

    int compare(const StringBase<T> &other) const
    {
        const int length = other.m_bfmeHeader ? other.m_bfmeHeader->m_bfmeLength : 0;
        const char *data = other.m_bfmeHeader ? (const char *)&other.m_bfmeHeader->m_bfmeData[0] : "";
        const int myLength = m_bfmeHeader ? m_bfmeHeader->m_bfmeLength : 0;
        const char *myData = m_bfmeHeader ? (const char *)&m_bfmeHeader->m_bfmeData[0] : "";
        int result = memcmp(myData, data, myLength < length ? myLength : length);
        if (result == 0)
            result = myLength - length;
        return result;
    }

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
    int compare(const AsciiString &other) const
    {
        return StringBase<char>::compare(other);
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

	bool operator()(const S4SortElem20 &left,
		const S4SortElem20 &right) const
	{
		return left.m_bfmeName.compare(right.m_bfmeName) < 0;
	}
};

namespace _STL
{

template <class RandomAccessIterator, class Compare, class Tp, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last,
    Compare comp, Tp *, Distance *);

template <class RandomAccessIterator, class Tp, class Compare, class Distance>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
    RandomAccessIterator result, Tp value, Compare comp, Distance *);

template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
    Compare comp);

template <class RandomAccessIterator, class Tp, class Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle,
    RandomAccessIterator last, Tp *, Compare comp);

template <>
void __partial_sort<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0>(
    S4SortElem20 *first, S4SortElem20 *middle, S4SortElem20 *last,
    S4SortElem20 *, S4Cmp002EB8E0 comp)
{
    __make_heap(first, middle, comp, (S4SortElem20 *)0, (int *)0);
    for (S4SortElem20 *i = middle; i < last; ++i)
    {
        if (comp(*i, *first))
            __pop_heap(first, middle, i, S4SortElem20(*i), comp, (int *)0);
    }
    sort_heap(first, middle, comp);
}

}
