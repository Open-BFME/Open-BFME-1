// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow ostreambuf_iterator num_put::do_put(long).
// The retail body is slot 7 of the vtable at VA 0x0112E9B0, whose RTTI
// complete object locator names the narrow num_put, and it calls the
// __write_integer_backward instantiation whose value type is long.  It formats
// into a local 64-byte buffer and then applies grouping, field width and fill,
// exactly as the unsigned long long body at slot 2 does.

#include "stlport_prefix.h"

#undef _STLP_EXPOSE_STREAM_IMPLEMENTATION
#include <stl/_num_put.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

template <class Integer>
char *_STLP_CALL __write_integer_backward(char *, ios_base::fmtflags, Integer);

template <class OutputIter>
OutputIter _STLP_CALL __put_integer(char *, char *, OutputIter,
	ios_base &, ios_base::fmtflags, char);

typedef ostreambuf_iterator<char, char_traits<char> >
	BfmeNarrowLongPutIterator;

template <>
BfmeNarrowLongPutIterator
num_put<char, BfmeNarrowLongPutIterator>::do_put(
	BfmeNarrowLongPutIterator output, ios_base &stream, char fill,
	long value) const
{
	char buffer[64];
	ios_base::fmtflags flags = stream.flags();
	char *begin = __write_integer_backward(buffer + 64, flags, value);
	return __put_integer(begin, buffer + 64, output, stream, flags, fill);
}

_STLP_END_NAMESPACE
