// The retail body is the name-index lookup on the first string-record table (its release body is 0x00359330).
// Its table layout is shared with Rva00359330StringRecordRelease.cpp; byte-twin of Rva00359530StringRecordFindIndex.cpp (tools/twin_scan.py).

class AsciiString
{
};

class AsciiStringCompareShim
{
public:
	int compare( const AsciiString &other ) const;
};

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359330StringRecordTable
{
public:
	int findRecordIndex( AsciiString *name );

private:
	int findNameIndex( AsciiString *name );

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00359330Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

int Rva00359330StringRecordTable::findRecordIndex( AsciiString *name )
{
	unsigned int nameIndex = findNameIndex( name );
	if ( nameIndex < m_nameIndexesEnd - m_nameIndexesBegin )
	{
		int recordIndex = m_nameIndexesBegin[nameIndex];
		if ( ((AsciiStringCompareShim &)m_records[recordIndex].m_name).compare( *name ) == 0 )
			return recordIndex;
	}

	return -1;
}
