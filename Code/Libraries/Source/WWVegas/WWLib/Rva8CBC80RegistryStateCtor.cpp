// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of a registry-inserting constructor, retail 0x008CBC80 (132 bytes).
//
// Same registry insert as Rva8CB600RegistryCtor.cpp but kind=0x14, this in esi
// under an SEH frame, shared if/else tail, then the 16-byte subobject at +8 is
// constructed with Rva0089C860State(4) (landed as initialize at 0x0089C860).
// Final vptr 0x011372C0. Overflow clears bit 0x40000000; jl to the insert.

class BfmeBaseKind14;

struct BfmeRegistryKind14
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(BfmeBaseKind14 *obj);
};

extern "C" BfmeRegistryKind14 *g_bfmeRegistryVNF;

class BfmeBaseKind14
{
public:
	__forceinline BfmeBaseKind14()
	{
		unsigned int flags = m_flags;
		flags &= 0xf0008014;
		flags |= 0x40008014;
		m_flags = flags;
		g_bfmeRegistryVNF->addOrClear(this);
	}

	virtual ~BfmeBaseKind14() {}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

private:
	unsigned int m_flags;
};

__forceinline void BfmeRegistryKind14::addOrClear(BfmeBaseKind14 *obj)
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

class Rva8CBC80Derived : public BfmeBaseKind14
{
public:
	Rva8CBC80Derived();

private:
	Rva0089C860State m_state;
};

Rva8CBC80Derived::Rva8CBC80Derived() :
	m_state(4)
{
}
