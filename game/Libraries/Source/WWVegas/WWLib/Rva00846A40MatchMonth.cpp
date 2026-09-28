// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <locale>

// Match one of the twenty-four abbreviated or full month names against a
// narrow input stream. Narrow twin of the landed wide month matcher at
// 0x00846BD0: __match over table->_M_monthname[0..24), index mod 12,
// stored at out[4] (the tm_mon slot of the caller's struct), returns
// whether a name matched. Opaque name: the table arithmetic is proved by
// the bytes, the do_get_* slot identity is not claimed.
typedef _STL::istreambuf_iterator<char, _STL::char_traits<char> >
    BfmeNarrowTimeIterator;

bool Rva00846A40MatchMonth(
    BfmeNarrowTimeIterator &first, BfmeNarrowTimeIterator &last,
    const _STL::_Time_Info *table, int *out)
{
    _STL::string *end;
    _STL::string *matched = _STL::__match(first, last,
        const_cast<_STL::string *>(table->_M_monthname),
        end = const_cast<_STL::string *>(table->_M_monthname) + 24,
        (long *)0);
    out[4] = ((int)(matched - table->_M_monthname)) % 12;
    return matched != end;
}
