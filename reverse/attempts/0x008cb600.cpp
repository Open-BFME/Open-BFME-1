// ??0BfmeDerivedVNF@@QAE@H@Z
// partial score=0.92 date=2026-09-01
struct BfmeRegistryVNF
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline bool failedAdd(void *entry)
	{
		int index = m_count;
		if (index < m_capacity)
		{
			m_entries[index] = entry;
			++m_count;
			return false;
		}

		return true;
	}
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

		if (!g_bfmeRegistryVNF->failedAdd(this))
			return;

		flags &= ~0x40000000;
		m_flags = flags;
	}

	virtual ~BfmeBaseVNF();

private:
	unsigned int m_flags;
};

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
