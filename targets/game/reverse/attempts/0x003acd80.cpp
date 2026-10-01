// ?Rva003ACD80@@YAPAURva003ACD80Record@@PAU1@00ABUrandom_access_iterator_tag@_STL@@PAH@Z
// partial score=0.0 date=2026-10-01
// stlport
#include <algorithm>

struct Rva003ACD80Point
{
    float m_at00, m_at04, m_at08;
};

struct Rva003ACD80Record
{
    virtual void slot00();
    int m_at04;
    Rva003ACD80Point m_at08;
    int m_at14;
    int m_at18;
    bool m_at1c;
};

Rva003ACD80Record *Rva003ACD80(Rva003ACD80Record *first,
    Rva003ACD80Record *last, Rva003ACD80Record *result,
    const _STL::random_access_iterator_tag &, int *)
{
    int n = last - first;
    if (n >= 4)
    {
        int groups = ((n - 4) >> 2) + 1;
        int left = groups;
        do
        {
            result[0] = first[0];
            result[1] = first[1];
            result[2] = first[2];
            result[3] = first[3];
            first += 4;
            result += 4;
        } while (--left);
        n -= groups << 2;
    }
    while (n-- > 0)
    {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}
