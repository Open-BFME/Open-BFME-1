// cl: /DNDEBUG /DWIN32 /MD /O2 /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Retail RTTI COL -> type-descriptor links identify this STLport stdexcept family.
// Vtables D2E8B8 + 12*i correspond to the destructor order below; each complete
// destructor restores its own table, and slot 0 names its deleting wrapper.
// The root is __Named_exception, not either previously claimed bad_alloc type.
// The canonical header supplies the native exception base and 256-byte name buffer;
// retail constructor 82C180 copies that buffer at this+12 (ending at this+267).
// Keep the authentic out-of-line destructors unoptimized. Restoring optimization
// afterwards lets MSVC naturally emit the retail deleting wrappers; no anchors.
#include <stdexcept>

#pragma optimize("", off)
namespace _STL {

// Complete destructor 0x0082AE40; RTTI .?AV__Named_exception@_STL@@.
__Named_exception::~__Named_exception() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AE60; RTTI .?AVlogic_error@_STL@@.
logic_error::~logic_error() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AE80; RTTI .?AVruntime_error@_STL@@.
runtime_error::~runtime_error() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AEA0; RTTI .?AVdomain_error@_STL@@.
domain_error::~domain_error() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AEC0; RTTI .?AVinvalid_argument@_STL@@.
invalid_argument::~invalid_argument() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AEE0; RTTI .?AVlength_error@_STL@@.
length_error::~length_error() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AF00; RTTI .?AVout_of_range@_STL@@.
out_of_range::~out_of_range() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AF20; RTTI .?AVrange_error@_STL@@.
range_error::~range_error() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AF40; RTTI .?AVoverflow_error@_STL@@.
overflow_error::~overflow_error() _STLP_NOTHROW_INHERENTLY
{
}

// Complete destructor 0x0082AF60; RTTI .?AVunderflow_error@_STL@@.
underflow_error::~underflow_error() _STLP_NOTHROW_INHERENTLY
{
}

}
#pragma optimize("", on)
