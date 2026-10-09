// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen0083E8F0;

// The retail tail call reaches ios_base::_M_throw_failure at 0x0083E8F0.
// Keep its protected thiscall declaration without importing stream bodies.
namespace _STL
{
class ios_base
{
protected:
	void _M_throw_failure();
	friend class ::Gen0083E8F0;
};
}

class Gen0083E8F0
{
	unsigned char m_pad8[8];
	unsigned m_8;
	unsigned char m_pad14[0x14 - 0xC];
	unsigned m_14;
	unsigned char m_pad58[0x58 - 0x18];
	unsigned m_58;

public:
	void addFlags(unsigned flags);
};

void Gen0083E8F0::addFlags(unsigned flags)
{
	unsigned combined = m_8;
	combined |= flags;
	if (!m_58)
		combined |= 1;
	if (m_14 & combined) {
		m_8 = combined;
		reinterpret_cast<_STL::ios_base *>(this)->_M_throw_failure();
	} else {
		m_8 = combined;
	}
}
