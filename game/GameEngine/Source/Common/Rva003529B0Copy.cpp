// cl: /O2 /Ob0

void j_00028718();
void j_0002a7b1();
void j_0003fa85();
void j_0003e185();

// Retail VA010E855C: four existing ILT entries (vtable_lookup.py), the vftable installed by
// the script-record constructors, copy constructors and clone.
void *g_ScriptNodeVftable[4] = {
	reinterpret_cast<void *>(&j_00028718),
	reinterpret_cast<void *>(&j_0002a7b1),
	reinterpret_cast<void *>(&j_0003fa85),
	reinterpret_cast<void *>(&j_0003e185),
};

class Rva003525E0Pair
{
public:
	Rva003525E0Pair(const Rva003525E0Pair &other);

private:
	void *m_a;
	void *m_b;
};

class Rva003529B0
{
	void *m_vptr;
	Rva003525E0Pair m_04;
	char m_0C;
	char m_0D;
	char m_0E;

public:
	Rva003529B0(const Rva003529B0 *other);
};

Rva003529B0::Rva003529B0(const Rva003529B0 *other)
	: m_04(*(other ? &other->m_04 : 0))
{
	m_vptr = g_ScriptNodeVftable;
	m_0C = other->m_0C;
	m_0D = other->m_0D;
	m_0E = 0;
}
