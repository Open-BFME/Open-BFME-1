class BfmeEntryCK
{
public:
	int m_bfmeTag;
	BfmeEntryCK *m_bfmeNext;
	int m_bfmeGap[3];
	void *m_bfmeKey;
};

class TimedOperationNode;
extern TimedOperationNode *g_timedOperationHead;

// Retail calls ILT 0x00035553, which the ledger defines as ?j_00035553@@YAXXZ.
extern void j_00035553();
typedef void (__stdcall *BfmeUnlinkCKCall)(BfmeEntryCK *entry);

static __forceinline BfmeEntryCK *bfmeFindCK(void *key)
{
	BfmeEntryCK *entry = (BfmeEntryCK *)g_timedOperationHead;

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
	BfmeEntryCK *head = (BfmeEntryCK *)g_timedOperationHead;
	BfmeEntryCK *entry = bfmeFindCK(key);

	if (entry != 0)
	{
		if (entry == head)
			g_timedOperationHead = (TimedOperationNode *)entry->m_bfmeNext;
		else
			((BfmeUnlinkCKCall)j_00035553)(entry);
	}

	return entry != 0;
}
