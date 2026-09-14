// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// STLport 4.5.3 stdio stream-buffer destructors (src/stdio_streambuf.cpp).

#include "stlport_prefix.h"
#include <stdio_streambuf>

namespace _SgI {

stdio_streambuf_base::~stdio_streambuf_base()
{
	_STLP_VENDOR_CSTD::fflush(_M_file);
}

stdio_istreambuf::~stdio_istreambuf()
{
}

stdio_ostreambuf::~stdio_ostreambuf()
{
}

// The original library object also constructs this concrete class, which
// makes its vtable and compiler-generated deleting destructor concrete here.
stdio_istreambuf* make_stdio_istreambuf_for_vtable(FILE* file)
{
	return new stdio_istreambuf(file);
}

stdio_ostreambuf* make_stdio_ostreambuf_for_vtable(FILE* file)
{
	return new stdio_ostreambuf(file);
}

} // namespace _SgI
