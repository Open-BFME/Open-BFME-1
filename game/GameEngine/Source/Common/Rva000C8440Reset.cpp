// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C8440
{
	void *m_vtbl;
	int m_a[32];
	int m_aCount;
	int m_b[32];
	int m_bCount;

public:
	void reset();
};

void Rva000C8440::reset()
{
	for (int i = 0; i < 32; ++i)
	{
		m_a[i] = 0;
		m_b[i] = 0;
	}
	m_aCount = 0;
	m_bCount = 0;
}
