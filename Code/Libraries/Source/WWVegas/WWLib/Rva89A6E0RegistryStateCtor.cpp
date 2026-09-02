// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Twin of Rva89A2C0RegistryStateCtor.cpp with kind=0x19, retail 0x0089A6E0 (150 bytes).

class BfmeBaseKind19;

struct BfmeRegistryKind19
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(BfmeBaseKind19 *obj);
};

extern "C" BfmeRegistryKind19 *g_bfmeRegistryVNF;

class BfmeBaseKind19
{
public:
	__forceinline BfmeBaseKind19()
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008019;
		flags |= 0x40008019;
		m_flags = flags;
		g_bfmeRegistryVNF->addOrClear(this);
	}

	virtual ~BfmeBaseKind19() {}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

protected:
	unsigned int m_flags;
};

__forceinline void BfmeRegistryKind19::addOrClear(BfmeBaseKind19 *obj)
{
	int index = m_count;
	if (index >= m_capacity)
	{
		obj->clearRegistered();
		return;
	}

	m_entries[index] = obj;
	++m_count;
}

class Rva0089C860State
{
public:
	Rva0089C860State(int value);
	~Rva0089C860State();

private:
	int m_value;
	int m_first;
	int m_second;
	int m_third;
};

class Rva89A6E0Derived : public BfmeBaseKind19
{
public:
	Rva89A6E0Derived();

private:
	Rva0089C860State m_state;
};

Rva89A6E0Derived::Rva89A6E0Derived() :
	m_state(8)
{
	m_flags &= ~0x3f80u;
	m_flags |= 0x0fff0040;
}
