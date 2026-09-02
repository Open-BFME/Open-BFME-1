struct BfmeRecord6BE90
{
	char m_data[0xBC];
};

struct BfmeRecordRange6BE90
{
	char m_pad00[0x24];
	BfmeRecord6BE90 *m_begin;
	BfmeRecord6BE90 *m_end;
};

class BfmeRecordHook6BE90
{
public:
	void bfmeSelect6BE90(BfmeRecord6BE90 *record, int activate, int reserved);
};

class Rva0076BE90Cursor
{
public:
	void advanceRecord();

private:
	char m_pad00[8];
	BfmeRecord6BE90 *m_current;
	char m_pad0C[0x224 - 0x0C];
	bool m_active;
};

void Rva0076BE90Cursor::advanceRecord()
{
	BfmeRecordRange6BE90 *range =
		*reinterpret_cast<BfmeRecordRange6BE90 **>(reinterpret_cast<char *>(this) - 8);
	bool found = false;
	for (BfmeRecord6BE90 *record = range->m_begin; record != range->m_end; ++record)
	{
		if (found)
		{
			if (record)
			{
				m_active = true;
				BfmeRecordHook6BE90 *hook = reinterpret_cast<BfmeRecordHook6BE90 *>(
					reinterpret_cast<char *>(this) - 12);
				hook->bfmeSelect6BE90(record, 1, 0);
			}
			return;
		}
		if (record == m_current)
			found = true;
	}
}
