// Retail 0x002EADF0 forwards to the S4 pop specialization. The 12-byte
// tail facade and StringBase access match the existing canonical owners.
// cl: /O2 /Ob0 /DNDEBUG /MD /EHsc

struct BfmeSortTailElement12;

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
    friend struct S4SortElem20;
};

// Retail S4+0 is the AsciiString wrapper; its destructor is the existing
// public-QAE AsciiString dtor at RVA 0x005EE90 (ILT 0x0000D828), distinct
// from the private StringBase<char> dtor at RVA 0x005E490.
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

template <class RandomAccessIterator, class Tp, class Compare, class Distance>
void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
    RandomAccessIterator result, Tp value, Compare comp, Distance *distance);

}

// 0x002EADF0 is a separate 47-byte forwarding body. Its fourth argument
// carries the comparator value in a pointer-sized slot; preserve that raw ABI
// while naming the actual 0x002EABF0 callee as the S4 pop specialization.
void gen002EADF0(void *a, void *b, int, void *c)
{
    _STL::__pop_heap<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0, int>(
        (S4SortElem20 *)a, (S4SortElem20 *)b - 1,
        (S4SortElem20 *)b - 1, *((S4SortElem20 *)b - 1),
        *(S4Cmp002EB8E0 *)&c, (int *)0);
}
