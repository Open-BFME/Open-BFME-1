// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Twin of Rva8CBC80RegistryStateCtor.cpp with kind=0x17 and state(8), retail 0x0089A2C0 (150 bytes).

class BfmeBaseKind17;

struct BfmeRegistryKind17
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(BfmeBaseKind17 *obj);
};

extern "C" BfmeRegistryKind17 *g_bfmeRegistryVNF;

class BfmeBaseKind17
{
public:
	__forceinline BfmeBaseKind17()
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008017;
		flags |= 0x40008017;
		m_flags = flags;
		g_bfmeRegistryVNF->addOrClear(this);
	}

	virtual ~BfmeBaseKind17() {}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

protected:
	unsigned int m_flags;
};

__forceinline void BfmeRegistryKind17::addOrClear(BfmeBaseKind17 *obj)
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

class Rva89A2C0Derived : public BfmeBaseKind17
{
public:
	Rva89A2C0Derived();

private:
	Rva0089C860State m_state;
};

Rva89A2C0Derived::Rva89A2C0Derived() :
	m_state(8)
{
	m_flags &= ~0x3f80u;
	m_flags |= 0x0fff0040;
}
