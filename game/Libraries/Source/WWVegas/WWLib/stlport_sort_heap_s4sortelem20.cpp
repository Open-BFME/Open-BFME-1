// STLport 4.5.3 sort_heap loop for retail 0x002EB010. The forwarder's
// existing four-argument ABI is named directly below.
#include "ascii_string.h"


// Retail S4+0 is the AsciiString wrapper. Its four-byte StringBase subobject
// keeps the 20-byte record layout, while cleanup resolves the distinct QAE
// AsciiString destructor (RVA 0x005EE90 / ILT 0x0000D828), not the private
// StringBase<char> destructor.

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
