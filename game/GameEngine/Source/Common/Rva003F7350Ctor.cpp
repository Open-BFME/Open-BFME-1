// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003F7350
{
	unsigned m_0;
	unsigned m_4;
	unsigned short m_8;
	unsigned short m_A;
	unsigned m_bits;

public:
	Rva003F7350();
};

Rva003F7350::Rva003F7350()
{
	m_0 = 0;
	m_4 = 0;
	m_A = 0;
	m_8 = 0;
	m_bits = (m_bits & 0xFE000000u) | 0x40u;
}
