// The retail body is the name-index lookup on the second string-record table.
// Its table layout is shared with Rva00359330StringRecordRelease.cpp.

class AsciiString
{
};

class AsciiStringCompareShim
{
public:
	int compare( const AsciiString &other ) const;
};

struct Rva00359530Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359530StringRecordTable
{
public:
	int findRecordIndex( AsciiString *name );

private:
	int findNameIndex( AsciiString *name );

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00359530Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

int Rva00359530StringRecordTable::findRecordIndex( AsciiString *name )
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
