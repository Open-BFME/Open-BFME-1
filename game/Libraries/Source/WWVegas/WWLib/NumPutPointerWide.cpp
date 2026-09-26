// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Adapted from STLport 4.5.3.
// STLport's wide num_put pointer formatter.  Its retail body at 0x008324F0
// saves ios_base flags, applies showbase/hex/internal with a ten-byte width,
// widens '0' through the cached wide ctype facet, delegates to the unsigned
// integer virtual, restores the flags, and returns the output iterator.
// The ctype<wchar_t>::do_widen slot (+0x28) distinguishes this body from the
// narrow sibling at 0x00832480.

#include "stlport_prefix.h"

// The stock _num_put.c source constructs an unused locale temporary in this
// overload.  The retail STLport object was built from the equivalent
// no-temporary implementation; hide the source implementation and recover
// that compiler-facing specialization directly from the public facet type.
#undef _STLP_EXPOSE_STREAM_IMPLEMENTATION
#include <stl/_num_put.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> >
	BfmeWidePointerIterator;

template <>
BfmeWidePointerIterator
num_put<wchar_t, BfmeWidePointerIterator>::do_put(
	BfmeWidePointerIterator output, ios_base &stream, wchar_t,
	const void *value) const
{
	const ctype<wchar_t> &ctype_facet =
		*(const ctype<wchar_t> *)stream._M_ctype_facet();
	const ios_base::fmtflags saved_flags = stream.flags();
	stream.setf(ios_base::hex, ios_base::basefield);
	stream.setf(ios_base::showbase);
	stream.setf(ios_base::internal, ios_base::adjustfield);
	stream.width((sizeof(void *) * 2) + 2);
	BfmeWidePointerIterator result = this->do_put(output, stream,
		ctype_facet.widen('0'),
		(unsigned _STLP_LONG_LONG)value);
	stream.flags(saved_flags);
	return result;
}

_STLP_END_NAMESPACE
