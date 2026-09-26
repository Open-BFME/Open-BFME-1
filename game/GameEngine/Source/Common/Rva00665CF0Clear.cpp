// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00665CF0
{
	unsigned m_buf[0x800];

public:
	void clear();
};

void Rva00665CF0::clear()
{
	for (unsigned i = 0; i < 0x800; ++i)
		m_buf[i] = 0;
}
