// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class BfmeBaseKind26;

struct BfmeRegistryKind26
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(BfmeBaseKind26 *obj);
};

extern "C" BfmeRegistryKind26 *g_bfmeRegistryVNF;

class BfmeBaseKind26
{
public:
	__forceinline BfmeBaseKind26()
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008026;
		flags |= 0x40008026;
		m_flags = flags;
		g_bfmeRegistryVNF->addOrClear(this);
	}

	virtual ~BfmeBaseKind26() {}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

protected:
	unsigned int m_flags;
};

__forceinline void BfmeRegistryKind26::addOrClear(BfmeBaseKind26 *obj)
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

class Rva89A880Derived : public BfmeBaseKind26
{
public:
	Rva89A880Derived();

private:
	Rva0089C860State m_state;
};

Rva89A880Derived::Rva89A880Derived() :
	m_state(8)
{
	m_flags &= ~0x3f80u;
	m_flags |= 0x0fff0040;
}
