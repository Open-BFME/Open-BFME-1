// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeBaseKind27;

struct BfmeRegistryKind27
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(BfmeBaseKind27 *obj);
};

extern "C" BfmeRegistryKind27 *g_bfmeRegistryVNF;

class BfmeBaseKind27
{
public:
	__forceinline BfmeBaseKind27()
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008027;
		flags |= 0x40008027;
		m_flags = flags;
		g_bfmeRegistryVNF->addOrClear(this);
	}

	virtual ~BfmeBaseKind27() {}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

protected:
	unsigned int m_flags;
};

__forceinline void BfmeRegistryKind27::addOrClear(BfmeBaseKind27 *obj)
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

class Rva89AA20Derived : public BfmeBaseKind27
{
public:
	Rva89AA20Derived();

private:
	Rva0089C860State m_state;
};

Rva89AA20Derived::Rva89AA20Derived() :
	m_state(8)
{
	m_flags &= ~0x3f80u;
	m_flags |= 0x0fff0040;
}
