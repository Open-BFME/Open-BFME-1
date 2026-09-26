// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva004095F0
{
	char m_pad0[4];
	int *m_ptr;
	int m_8;
	char m_pad1[4];
	int m_10;

public:
	void sync();
};

void Rva004095F0::sync()
{
	if (m_8)
	{
		if (m_ptr)
		{
			int value = m_10;
			m_ptr[0x10] = value;
			m_10 = value;
		}
	}
}
