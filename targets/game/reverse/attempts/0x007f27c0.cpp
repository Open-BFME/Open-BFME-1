// ?build@Rva007F27C0Host@@QAEXPAVRva007E8810Message@@PBDPBURva007F27C0User@@H@Z
// partial score=0.3 date=2026-09-16
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

	char m_head[ 0x1C ];
	unsigned int m_category;
};

struct Rva007F27C0Stat
{
	int userType;
	const char *key;
	float value;
	const char *text;
};

struct Rva007F27C0UserHeader
{
	FeslInt64 owner;
	int ownerType;
	int field0C;
};

struct Rva007F27C0UserData
{
	int statCount;
	Rva007F27C0Stat *stats;
};

struct Rva007F27C0User
{
	Rva007F27C0UserHeader header;
	Rva007F27C0UserData data;
};

class Rva007F27C0Host
{
public:
	void build( Rva007E8810Message *msg, const char *gsid,
		const Rva007F27C0User *users, int userCount );
};

void Rva007F27C0Host::build( Rva007E8810Message *msg, const char *gsid,
	const Rva007F27C0User *users, int userCount )
{
	register Rva007E8810Message *message;
	register const char *txn;
	char name[ 0x40 ];
	char value[ 0x40 ];
	int i;

	message = msg;
	txn = *(const char * const *)0x0130A690;
	message->reset();
	message->m_category = 'rank';
	message->addString( "TXN", txn );
	message->addString( "gsid", gsid );
	for( i = 0; i < userCount; ++i )
	{
		const Rva007F27C0UserData *data = &users[ i ].data;
		const Rva007F27C0UserHeader *header =
			(const Rva007F27C0UserHeader *)( (const char *)data - 0x10 );
		FeslInt64 owner = header->owner;
		int ownerType = header->ownerType;
		int field0C = *(volatile int *)&header->field0C;

		if( owner )
		{
			sprintf( name, "u.%d.o", i );
			message->addInt64( name, owner );
			sprintf( name, "u.%d.ot", i );
			message->addInt( name, ownerType );
		}

		{
			int j;
			int statOffset = 0;
			for( j = 0; j < data->statCount; ++j )
			{
				const Rva007F27C0Stat *stat =
					(const Rva007F27C0Stat *)( (const char *)data->stats + statOffset );

				sprintf( name, "u.%d.s.%d.ut", i, j );
				message->addInt( name, stat->userType );
				sprintf( name, "u.%d.s.%d.k", i, j );
				message->addString( name, stat->key );
				sprintf( name, "u.%d.s.%d.v", i, j );
				sprintf( value, "%.4f", stat->value );
				message->addString( name, value );
				sprintf( name, "u.%d.s.%d.t", i, j );
				message->addString( name, stat->text );
				statOffset += 0x10;
			}
		}

		sprintf( name, "u.%d.s.[]", i );
		message->addInt( name, data->statCount );
	}
	message->addInt( "u.[]", userCount );
}
