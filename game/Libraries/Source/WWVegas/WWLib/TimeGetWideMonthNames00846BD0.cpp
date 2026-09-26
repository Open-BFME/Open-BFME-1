// cl: /O2 /Ob0 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <locale>

// Match one of the twenty-four abbreviated or full month names against a wide input stream.
typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
    BfmeWideTimeIterator;

bool bfmeRva00846BD0MatchWideMonthNames(
    BfmeWideTimeIterator &first, BfmeWideTimeIterator &last,
    const _STL::_Time_Info *table, tm *value)
{
    _STL::string *end;
    _STL::string *matched = _STL::__match(first, last,
        const_cast<_STL::string *>(table->_M_monthname),
        end = const_cast<_STL::string *>(table->_M_monthname) + 24,
        (long *)0);
    value->tm_mon = ((int)(matched - table->_M_monthname)) % 12;
    return matched != end;
}
