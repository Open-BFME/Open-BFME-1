// cl: /Igame/Libraries/Source/WWVegas/WWLib
// The body at retail 0x0035A220 checks the released byte for a named record.
// Its table starts at owner +0x2C and uses the second StringRecord
// findNameIndex body at 0x00356A60.

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

class Rva00359530StringRecordTable
{
	friend bool rvaLookupReleased0035a220(void *owner, AsciiString *name);

private:
	int findNameIndex( AsciiString *name );

public:
	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00359530Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class Rva0035A220Owner
{
public:
	unsigned char m_head[0x2c];
	Rva00359530StringRecordTable m_nameTable;
};

bool rvaLookupReleased0035a220(void *owner, AsciiString *name)
{
	Rva00359530StringRecordTable *table =
		&((Rva0035A220Owner *)owner)->m_nameTable;
	unsigned int nameIndex = table->findNameIndex( name );

	if ( nameIndex < (unsigned int)(table->m_nameIndexesEnd -
									 table->m_nameIndexesBegin) )
	{
		int recordIndex = table->m_nameIndexesBegin[nameIndex];

		if ( ((StringBase<char> &)table->m_records[recordIndex].m_name).
				compare( *(StringBase<char> *)name ) == 0 && recordIndex != -1 )
			return ((Rva0035A220Owner *)owner)->m_nameTable
				.m_records[recordIndex].m_released;
	}

	return true;
}
