// Retail 0x004A8FC0: clear twenty entry flags and release live entries.

extern void j_0000bc49( void );
typedef void (*Rva004A8FC0Release)( void *, int );

class Rva004A8FC0
{
public:
	void clearEntries( void );

	char m_pad00[ 0x100 ];
	void *m_entries[ 20 ];
	char m_pad150[ 0xA0 ];
	int m_entryFlags[ 20 ];
};

void Rva004A8FC0::clearEntries( void )
{
	void **entries = m_entries;
	int i;

	for ( i = 20; i != 0; --i )
	{
		void *entry = *entries;
		((int *)entries)[ 0x3C ] = 0;
		if ( entry != 0 )
			((Rva004A8FC0Release)j_0000bc49)( entry, 0 );
		++entries;
	}
}
