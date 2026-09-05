// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;

struct BfmeEntryBB
{
	int m_key;
	unsigned char m_data[0x18];
};

struct BfmeEntryYB
{
	int m_key;
	unsigned char m_data[0x50];
};

struct BfmeCallJ3A1FC
{
	BfmeEntryBB *invoke(int key) const;
};

struct BfmeEntry8
{
	int m_key;
	int m_data;
};

class Rva002E4CA0
{
public:
	void *rva002E4CA0(int key) const;

private:
	unsigned char m_pad00[0x10];
	volatile BfmeEntry8 m_entries[13];
	unsigned char m_pad78[0x7c - 0x78];
	volatile int *m_valuesBegin;
	volatile int *m_valuesEnd;
	unsigned char m_pad84[0x98 - 0x84];
	volatile BfmeEntryYB *m_recordsBegin;
	volatile BfmeEntryYB *m_recordsEnd;
};

void *Rva002E4CA0::rva002E4CA0(int key) const
{
	int index = 0;
	BfmeEntry8 *entry = (BfmeEntry8 *)m_entries;
	while (index < 13)
	{
		if (entry->m_key == key)
		{
			BfmeEntry8 *entry = (BfmeEntry8 *)&m_entries[index];
			if (entry != 0)
				return entry;
			goto values;
		}
		++index;
		++entry;
	}

values:
	{
		volatile int *value = m_valuesBegin;
		while (value != m_valuesEnd)
		{
			if (*value == key)
				return (void *)value;
			++value;
		}
	}

	volatile BfmeEntryYB *record = m_recordsBegin;
	while (record != m_recordsEnd)
	{
		if (record->m_key == key)
			return (void *)record;
		record = (volatile BfmeEntryYB *)((char *)record + 0x54);
	}

	return reinterpret_cast<const BfmeCallJ3A1FC *>(this)->invoke(key);
}
