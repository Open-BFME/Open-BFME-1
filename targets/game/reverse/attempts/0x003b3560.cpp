// ??$__copy@PBURva003B3560Elem32@@PAU1@H@_STL@@YAPAURva003B3560Elem32@@PBU1@0PAU1@ABUrandom_access_iterator_tag@0@PAH@Z
// partial score=0.08 date=2026-09-24
// ??$__copy@PBURva003B3560Elem32@@PAU1@H@_STL@@YAPAURva003B3560Elem32@@PBU1@0PAU1@ABUrandom_access_iterator_tag@0@PAH@Z
// Trial: forward __copy with in-place group and tail iterators.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

struct Rva003B3560Elem32
{
    int m_untouched;
    int m_a;
    int m_b;
    int m_c;
    int m_d;
    int m_e;
    int m_f;
    bool m_flag;
    unsigned char m_pad[3];

    Rva003B3560Elem32 &operator=(const Rva003B3560Elem32 &other)
    {
        m_a = other.m_a;
        m_b = other.m_b;
        m_c = other.m_c;
        m_d = other.m_d;
        m_e = other.m_e;
        m_f = other.m_f;
        m_flag = other.m_flag;
        return *this;
    }
};

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last,
    OutputIterator result, const random_access_iterator_tag &, Distance *)
{
    Distance count = last - first;
    if (count >= 4)
    {
        Distance groups = ((count - 4) >> 2) + 1;
        Distance done = groups;
        do
        {
            result[0] = first[0];
            result[1] = first[1];
            result[2] = first[2];
            result[3] = first[3];
            first += 4;
            result += 4;
        } while (--done);
        count -= groups << 2;
    }
    while (count-- > 0)
    {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

template Rva003B3560Elem32 *__copy<
    const Rva003B3560Elem32 *, Rva003B3560Elem32 *, int>(
    const Rva003B3560Elem32 *, const Rva003B3560Elem32 *,
    Rva003B3560Elem32 *, const random_access_iterator_tag &, int *);
}
