// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00666C30
{
	unsigned m_buf[0x800];

public:
	Rva00666C30(unsigned value);
};

Rva00666C30::Rva00666C30(unsigned value)
{
	for (unsigned i = 0; i < 0x800; ++i)
		m_buf[i] = 0;
	m_buf[0] = value;
}
