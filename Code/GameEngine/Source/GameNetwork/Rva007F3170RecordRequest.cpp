// cl: /GS

#include <stdio.h>

// Retail 0x007F3170 builds the FESL `recp` record request. The owner layout,
// field keys, and two indexed arrays come from the retail loads and literals.

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset( void );
	void addString( const char *key, const char *value );
	void addInt( const char *key, int value );
	void addInt64( const char *key, FeslInt64 value );
	void setError( int code );

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

struct Rva007F3170Owner
{
	FeslInt64 owner;
	int ownerType;
};

struct Rva007F3170Value
{
	const char *key;
	const char *value;
};

extern const char * const g_Rva0130A6E4;

void __stdcall Rva007F3170( Rva007E8810Message *msg,
	const Rva007F3170Owner *owner, const char *recordName,
	const Rva007F3170Value *values, unsigned int count, int ttl,
	const char * const *remove, unsigned int removeCount )
{
	const char *txn = g_Rva0130A6E4;
	unsigned int i;
	const Rva007F3170Value *entries = values;

	msg->reset();
	msg->m_category = 'recp';
	msg->addString( "TXN", txn );
	if( owner )
	{
		if( owner->ownerType == 1 )
		{
			msg->addInt64( "owner", owner->owner );
			msg->addInt( "ownerType", owner->ownerType );
		}
		else
		{
			msg->setError( -113 );
			return;
		}
	}
	msg->addString( "recordName", recordName );
	msg->addInt( "values.[]", count );
	for( i = 0; i < count; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "values.%d.key", i );
		msg->addString( key, entries[ i ].key );
		sprintf( key, "values.%d.value", i );
		msg->addString( key, entries[ i ].value );
	}
	msg->addInt( "TTL", ttl );
	msg->addInt( "remove.[]", removeCount );
	for( i = 0; i < removeCount; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "remove.%d", i );
		msg->addString( key, remove[ i ] );
	}
}
