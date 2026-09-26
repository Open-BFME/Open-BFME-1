// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0035ED70
{
	unsigned char m_pad[0x20];
	unsigned char *m_20;
	unsigned char m_24;

public:
	void restore();
};

void Rva0035ED70::restore()
{
	if (m_20 != 0)
	{
		*m_20 = m_24;
		m_20 = 0;
		m_24 = 0;
	}
}
