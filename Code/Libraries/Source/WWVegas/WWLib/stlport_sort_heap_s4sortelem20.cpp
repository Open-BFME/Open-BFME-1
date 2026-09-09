// STLport 4.5.3 sort_heap loop for retail 0x002EB010. The forwarder's
// existing four-argument ABI is named directly below.
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
struct S4Cmp002EB8E0 { int m_bfmeSlot; };
void gen002EADF0(void *first, void *last, int zero, void *extra);
namespace _STL
{
template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
    Compare comp);

template <>
void sort_heap<S4SortElem20 *, S4Cmp002EB8E0>(
    S4SortElem20 *first, S4SortElem20 *last, S4Cmp002EB8E0 comp)
{
    // Retail passes the comparator's opaque four-byte state as the forwarder's
    // fourth pointer-sized argument; this preserves that ABI without aliasing.
    void *extra = (void *)(unsigned int)comp.m_bfmeSlot;
    while (last - first > 1)
    {
        gen002EADF0((void *)first, (void *)last, 0, extra);
        --last;
    }
}
}
