// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// STLport 4.5.3 stdio_istreambuf::pbackfail (src/stdio_streambuf.cpp).

#include "stlport_prefix.h"
#include <stdio_streambuf>

namespace _SgI {

stdio_istreambuf::int_type stdio_istreambuf::pbackfail(int_type c)
{
	if (c != traits_type::eof()) {
		int result = _STLP_VENDOR_CSTD::ungetc(c, _M_file);
		return result != EOF ? result : traits_type::eof();
	}
	else {
		if (this->eback() < this->gptr()) {
			this->gbump(-1);
			return traits_type::not_eof(c);
		}
		else
			return traits_type::eof();
	}
}

} // namespace _SgI
