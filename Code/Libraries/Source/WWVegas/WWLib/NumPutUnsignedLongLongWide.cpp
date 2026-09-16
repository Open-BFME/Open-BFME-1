// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide ostreambuf_iterator num_put::do_put(unsigned long long).
// The retail body is slot 2 of the vtable at VA 0x0112EA2C, whose RTTI
// complete object locator names the wide num_put, and it calls the
// __write_integer_backward instantiation at 0x00835140 whose value type is
// unsigned __int64.  It formats into a local 64-byte buffer and then applies
// grouping, field width and fill.

#include "stlport_prefix.h"

#undef _STLP_EXPOSE_STREAM_IMPLEMENTATION
#include <stl/_num_put.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

template <class Integer>
char *_STLP_CALL __write_integer_backward(char *, ios_base::fmtflags, Integer);

template <class OutputIter>
OutputIter _STLP_CALL __put_integer(char *, char *, OutputIter,
	ios_base &, ios_base::fmtflags, wchar_t);

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> >
	BfmeWideUnsignedLongLongPutIterator;

template <>
BfmeWideUnsignedLongLongPutIterator
num_put<wchar_t, BfmeWideUnsignedLongLongPutIterator>::do_put(
	BfmeWideUnsignedLongLongPutIterator output, ios_base &stream, wchar_t fill,
	unsigned _STLP_LONG_LONG value) const
{
	char buffer[64];
	ios_base::fmtflags flags = stream.flags();
	char *begin = __write_integer_backward(buffer + 64, flags, value);
	return __put_integer(begin, buffer + 64, output, stream, flags, fill);
}

_STLP_END_NAMESPACE
