// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME: STLport 4.5.3 __introsort_loop over the twenty-byte S4 record
// used by the adjacent insertion, heap, partial-sort, and partition family.
// The record has a 12-byte vector tail. AsciiString copies use the private
// StringBase constructor; cleanup calls the existing AsciiString destructor.

#include <algorithm>

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

// Bind the retail 0x002EB330 partial-sort
// owner instead of emitting another helper family in this TU.
template <>
void __partial_sort<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0>(
	S4SortElem20 *, S4SortElem20 *, S4SortElem20 *,
	S4SortElem20 *, S4Cmp002EB8E0);

template void __introsort_loop<S4SortElem20 *, S4SortElem20, int,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20 *, int,
	S4Cmp002EB8E0);

}
