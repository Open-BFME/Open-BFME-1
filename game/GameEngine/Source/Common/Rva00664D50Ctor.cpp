// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00664D50
{
	unsigned m_buf[0x800];

public:
	Rva00664D50();
};

Rva00664D50::Rva00664D50()
{
	for (unsigned i = 0; i < 0x800; ++i)
		m_buf[i] = 0;
}
