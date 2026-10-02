// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen0083E8F0
{
	unsigned char m_pad8[8];
	unsigned m_8;
	unsigned char m_pad14[0x14 - 0xC];
	unsigned m_14;
	unsigned char m_pad58[0x58 - 0x18];
	unsigned m_58;

public:
	void set(unsigned v);
};

// The flag cleared at +0x00 (offset 0x58) and the exception mask tested at
// +0x0E (offset 0x14) are _STL::basic_ios::_M_streambuf and
// ios_base::_M_exception_mask, and retail's call at +0x16 lands on the
// matched STLport 4.5.3 ios_base::_M_throw_failure body at 0x0083E8F0
// (game/Libraries/Source/WWVegas/WWLib/stlport_ios_base_throw_failure.cpp).
// That member is protected, so the reference is spelled through a local
// declaration of the same class with set() befriended; this TU is /Ob0, so the
// call must be the direct thiscall, not an inlined wrapper.
namespace _STL
{
class ios_base
{
protected:
	void _M_throw_failure();
	friend void ::Gen0083E8F0::set(unsigned);
};
}

void Gen0083E8F0::set(unsigned v)
{
	if (!m_58)
		v |= 1;
	m_8 = v;
	if (m_14 & v)
		((_STL::ios_base *)this)->_M_throw_failure();
}