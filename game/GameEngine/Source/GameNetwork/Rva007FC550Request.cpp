// cl: /GS
#include <stdio.h>
#include <string.h>

// Retail 0x007E8AC0 is matched as Rva007E8AC0::run (functions.csv).  This
// TU only calls that body through the message pointer, so it is spelled
// through its defining class; the same pattern is used in
// Common/Rva007F3980AttributeSerialize.cpp.
class Rva007E8AC0
{
public:
	void run( void );                                                // 0x007E8AC0
};

// The three writers are matched rows under other ledger spellings:
// 0x007E8A10 ?addString@BfmeC994, 0x007E88D0 ?bfmeGoCIB@BfmeThingCIB and
// 0x007E8980 ?go@Rva007E8980; the calls below go through those names.
class BfmeC994
{
public:
	void addString( const char *key, const char *value );
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *one, void *two );
};

class Rva007E8980
{
public:
	void go( int x, unsigned char f );
};

class Rva007E8810Message
{
public:
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
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'CGAM';
	msg->m_depth = 3;
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"RID", (void *)( rid ) );
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"LID", (void *)( lid ) );
	( (Rva007E8980 *)msg )->go( (int)"RESERVE-HOST", reserveHost );
	( (BfmeC994 *)msg )->addString( "NAME", name );
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"PORT", (void *)( port ) );
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"MAX-PLAYERS", (void *)( maxPlayers ) );
	if( password && strlen( password ) != 0 )
		( (BfmeC994 *)msg )->addString( "PASSWORD", password );
	if( userId )
	{
		( (BfmeC994 *)msg )->addString( "UGID", userId );
		( (BfmeC994 *)msg )->addString( "SECRET", secret );
	}
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "B-%s", attributes[ index ].m_key );
		( (BfmeC994 *)msg )->addString( key, attributes[ index ].m_value );
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
		( (BfmeC994 *)msg )->addString( "RESERVE-IDS", ids );
		( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"RESERVE-TIMEOUT", (void *)( reserveTimeout ) );
		((Rva007EFFC0Allocator *)bfmeGo929C())->release( ids, 0 );
	}
}
