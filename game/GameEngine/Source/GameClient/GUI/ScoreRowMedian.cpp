// cl: /DNDEBUG /MD /EHsc
// stlport
// ?$__median@US4SortElem8@@@_STL@@YAABUS4SortElem8@@ABU1@00@Z

#include <algorithm>

struct S4SortElem8
{
    int m_bfmeFirst;
    int m_bfmeSecond;

    bool BfmeLess00574AA0(const S4SortElem8 &other) const;

    bool operator<(const S4SortElem8 &other) const
    {
        return BfmeLess00574AA0(other);
    }
};

namespace _STL
{

template const S4SortElem8 &_STL::__median<S4SortElem8>(
    const S4SortElem8 &, const S4SortElem8 &, const S4SortElem8 &);

}
