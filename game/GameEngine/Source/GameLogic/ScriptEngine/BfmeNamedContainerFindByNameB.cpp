// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// The ILT at 0x0000A592 and the lookup caller at 0x0033C450 identify this
// method as BfmeNamedContainer0033c340::findByNameB. The table at +0x2C is the
// second string-record table (findNameIndex at 0x00356A60 through ILT
// 0x000072F7); its 20-byte record holds the name at +8 and the m_nodes pointer
// at +0x10, and the method returns m_nodes + 4. Record and table layouts are
// the ones Rva0035A220LookupReleased.cpp and the Rva00359330 / Rva003568C0
// StringRecord siblings declare. Retail 0x00359CE0 is the same name-to-id
// lookup out of line; here it is inlined, then the record is re-read through
// this.

#include "ascii_string.h"

struct Rva00359530Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	bool m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class BfmeNamedContainer0033c340;

class Rva00359530StringRecordTable
{
private:
	friend class BfmeNamedContainer0033c340;
	int findNameIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00359530Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
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
		if ((unsigned int)index < (unsigned int)(table->m_nameIndexesEnd -
			table->m_nameIndexesBegin))
		{
			int id = table->m_nameIndexesBegin[index];
			if (((const StringBase<char> *)&table->m_records[id].m_name)
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
		((char *)m_table.m_records[id].m_nodes + 4) : 0;
}
