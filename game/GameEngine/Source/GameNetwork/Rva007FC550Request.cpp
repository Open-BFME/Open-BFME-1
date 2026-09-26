// cl: /GS
#include <stdio.h>
#include <string.h>

class Rva007E8810Message
{
public:
	void reset( void );
	void addString( const char *key, const char *value );
	void addInt( const char *key, int value );
	void addBool( const char *key, bool value );

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

extern void *bfmeGo929C();

struct Rva007FC550Attribute
{
	const char *m_key;
	const char *m_value;
};

struct Rva007FC550Reservation
{
	__int64 m_id;
	int m_slot;
	int m_pad;
};

void __stdcall Rva007FC550( Rva007E8810Message *msg, int rid, int lid,
	bool reserveHost, const char *name, int port, int maxPlayers,
	const char *password, const Rva007FC550Attribute *attributes,
	unsigned int numAttributes, const Rva007FC550Reservation *reservations,
	unsigned int numReservations, int reserveTimeout, const char *userId,
	const char *secret )
{
	unsigned int index;
	msg->reset();
	msg->m_category = 'CGAM';
	msg->m_depth = 3;
	msg->addInt( "RID", rid );
	msg->addInt( "LID", lid );
	msg->addBool( "RESERVE-HOST", reserveHost );
	msg->addString( "NAME", name );
	msg->addInt( "PORT", port );
	msg->addInt( "MAX-PLAYERS", maxPlayers );
	if( password && strlen( password ) != 0 )
		msg->addString( "PASSWORD", password );
	if( userId )
	{
		msg->addString( "UGID", userId );
		msg->addString( "SECRET", secret );
	}
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "B-%s", attributes[ index ].m_key );
		msg->addString( key, attributes[ index ].m_value );
	}
	if( reservations && numReservations )
	{
		char *ids = (char *)((Rva007EFFC0Allocator *)bfmeGo929C())->allocate(
			numReservations * 0x23, 0 );
		char key[ 0x40 ];

		ids[ 0 ] = 0;
		unsigned int reservationIndex = 0;
		if( numReservations > 0 )
		{
			const Rva007FC550Reservation *reservation = reservations;
			do
			{
				sprintf( key, "%I64d", reservation->m_id );
				strcat( ids, key );
				strcat( ids, "-" );
				sprintf( key, "%d", reservation->m_slot );
				strcat( ids, key );
				if( reservationIndex < numReservations - 1 )
					strcat( ids, ";" );
				reservationIndex++;
				reservation++;
			} while( reservationIndex < numReservations );
		}
		msg->addString( "RESERVE-IDS", ids );
		msg->addInt( "RESERVE-TIMEOUT", reserveTimeout );
		((Rva007EFFC0Allocator *)bfmeGo929C())->release( ids, 0 );
	}
}
