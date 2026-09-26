// cl: /O2
// 0x007EA550 / 0x007EA590: FESL servicehub.cpp eight-slot owner table.
// The pinger at 0x00803260 already names these members.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva00803080;

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *owner);
	void remove(Rva00803080 *owner);

private:
	char m_pad[0x10];
	Rva00803080 *m_slots[8];
};

void Rva007EAServiceList::add(Rva00803080 *owner)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_slots[i] == 0)
		{
			m_slots[i] = owner;
			return;
		}
	}
	Rva007EB810Get()->fail(
		"false",
		"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp",
		679);
}

void Rva007EAServiceList::remove(Rva00803080 *owner)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_slots[i] == owner)
		{
			m_slots[i] = 0;
			return;
		}
	}
	Rva007EB810Get()->fail(
		"false",
		"\\views\\feslbuild_main\\jabba\\fesl\\source\\servicehub.cpp",
		694);
}
