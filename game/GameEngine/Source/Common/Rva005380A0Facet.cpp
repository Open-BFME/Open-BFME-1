// cl: /O2 /Ob0 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <istream>

class Rva005380A0
{};

template _STL::locale::id
_STL::num_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >::id;

void *rva005380a0(Rva005380A0 *obj)
{
	return reinterpret_cast<_STL::locale *>(obj)->_M_use_facet(_STL::num_get<char>::id);
}
