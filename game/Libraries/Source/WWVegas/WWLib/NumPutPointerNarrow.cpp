// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Adapted from STLport 4.5.3.
// STLport's narrow num_put pointer formatter at retail body 0x00832480
// saves ios_base flags, applies showbase/hex/internal with a ten-byte width,
// widens '0' through the cached narrow ctype facet, delegates to the unsigned
// integer virtual, restores the flags, and returns the output iterator.

#include "stlport_prefix.h"

// The stock _num_put.c source constructs an unused locale temporary in this
// overload. The retail STLport object used the equivalent no-temporary
// implementation, so this specialization keeps the compiler-facing shape.
#undef _STLP_EXPOSE_STREAM_IMPLEMENTATION
#include <stl/_num_put.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

typedef ostreambuf_iterator<char, char_traits<char> >
	BfmeNarrowPointerIterator;

template <>
BfmeNarrowPointerIterator
num_put<char, BfmeNarrowPointerIterator>::do_put(
	BfmeNarrowPointerIterator output, ios_base &stream, char,
	const void *value) const
{
	const ctype<char> &ctype_facet =
		*(const ctype<char> *)stream._M_ctype_facet();
	const ios_base::fmtflags saved_flags = stream.flags();
	stream.setf(ios_base::hex, ios_base::basefield);
	stream.setf(ios_base::showbase);
	stream.setf(ios_base::internal, ios_base::adjustfield);
	stream.width((sizeof(void *) * 2) + 2);
	BfmeNarrowPointerIterator result = this->do_put(output, stream,
		ctype_facet.widen('0'),
		(unsigned _STLP_LONG_LONG)value);
	stream.flags(saved_flags);
	return result;
}

_STLP_END_NAMESPACE
