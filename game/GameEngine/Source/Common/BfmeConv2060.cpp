class BfmeEntryCK
{
public:
	int m_bfmeTag;
	BfmeEntryCK *m_bfmeNext;
	int m_bfmeGap[3];
	void *m_bfmeKey;
};

extern BfmeEntryCK *g_bfmeListCK;

void __stdcall bfmeUnlinkCK(BfmeEntryCK *entry);

static __forceinline BfmeEntryCK *bfmeFindCK(void *key)
{
	BfmeEntryCK *entry = g_bfmeListCK;

	while (entry)
	{
		if (entry->m_bfmeKey == key)
			break;

		entry = entry->m_bfmeNext;
	}

	return entry;
}

bool __cdecl bfmeRemoveCK(void *key)
{
	BfmeEntryCK *head = g_bfmeListCK;
	BfmeEntryCK *entry = bfmeFindCK(key);

	if (entry != 0)
	{
		if (entry == head)
			g_bfmeListCK = entry->m_bfmeNext;
		else
			bfmeUnlinkCK(entry);
	}

	return entry != 0;
}
