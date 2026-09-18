// cl: /DNDEBUG /DWIN32 /MD /Od /Ob1 /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// STLport stdexcept supplies the authentic 256-byte name buffer and native
// exception base. Its inline implementation witnesses this constructor/what
// pair; stl/_string_fwd.c independently witnesses __get_c_string via c_str().
// Retail 82C180 installs the RTTI-proven root table D2E8B8, calls the native
// exception import and 82C160, copies 256 bytes at this+12, then zeros this+267.
// All ten stdexcept vtables use 82AE20 in slot 1. /Od /Ob1 preserves the retail
// 19-byte helper while naturally inlining c_str(); no raw-layout surrogate.
#include <string>
#include <stdexcept>
namespace _STL {
// 0x0082C160 (19 bytes).
const char* _STLP_CALL __get_c_string(const string& text)
{
    return text.c_str();
}
// 0x0082C180 (123 bytes).
__Named_exception::__Named_exception(const string& text)
{
    strncpy(_M_name, __get_c_string(text), _S_bufsize);
    _M_name[_S_bufsize - 1] = '\0';
}
// 0x0082AE20 (17 bytes).
const char* __Named_exception::what() const _STLP_NOTHROW_INHERENTLY
{
    return _M_name;
}
}
