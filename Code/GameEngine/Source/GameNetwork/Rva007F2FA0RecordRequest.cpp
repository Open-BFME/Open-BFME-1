// cl: /GS

#include <stdio.h>

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

struct Rva007F2FA0Owner
{
	FeslInt64 owner;
	int ownerType;
};

struct Rva007F2FA0Value
{
	const char *key;
	const char *value;
};

extern const char * const g_Rva0130A6CC;

void __stdcall Rva007F2FA0( Rva007E8810Message *msg,
	const Rva007F2FA0Owner *owner, const char *recordName,
	const Rva007F2FA0Value *values, unsigned int count, int ttl )
{
	const char *txn = g_Rva0130A6CC;
	unsigned int i;
	const Rva007F2FA0Value *entries = values;

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
}

// ?Rva007F2FA0@@YGXPAVRva007E8810Message@@PBURva007F2FA0Owner@@PBDPBURva007F2FA0Value@@IH@Z
