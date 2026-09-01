// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00410F10Allocation
{
public:
	Rva00410F10Allocation()
	{
		for (int i = 0; i < 14; ++i) {
			m_first[i] = 0;
			m_second[i] = 0;
		}
	}

	virtual ~Rva00410F10Allocation();

private:
	int m_first[14];
	int m_second[14];
};

class Rva00410F10Owner
{
public:
	Rva00410F10Allocation *ensure(void);

private:
	unsigned char m_pad0[0x2E0];
	Rva00410F10Allocation *m_allocation;
};

Rva00410F10Allocation *Rva00410F10Owner::ensure(void)
{
	if (!m_allocation)
		m_allocation = new Rva00410F10Allocation;
	return m_allocation;
}
