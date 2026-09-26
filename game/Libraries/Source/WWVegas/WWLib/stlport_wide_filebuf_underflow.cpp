// ?underflow@?$basic_filebuf@GV?$char_traits@G@_STL@@@_STL@@MAEGXZ
// STLport 4.5.3 basic_filebuf<wchar_t>::underflow.
// The RTTI table at VA 0x0112F350 names basic_filebuf<wchar_t>.
// Its slot 7 points to this ten-byte forwarder at RVA 0x00843620.
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <wchar.h>

namespace _STL
{
template <class CharT>
class char_traits
{
};

template <class CharT, class Traits>
class basic_filebuf
{
protected:
	typedef unsigned short int_type;

	virtual int_type underflow();
};

template <class CharT, class Traits>
class _Underflow
{
public:
	typedef unsigned short int_type;

	static int_type _M_doit(basic_filebuf<CharT, Traits> *file);
};

template <>
unsigned short basic_filebuf<wchar_t, char_traits<wchar_t> >::underflow()
{
	return _Underflow<wchar_t, char_traits<wchar_t> >::_M_doit(this);
}
}
