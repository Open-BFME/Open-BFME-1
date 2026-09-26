// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Natural STLport basic_string<char>::append(const basic_string&) at
// RVA 0x005C9CA0, 26 bytes. QRServerKeyCallback's string append at
// 0x0064DC36 calls ILT 0x00017300, which routes to this body. Its call
// through 0x00011522 names append(first,last,forward_iterator_tag) at
// 0x000A4030. The old generated +=-shaped placeholder carried no identity.
#include <string>
template std::string& std::string::append(const std::string&);
