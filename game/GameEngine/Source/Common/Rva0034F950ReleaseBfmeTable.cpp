class Rva0034F950OwnedValue
{
public:
	virtual ~Rva0034F950OwnedValue(void);
};

struct BfmeEntryERJ
{
	unsigned char m_head[8];
	void *m_value;
	unsigned char m_tail[12];
};

class BfmeTableERJ
{
public:
	BfmeEntryERJ *bfmeAtERJ(int index)
	{
		if (index >= 0 && index < m_count)
			return m_entries + index;

		return 0;
	}

	unsigned char m_head[0x28];
	int m_count;
	BfmeEntryERJ m_entries[1];
};

extern BfmeTableERJ *g_bfmeTableERJ;

// The only reachable evidence is the global table and its anonymous cleanup
// body; no named caller or owning vtable class has been proven for this RVA.
void rva0034f950ReleaseBfmeTable(void)
{
	if (g_bfmeTableERJ != 0)
	{
		for (int index = 0; index < g_bfmeTableERJ->m_count; ++index)
		{
			Rva0034F950OwnedValue *value =
				(Rva0034F950OwnedValue *)g_bfmeTableERJ->bfmeAtERJ(index)->m_value;
			g_bfmeTableERJ->bfmeAtERJ(index)->m_value = 0;

			if (value != 0)
				delete value;
		}
	}
}
