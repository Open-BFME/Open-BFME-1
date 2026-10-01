// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: _STL::operator+(const basic_string<char> &, const char *),
// retail 0x005CAE30, 257 bytes. Canonical STLport 4.5.3 string-plus-const-char-pointer operator,
// explicit instantiation against the vendored headers. Identity per the matched caller
// ParticleSystemTemplate::writeINI at 0x005CCAB0 via ILT 0x0002F98C (callees.py), which passes
// a string object and a char pointer and consumes the returned string.
#include <string>
namespace _STL {
template basic_string<char, char_traits<char>, allocator<char> > operator+(const basic_string<char, char_traits<char>, allocator<char> > &, const char *);
}
