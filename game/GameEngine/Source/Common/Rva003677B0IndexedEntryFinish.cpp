// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The retail body proves a [first,last) array of 0x58-byte entries at
// +0x18/+0x1C.  A valid signed index advances an entry from state 3 to state
// 4, then passes its +0x3C field and false to the entry operation.  The class
// and method names remain descriptive because no trustworthy higher-level
// identity is known.

class Rva003677B0Entry
{
public:
	void finish( void *value, bool enabled );

	char m_lead[ 0x20 ];
	int  m_state;
	char m_middle[ 0x18 ];
	char m_value;
	char m_tail[ 0x1B ];
};

class Rva003677B0EntryRange
{
public:
	unsigned int size() const { return m_last - m_first; }
	Rva003677B0Entry &operator[]( int index ) { return m_first[ index ]; }

private:
	Rva003677B0Entry *m_first;
	Rva003677B0Entry *m_last;
};

class Rva003677B0IndexedEntries
{
public:
	void finish( int index );

private:
	char m_lead[ 0x18 ];
	Rva003677B0EntryRange m_entries;
};

void Rva003677B0IndexedEntries::finish( int index )
{
	if( index < 0 || static_cast<unsigned int>( index ) >= m_entries.size() )
		return;

	Rva003677B0Entry &entry = m_entries[ index ];
	if( entry.m_state == 3 )
	{
		entry.m_state = 4;
		entry.finish( &entry.m_value, false );
	}
}
