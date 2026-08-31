// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The mapped value's default/copy constructors and cleanup resolve to
// STLport basic_string<char>; the neighboring tree insertion body fixes the
// key as unsigned int.  Explicit instantiation reproduces retail's operator[].

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>
#include <string>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	UIntMapString;
typedef _STL::map<unsigned int, UIntMapString> UIntStringMap;

template UIntMapString &UIntStringMap::operator[](const unsigned int &key);
