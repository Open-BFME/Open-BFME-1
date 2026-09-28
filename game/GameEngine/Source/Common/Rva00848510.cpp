// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <iterator>
#include <algorithm>
// INT3 precedes 00848510; complete RET at 00848580 precedes INT3.
// The native iterator witnesses streambuf at +0 and success byte at +4;
// fill_n keeps writing the same referenced character until count is exhausted.
_STL::ostreambuf_iterator<char> Rva00848510(
    _STL::ostreambuf_iterator<char> output, unsigned count, const char &value)
{
    for (; count > 0; --count, ++output)
        *output = value;
    return output;
}

