// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Twin of Rva89A2C0RegistryStateCtor.cpp with kind=0x1F, retail 0x0089A540 (150 bytes).

class BfmeBaseKind1F;

struct BfmeRegistryKind1F
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(BfmeBaseKind1F *obj);
};

extern "C" BfmeRegistryKind1F *g_bfmeRegistryVNF;

class BfmeBaseKind1F
{
public:
	__forceinline BfmeBaseKind1F()
	{
		unsigned int flags = m_flags;
		flags &= 0xf000801f;
		flags |= 0x4000801f;
		m_flags = flags;
		g_bfmeRegistryVNF->addOrClear(this);
	}

	virtual ~BfmeBaseKind1F() {}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

protected:
	unsigned int m_flags;
};

__forceinline void BfmeRegistryKind1F::addOrClear(BfmeBaseKind1F *obj)
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

class Rva89A540Derived : public BfmeBaseKind1F
{
public:
	Rva89A540Derived();

private:
	Rva0089C860State m_state;
};

Rva89A540Derived::Rva89A540Derived() :
	m_state(8)
{
	m_flags &= ~0x3f80u;
	m_flags |= 0x0fff0040;
}
