// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// STLport 4.5.3 stdio_ostreambuf::overflow (src/stdio_streambuf.cpp).
//
// Slot 12 of the vtable at VA 0x0112F2B8, whose RTTI complete object locator
// spells '.?AVstdio_ostreambuf@_SgI@@'.  Slot 12 of the narrow basic_streambuf
// table at 0x0112EBD4 holds the one-argument eof returner that
// inputs/vendor/stlport/stl/_streambuf.h calls overflow, and this is the slot
// stdio_ostreambuf overrides.  The PE import table names the two slots this
// body calls, 0x00F593C4 as fputc and 0x00F593A8 as fflush, both in MSVCR71.dll.

#include "stlport_prefix.h"
#include <stdio_streambuf>

namespace _SgI {

stdio_ostreambuf::int_type stdio_ostreambuf::overflow(int_type c)
{
	if (c == traits_type::eof()) {
		ptrdiff_t pending = this->pptr() - this->pbase();
		if (pending != 0) {
			_STLP_VENDOR_CSTD::fflush(_M_file);
			return (this->pptr() - this->pbase()) < pending
				? traits_type::not_eof(c)
				: traits_type::eof();
		}
		return traits_type::not_eof(c);
	}
	else {
		int result = _STLP_VENDOR_CSTD::fputc(c, _M_file);
		return result != EOF ? result : traits_type::eof();
	}
}

} // namespace _SgI
