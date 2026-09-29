// Retail 0x008A1D80 (102 bytes, thiscall, ret 8): scans the owner's +0x04
// entry list for the first type-8 entry carrying the given key, runs that
// entry's action stream on the Apt interpreter with the caller's argument
// (the same BfmeR1226::bfmeAdd1226 / bfmeLine1226 pair BfmeConv1226.cpp
// uses) under the "Imported Init Actions" label, then negates the entry's
// key so it cannot fire again.  No named caller reaches it, so the owner
// keeps the address.

class BfmeR1226
{
public:
	void bfmeAdd1226(void *a, void *b, int c);
	void bfmeLine1226(char *a);
};

extern BfmeR1226 g_bfmeR1226;

struct Rva008A1D80Entry
{
	int m_type;
	int m_key;
	void *m_stream;
};

struct Rva008A1D80List
{
	int m_count;
	Rva008A1D80Entry **m_entries;
};

class Rva008A1D80Owner
{
public:
	void runImportedInitActions(void *arg, int key);

	int m_bfme00;
	Rva008A1D80List *m_list;
};

void Rva008A1D80Owner::runImportedInitActions(void *arg, int key)
{
	for (int i = 0; i < m_list->m_count; ++i)
	{
		Rva008A1D80Entry *entry = m_list->m_entries[i];
		if (entry->m_type == 8 && entry->m_key == key)
		{
			g_bfmeR1226.bfmeAdd1226(m_list->m_entries[i]->m_stream, arg, -1);
			g_bfmeR1226.bfmeLine1226("Imported Init Actions");
			entry->m_key = -entry->m_key;
			return;
		}
	}
}
