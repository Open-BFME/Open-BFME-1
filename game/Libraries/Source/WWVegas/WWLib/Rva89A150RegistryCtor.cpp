// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Twin of Rva8CB530RegistryCtor.cpp with kind=0xB and no payload, retail 0x0089A150 (87 bytes).

class BfmeBaseKindB;

struct BfmeRegistryKindB
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline int add(BfmeBaseKindB *obj);
};

extern "C" BfmeRegistryKindB *g_bfmeRegistryVNF;

class BfmeBaseKindB
{
public:
	__forceinline BfmeBaseKindB()
	{
		unsigned int flags = m_flags;
		flags &= 0xf000800b;
		flags |= 0x4000800b;
		m_flags = flags;

		if (!g_bfmeRegistryVNF->add(this))
			return;
	}

	virtual ~BfmeBaseKindB();

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

protected:
	unsigned int m_flags;
};

__forceinline int BfmeRegistryKindB::add(BfmeBaseKindB *obj)
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

class BfmeDerivedKindB : public BfmeBaseKindB
{
public:
	BfmeDerivedKindB();
	virtual ~BfmeDerivedKindB();
};

BfmeDerivedKindB::BfmeDerivedKindB()
{
	m_flags |= 0x0fff0000;
}
