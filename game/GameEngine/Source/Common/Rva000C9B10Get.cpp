// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C9B10
{
	char m_pad[0x64];
	void *m_1;
	void *m_2;
	void *m_3;

public:
	void *get(int which);
};

void *Rva000C9B10::get(int which)
{
	switch (which)
	{
	case 1:
		return m_1;
	case 2:
		return m_2;
	case 3:
		return m_3;
	default:
		return 0;
	}
}
