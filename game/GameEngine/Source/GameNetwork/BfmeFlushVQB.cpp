// 0x007FAAB0: FESL service-hub flush over four pending records.

class Rva00803080;

class Rva007EAServiceList
{
public:
	void remove( Rva00803080 *owner );
};

struct BfmeFlushVQBItem;

struct BfmeFlushVQBRecord
{
	void (__cdecl *m_flush)( void *, void *, int );
	void *m_first;
	void *m_second;
	BfmeFlushVQBItem *m_item;
};

struct BfmeFlushVQBItem
{
	void *m_unused;
	int m_value;
	int (*m_ready)( BfmeFlushVQBItem * );
	void (*m_release)( BfmeFlushVQBItem * );
};

class BfmeHubVQB
{
public:
	void bfmeFlushVQB( int unused );

	private:
		int m_padding;
		BfmeFlushVQBRecord m_records[ 4 ];
		int m_count;
		Rva007EAServiceList *m_services;
};

void BfmeHubVQB::bfmeFlushVQB( int unused )
{
	for ( int i = 0; i < 4; ++i )
	{
		BfmeFlushVQBRecord &record = m_records[ i ];
		if ( record.m_flush == 0 || record.m_item == 0 ||
			!record.m_item->m_ready( record.m_item ) )
			continue;

		if ( --m_count < 1 )
			m_services->remove( (Rva00803080 *)((int)this - 4 != 0 ? (int)this : 0) );

		volatile BfmeFlushVQBItem *item = record.m_item;
		record.m_flush( record.m_first, record.m_second, item->m_value );
		record.m_item->m_release( record.m_item );
		record.m_flush = 0;
		record.m_first = 0;
		record.m_second = 0;
		record.m_item = 0;
	}
}
