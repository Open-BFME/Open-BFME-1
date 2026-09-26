extern "C" void _ReadWriteBarrier(void);
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <iterator>

struct Rva00450B90Item
{
    char m_beforeFlags[0x24];
    bool m_flag24;
    bool m_flag25;
    bool m_flag26;
};
class Rva00450B90Predicate
{
public:
    bool operator()(const Rva00450B90Item *item) const
    {
        if ((m_mask & 0x01) != 0 && item->m_flag26)
            goto selected26;
        if ((m_mask & 0x02) == 0 || item->m_flag26)
            return false;

    selected26:
        if ((item->m_flag24 && (m_mask & 0x04) != 0)
                || (!item->m_flag24 && (m_mask & 0x08) != 0))
            return false;

        return !((item->m_flag25 && (m_mask & 0x10) != 0)
                || (!item->m_flag25 && (m_mask & 0x20) != 0));
    }

    unsigned int m_mask;
};
struct Rva00452120Range
{
    Rva00450B90Item **first;
    Rva00450B90Item **last;
};
namespace _STL
{
template<class Iterator, class Predicate>
Iterator __partition(Iterator first, Iterator last, Predicate predicate,
                     const bidirectional_iterator_tag &category);
}
// The first argument is the four-byte predicate value used by the matched
// __partition instantiation; the second points to a two-iterator range.
Rva00450B90Item **rva00452120Partition(Rva00450B90Predicate predicate,
                                       const Rva00452120Range *range)
{
    Rva00450B90Item **last = range->last;
    Rva00450B90Item **first = range->first;
    _ReadWriteBarrier();
    _STL::bidirectional_iterator_tag category;
    return _STL::__partition(first, last, predicate, category);
}
