// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of a registry-inserting constructor, retail 0x008CB600 (101 bytes).
//
// Inlines a simplified Rva899F00Base construction: mask/or the +4 bitfield with
// kind=8 (0xF0008008 / 0x40008008), store base vptr 0x01135D68, push this into
// the fixed registry at VA 0x01337810 (capacity at +0, count at +4, entries at
// +8), and on overflow clear bit 0x40000000. Then store derived vptr 0x01137140
// and the stack argument at +8. Failure is the fallthrough (jl to the insert).

class BfmeBaseVNF;

struct BfmeRegistryVNF
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline int add(BfmeBaseVNF *obj);
};

extern "C" BfmeRegistryVNF *g_bfmeRegistryVNF;

class BfmeBaseVNF
{
public:
	__forceinline BfmeBaseVNF(unsigned int kind)
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008000 | kind;
		flags |= 0x40008000 | kind;
		m_flags = flags;

		if (!g_bfmeRegistryVNF->add(this))
			return;
	}

	virtual ~BfmeBaseVNF();

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

private:
	unsigned int m_flags;
};

__forceinline int BfmeRegistryVNF::add(BfmeBaseVNF *obj)
{
	int index = m_count;
	if (index >= m_capacity)
	{
		obj->clearRegistered();
		return 0;
	}

	m_entries[index] = obj;
	++m_count;
	return 1;
}

class BfmeDerivedVNF : public BfmeBaseVNF
{
public:
	BfmeDerivedVNF(int value);
	virtual ~BfmeDerivedVNF();

private:
	int m_value;
};

BfmeDerivedVNF::BfmeDerivedVNF(int value) :
	BfmeBaseVNF(8),
	m_value(value)
{
}
