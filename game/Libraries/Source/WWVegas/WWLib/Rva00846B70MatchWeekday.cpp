// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <locale>

// Match one of the fourteen abbreviated or full weekday names against a
// wide input stream. Wide twin of the landed narrow weekday helpers:
// __match over table->_M_dayname[0..14), index mod 7, returns whether a
// name matched. Opaque name: the table arithmetic is proved by the bytes,
// the do_get_* slot identity is not claimed.
typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
    BfmeWideTimeIterator;

bool Rva00846B70MatchWeekday(
    BfmeWideTimeIterator &first, BfmeWideTimeIterator &last,
    const _STL::_Time_Info *table, tm *value)
{
    _STL::string *end;
    _STL::string *matched = _STL::__match(first, last,
        const_cast<_STL::string *>(table->_M_dayname),
        end = const_cast<_STL::string *>(table->_M_dayname) + 14,
        (int *)0);
    value->tm_wday = (int)(matched - table->_M_dayname) % 7;
    return matched != end;
}
