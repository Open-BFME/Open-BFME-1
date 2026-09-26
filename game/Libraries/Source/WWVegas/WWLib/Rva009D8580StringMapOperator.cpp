// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Address-derived STLport operator[] for the table embedded at +0x18 in the
// object constructed at retail 0x009D8630.  The retail same-object caller at
// 0x009D86E0 passes a temporary basic_string and uses the returned int slot;
// retail's insert callee at 0x009D8350 constructs pair<const basic_string,
// int>.  No public owner name is inferred from the generated dump.

#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <hash_map>
#include <string>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva009D8580String;
typedef _STL::pair<const Rva009D8580String, int> Rva009D8580Value;
typedef _STL::hash_map<Rva009D8580String, int, _STL::hash<Rva009D8580String>,
	_STL::equal_to<Rva009D8580String>, _STL::allocator<Rva009D8580Value> >
	Rva009D8580Map;

// retail RVA 0x009D8580; caller evidence and the pair constructor fix the
// key/value types while the owner remains address-derived pending a public
// class/registration proof.
template int &Rva009D8580Map::operator[]( const Rva009D8580String &key );
