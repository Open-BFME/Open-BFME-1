// ?getIndexedRecord@Rva00194150Table@@QBE_NHHAAVBuildListInfo@@H@Z
// partial score=0.55 date=2026-09-09
// ?getIndexedRecord@Rva00194150Table@@QBE_NHHAAVBuildListInfo@@H@Z
// Open-BFME: clean reconstruction of retail 0x00194150.
// Scans a fixed 32-entry keyed table and copies an indexed 140-byte
// BuildListInfo record from one of two side-specific ranges.

class BuildListInfo
{
public:
	BuildListInfo &operator=(const BuildListInfo &);

private:
	unsigned char m_data[0x8C];
};

struct Rva00194150Entry
{
	int m_key;
	BuildListInfo *m_begin0;
	BuildListInfo *m_end0;
	unsigned int m_spare0;
	BuildListInfo *m_begin1;
	BuildListInfo *m_end1;
	unsigned int m_spare1;
};

class Rva00194150Table
{
public:
	bool getIndexedRecord(int key, int index, BuildListInfo &dest, int side) const;

private:
	unsigned char m_prefix[0x66C];
	Rva00194150Entry m_entries[32];
};

bool Rva00194150Table::getIndexedRecord(int key, int index, BuildListInfo &dest, int side) const
{
	const int mode = side;
	if (mode != 0 && mode != 1)
		return false;

	const Rva00194150Entry *entry = m_entries;
	const int lookupKey = key;
	int i = 0;
	do
	{
		if (entry->m_key == lookupKey)
			goto found;
		++i;
		++entry;
	} while (i < 32);
	return false;

found:
	BuildListInfo *begin;
	BuildListInfo *end;
	if (mode == 0)
	{
		begin = entry->m_begin0;
		end = entry->m_end0;
	}
	else
	{
		if (mode != 1)
			return false;
		begin = entry->m_begin1;
		end = entry->m_end1;
	}

	int count = end - begin;
	if (index >= count)
		return false;

	dest = begin[index];
	return true;
}
