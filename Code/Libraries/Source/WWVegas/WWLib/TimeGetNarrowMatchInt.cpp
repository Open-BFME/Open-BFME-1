// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3 narrow time_get name matcher, second copy at 0x00836980 (the int difference-type
// instantiation): byte-twin of TimeGetNarrowMatch.cpp (tools/twin_scan.py), no relocations differ.

namespace _STL
{

template <class CharT>
class char_traits
{
};

template <class CharT>
class allocator
{
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
    typedef unsigned int size_type;

    CharT *_M_start;
    CharT *_M_finish;
    CharT *_M_end_of_storage;

    size_type size() const { return (size_type)(_M_finish - _M_start); }

    CharT &operator[](size_type index) const { return _M_start[index]; }
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
    int sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
    typedef CharT char_type;

    void _M_getc() const;

    char_type operator*() const
    {
        _M_getc();
        return _M_c;
    }

    istreambuf_iterator &operator++()
    {
        _M_buf->sbumpc();
        _M_have_c = 0;
        return *this;
    }

    bool equal(const istreambuf_iterator &other) const
    {
        if (_M_buf)
            _M_getc();
        if (other._M_buf)
            other._M_getc();
        return _M_eof == other._M_eof;
    }

    basic_streambuf<CharT, Traits> *_M_buf;
    mutable CharT _M_c;
    mutable unsigned char _M_eof;
    mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
inline bool operator!=(
    const istreambuf_iterator<CharT, Traits> &left,
    const istreambuf_iterator<CharT, Traits> &right)
{
    return !left.equal(right);
}

template <class Type>
inline const Type &max(const Type &left, const Type &right)
{
    return left < right ? right : left;
}

template <class InputIter, class RandomAccessIter, class DifferenceType>
RandomAccessIter __match(
    InputIter &first, InputIter &last,
    RandomAccessIter name, RandomAccessIter name_end, DifferenceType *)
{
    typedef DifferenceType difference_type;
    difference_type count = name_end - name;
    unsigned int max_position = 0;
    difference_type index;
    difference_type position = 0;
    difference_type check_count = count;
    bool do_check[64];
    RandomAccessIter matching_name[64];

    for (index = 0; index < count; ++index)
        max_position = (max)(max_position, name[index].size());

    for (index = 0; index < 64; ++index)
        do_check[index] = true;

    for (index = 0; index < 64; ++index)
        matching_name[index] = name_end;

    while (first != last)
    {
        for (index = 0; index < count; ++index)
        {
            if (do_check[index])
            {
                if (*first == name[index][position])
                {
                    if (position == difference_type(name[index].size()) - 1)
                    {
                        do_check[index] = 0;
                        matching_name[position + 1] = name + index;
                        --check_count;
                        if (check_count == 0)
                        {
                            ++first;
                            return name + index;
                        }
                    }
                }
                else
                {
                    do_check[index] = 0;
                    --check_count;
                    if (check_count == 0)
                        return matching_name[position];
                }
            }
        }

        ++first;
        ++position;
    }

    return matching_name[position];
}

template basic_string<char, char_traits<char>, allocator<char> > *
__match(
    istreambuf_iterator<char, char_traits<char> > &,
    istreambuf_iterator<char, char_traits<char> > &,
    basic_string<char, char_traits<char>, allocator<char> > *,
    basic_string<char, char_traits<char>, allocator<char> > *,
    int *);

} // namespace _STL
