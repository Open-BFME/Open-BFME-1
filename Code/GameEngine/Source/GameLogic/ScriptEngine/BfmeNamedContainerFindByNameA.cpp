// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// The ILT at 0x000323F8 and the lookup caller lookupNamedItemA at 0x0033C340
// identify this method as BfmeNamedContainer0033c340::findByNameA. The table
// at +0x0C is the first string-record table (findNameIndex at 0x003568C0
// through ILT 0x000329FC); its 20-byte record holds the name at +8 and the
// m_nodes pointer at +0x10, and the method returns m_nodes + 4. Record and
// table layouts are the ones Rva00359FE0LookupReleased.cpp and the
// Rva00359330 / Rva003568C0 StringRecord siblings declare. Retail 0x00359C80
// is the same name-to-id lookup out of line; here it is inlined, then the
// record is re-read through this. Byte twin of findByNameB at 0x00359DC0.

#include "ascii_string.h"

struct Rva00359330Record
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

class Rva00359330StringRecordTable
{
private:
	friend class BfmeNamedContainer0033c340;
	int findNameIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00359330Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class BfmeNamedItem0033c340;

class BfmeNamedContainer0033c340
{
public:
	BfmeNamedItem0033c340 *findByNameA(const AsciiString &name);

private:
	// Inlined copy of retail 0x00359C80: record id for a name, or -1.
	int rva00359C80LookupId(const AsciiString &name)
	{
		Rva00359330StringRecordTable *table = &m_table;
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

	char m_prefix[0xc];
	Rva00359330StringRecordTable m_table;
};

// ?findByNameA@BfmeNamedContainer0033c340@@QAEPAVBfmeNamedItem0033c340@@ABVAsciiString@@@Z
BfmeNamedItem0033c340 *BfmeNamedContainer0033c340::findByNameA(
	const AsciiString &name)
{
	int id = rva00359C80LookupId(name);
	return id != -1 ? (BfmeNamedItem0033c340 *)
		((char *)m_table.m_records[id].m_nodes + 4) : 0;
}
