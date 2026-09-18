// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 12-byte vector element family anchored by copy body 0x00755100.
// The semantic element identity is unknown. STLport string is an emission
// surrogate for its observed assignment shape, not a recovered game type.
// These bodies were previously misidentified as Video, whose witnessed BFME
// layout is 28 bytes. Keep the address token until named callers prove more.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>

struct Rva00755100Element
{
    _STL::string m_storage;
};

template class _STL::vector<Rva00755100Element>;
