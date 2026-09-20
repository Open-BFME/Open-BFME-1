// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 wide __put_integer specialization, retail 0x00835AF0.

#include "stlport_prefix.h"

#define _STLP_EXPOSE_STREAM_IMPLEMENTATION
#include <stl/_num_put.h>

_STLP_BEGIN_NAMESPACE

class _Locale_impl
{
public:
	virtual void slot0(void) = 0;
	virtual void increment(void) = 0;
	virtual void decrement(void) = 0;
};

inline locale::~locale()
{
	_M_impl->decrement();
}

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> >
	BfmeWidePutIntegerIterator;

// ??$__put_integer@V?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@YA?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@0@PAD0V10@AAVios_base@0@HG@Z
template BfmeWidePutIntegerIterator _STLP_CALL
__put_integer<BfmeWidePutIntegerIterator>(
	char *, char *, BfmeWidePutIntegerIterator, ios_base &,
	ios_base::fmtflags, wchar_t);

_STLP_END_NAMESPACE
