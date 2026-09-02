// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Twin of Rva89A150RegistryCtor.cpp with kind=3 plus a 0x8000 clear, retail 0x0089A070 (93 bytes).

class BfmeBaseKind3;

struct BfmeRegistryKind3
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline int add(BfmeBaseKind3 *obj);
};

extern "C" BfmeRegistryKind3 *g_bfmeRegistryVNF;

class BfmeBaseKind3
{
public:
	__forceinline BfmeBaseKind3()
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008003;
		flags |= 0x40008003;
		m_flags = flags;

		if (!g_bfmeRegistryVNF->add(this))
			return;
	}

	virtual ~BfmeBaseKind3();

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

protected:
	unsigned int m_flags;
};

__forceinline int BfmeRegistryKind3::add(BfmeBaseKind3 *obj)
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

class BfmeDerivedKind3 : public BfmeBaseKind3
{
public:
	BfmeDerivedKind3();
	virtual ~BfmeDerivedKind3();
};

BfmeDerivedKind3::BfmeDerivedKind3()
{
	m_flags &= ~0x8000u;
	m_flags |= 0x0fff0000;
}
