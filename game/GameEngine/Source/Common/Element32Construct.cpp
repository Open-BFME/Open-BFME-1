// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: in-place construction helper for the 32-byte element used by
// the copy/fill walks at 0x00770C30 and 0x00770C70. Retail 0x00770B20.
#include <memory>
#include <string>

struct Elem32
{
	int m_at00;
	_STL::string m_at04;
	int m_at10;
	int m_at14;
	int m_at18;
	int m_at1C;
};

template void _STL::_Construct(Elem32 *, const Elem32 &);
