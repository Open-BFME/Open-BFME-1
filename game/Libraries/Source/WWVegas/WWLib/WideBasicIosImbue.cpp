// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.5.3 emits the retail wide basic_ios::imbue body when this TU
// exposes the node allocator implementation before instantiating the method.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_STATIC_MUTEX NodeAllocMutex
#define _STLP_MUTEX_INITIALIZER
#define _STLP_EXPOSE_GLOBALS_IMPLEMENTATION 1

namespace _STL
{

class NodeAllocMutex
{
public:
	void _M_acquire_lock(void);
	void _M_release_lock(void);
};

}

#include <istream>

template _STL::locale _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> >::imbue(
	const _STL::locale&);
