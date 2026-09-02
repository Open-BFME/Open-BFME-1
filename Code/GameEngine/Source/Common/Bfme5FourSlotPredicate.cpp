// Checks four enabled slots and succeeds when one slot's object accepts the
// supplied value for the owner's current source.

class BfmeFourSlotSource;

class BfmeFourSlotEntry
{
public:
	bool bfmeAccepts(BfmeFourSlotSource *source, int value, int mode);
};

class BfmeFourSlotTable
{
public:
	BfmeFourSlotEntry *bfmeGet(int index);
};

class BfmeFourSlotSource
{
public:
	BfmeFourSlotTable *bfmeTable(void) { return &m_table; }

	char m_prefix[0x264];
	BfmeFourSlotTable m_table;
};

class BfmeFourSlotFlags
{
public:
	char m_prefix[0x3c];
	unsigned int m_enabled;
};

class BfmeFourSlotOwner
{
public:
	bool bfmeAnyAccepts(int value);

private:
	char m_prefix[8];
	BfmeFourSlotFlags *m_flags;
	char m_gap[4];
	BfmeFourSlotSource *m_source;
};

// ?bfmeAnyAccepts@BfmeFourSlotOwner@@QAE_NH@Z
bool BfmeFourSlotOwner::bfmeAnyAccepts(int value)
{
	for (int index = 0; index < 4; ++index)
	{
		BfmeFourSlotSource *source = m_source;
		BfmeFourSlotEntry *entry = source->bfmeTable()->bfmeGet(index);
		if (entry != 0 &&
			(m_flags->m_enabled & (1 << index)) != 0 &&
			entry->bfmeAccepts(m_source, value, 0))
		{
			return true;
		}
	}
	return false;
}
