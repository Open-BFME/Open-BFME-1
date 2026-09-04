// ?lookupAndStore@Rva00801940LookupStore@@QAEHPAX0@Z
// partial score=0.96 date=2026-09-04
// ?lookupAndStore@Rva00801940LookupStore@@QAEHPAX0@Z
// partial score=0.96 date=2026-09-01
int __stdcall bfmeLookRH(void *table, void *key);

class BfmeSub1251
{
public:
	void bfmeSet1251(void *value);

private:
	char m_storage[8];
};

struct Rva00801940Owner
{
	char m_pad00[0x2A8];
	int m_table[1];
};

class Rva00801940LookupStore
{
public:
	int lookupAndStore(void *key, void *value);

private:
	char m_pad00[4];
	Rva00801940Owner *m_owner;
	char m_pad08[8];
	BfmeSub1251 *m_entries;
	int m_count;
};

int Rva00801940LookupStore::lookupAndStore(void *key, void *value)
{
	int index = bfmeLookRH(m_owner->m_table, key);
	if (index == -1)
		return -106;

	if (index >= m_count)
	{
		BfmeSub1251 *entry = 0;
		void *storedValue = value;
		entry->bfmeSet1251(storedValue);
		return 0;
	}
	else
	{
		BfmeSub1251 *entry = m_entries;
		void *storedValue = value;
		entry[index].bfmeSet1251(storedValue);
		return 0;
	}
}
