// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail 0x010F11C4 is DrawableIconInfo's vftable (dir32_addresses.csv records both
// names); DrawableVisualState.cpp emits it with the 0x004133C0 destructor. A virtual
// ~Rva00410F10Allocation here had no body, so the constructor stores that vftable.
extern "C" void *__identifier("??_7DrawableIconInfo@@6B@")[];

class Rva00410F10Allocation
{
public:
	Rva00410F10Allocation()
	{
		m_vtable = __identifier("??_7DrawableIconInfo@@6B@");
		for (int i = 0; i < 14; ++i) {
			m_first[i] = 0;
			m_second[i] = 0;
		}
	}

private:
	void **m_vtable;
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
