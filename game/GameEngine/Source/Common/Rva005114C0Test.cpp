// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva005114C0
{
	char m_lead[0x260];
	void *m_a;
	void *m_b;
	void *m_c;

public:
	unsigned char test();
};

unsigned char Rva005114C0::test()
{
	if (m_a)
	{
		if (m_b)
		{
			if (m_c)
				return 1;
		}
	}
	return 0;
}
