// cl: /O2 /Ob0 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <ostream>

class Rva005C0FD0
{};

template _STL::locale::id
_STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >::id;

void *rva005c0fd0(Rva005C0FD0 *obj)
{
	return reinterpret_cast<_STL::locale *>(obj)->_M_use_facet(_STL::num_put<char>::id);
}
