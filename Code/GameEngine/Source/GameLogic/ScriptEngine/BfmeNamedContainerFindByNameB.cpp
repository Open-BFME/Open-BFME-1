// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// The ILT at 0x0000A592 and the lookup caller at 0x0033C450 identify this
// method as BfmeNamedContainer0033c340::findByNameB. The table at +0x2C is the
// second string-record table (findNameIndex at 0x00356A60 through ILT
// 0x000072F7); its 20-byte record holds the name at +8 and the stored item
// pointer at +0x10. Retail 0x00359CE0 is the same name-to-id lookup out of
// line; here it is inlined, then the item is re-read through this.

#include "ascii_string.h"

struct BfmeBucketERY
{
	char m_head[8];
	AsciiString m_name;
	char m_padding[4];
	void *m_item;
};

class BfmeNamedContainer0033c340;

class Rva00359530StringRecordTable
{
private:
	friend class BfmeNamedContainer0033c340;
	int findNameIndex(AsciiString *name);

	int *m_first;
	int *m_last;
	char m_padding[4];
	BfmeBucketERY *m_entries;
};

class BfmeNamedItem0033c340;

class BfmeNamedContainer0033c340
{
public:
	BfmeNamedItem0033c340 *findByNameB(const AsciiString &name);

private:
	// Inlined copy of retail 0x00359CE0: record id for a name, or -1.
	int rva00359CE0LookupId(const AsciiString &name)
	{
		Rva00359530StringRecordTable *table = &m_table;
		int index = table->findNameIndex((AsciiString *)&name);
		if ((unsigned int)index < (unsigned int)(table->m_last - table->m_first))
		{
			int id = table->m_first[index];
			if (((const StringBase<char> *)&table->m_entries[id].m_name)
					->compare(*(const StringBase<char> *)&name) == 0)
				return id;
		}
		return -1;
	}

	char m_prefix[0x2c];
	Rva00359530StringRecordTable m_table;
};

// ?findByNameB@BfmeNamedContainer0033c340@@QAEPAVBfmeNamedItem0033c340@@ABVAsciiString@@@Z
BfmeNamedItem0033c340 *BfmeNamedContainer0033c340::findByNameB(
	const AsciiString &name)
{
	int id = rva00359CE0LookupId(name);
	return id != -1 ? (BfmeNamedItem0033c340 *)
		((char *)m_table.m_entries[id].m_item + 4) : 0;
}
