// ?at@Rva008B8D00Owner@@QAEPAXH@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Slot 4 of vtable 0x01136D58. Primary table at +0x20 below bound +0x28,
// secondary table at +0x18 below the low byte of +0x1C, else tail-call the
// 0x10-byte BfmeS1238 subobject at +8 with the twice-reduced index.

class BfmeS1238
{
public:
	BfmeS1238 *bfmeAt1238B(int index);

private:
	void *m_vtable;
	unsigned *m_entries;
	unsigned m_zero;
	unsigned m_one;
};

class Rva008B8D00Owner
{
public:
	void *at(int index);

private:
	void *m_vptr;
	unsigned char m_pad04[4];
	BfmeS1238 m_base;
	void **m_secondary;
	unsigned m_bound2;
	void **m_primary;
	int m_unused24;
	int m_bound;
};

void *Rva008B8D00Owner::at(int index)
{
	int bound = m_bound;
	if (index < bound)
	{
		void **table = m_primary;
		if (table)
		{
			unsigned tagged = (unsigned)table[index];
			if (!tagged || (tagged & 1))
				return (void *)(tagged & ~1u);
			return 0;
		}
	}

	unsigned bound2 = m_bound2;
	index -= bound;
	bound2 &= 0xff;
	if (index < (int)bound2)
		return m_secondary[index];

	index -= (int)bound2;
	return m_base.bfmeAt1238B(index);
}
