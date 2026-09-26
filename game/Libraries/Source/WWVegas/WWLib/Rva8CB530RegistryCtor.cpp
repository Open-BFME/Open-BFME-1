// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Twin of Rva8CB600RegistryCtor.cpp with kind=4, retail 0x008CB530 (101 bytes).

class BfmeBaseVN4;

struct BfmeRegistryVN4
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline int add(BfmeBaseVN4 *obj);
};

extern "C" BfmeRegistryVN4 *g_bfmeRegistryVNF;

class BfmeBaseVN4
{
public:
	__forceinline BfmeBaseVN4(unsigned int kind)
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008000 | kind;
		flags |= 0x40008000 | kind;
		m_flags = flags;

		if (!g_bfmeRegistryVNF->add(this))
			return;
	}

	virtual ~BfmeBaseVN4();

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

private:
	unsigned int m_flags;
};

__forceinline int BfmeRegistryVN4::add(BfmeBaseVN4 *obj)
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

class BfmeDerivedVN4 : public BfmeBaseVN4
{
public:
	BfmeDerivedVN4(int value);
	virtual ~BfmeDerivedVN4();

private:
	int m_value;
};

BfmeDerivedVN4::BfmeDerivedVN4(int value) :
	BfmeBaseVN4(4),
	m_value(value)
{
}
