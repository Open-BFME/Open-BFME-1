// cl: /O2 /GX- /GS
// Retail 0x00808CB0 is the five-argument sink reached by the matched
// Rva00803620Host::go body.  That caller obtains TID, PORT, and MAX-PLAYERS
// through the signed-decimal parser at 0x007EE720, so those values are ints.
// The surviving assertion and source path identify m_lanGames[0] and the
// lantheateremulator.cpp owner without assigning a public name that does not
// survive in the image.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Rva007EFFC0Allocator;

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual int v2();
};

// Retail uses EDX for the allocator table at slot +8.
// This fastcall view keeps the table in EDX while size and flags stay on the stack.
typedef void *(__fastcall *Rva007EFFC0AllocateSlot)(
	Rva007EFFC0Allocator *, void *, unsigned int, int);

void *bfmeGo929C(void);
Rva007E9B70Obj *Rva007E9B70Get();

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

class Rva007E86B0Base : public Gen007F0130
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
	__forceinline Rva00808CB0LanGameEntry( int sequence )
	{
		m_field08 = 0;
		m_field0c = 0;
		m_field04 = 0;
		m_sequence = sequence;
		m_field14 = 0;
	}

	int m_field08;
	int m_field0c;
	int m_sequence;
	int m_field14;
	char m_tail18[ 8 ];
};

class Rva00808920LanGame : public Gen007F0130
{
public:
	Rva00808920LanGame( int maxPlayers );

	int m_state;
	int m_maxPlayers;
	void **m_players;
	char m_name[ 0x80 ];
	char m_ugid[ 0x25 ];
	char m_tailb1[ 3 ];
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();

class Rva007EA650FieldAddress
{
public:
	char *get();
};

struct Rva00808CB0Browser
{
	char m_pad00[ 0x0c ];
	Rva007EA650FieldAddress *m_address;
};

struct Rva00808CB0Advert;

extern "C" void Rva0080EF50( Rva00808CB0Advert *advert,
	const char *address, char *name, const char *port );

void Rva007E8640Copy( char *dest, unsigned int size, const char *source );

class Rva00803620Sink
{
public:
	void apply( int tid, char *name, int port, int maxPlayers, char *ugid );

	char m_pad00[ 0x08 ];
	Rva00808CB0Browser *m_browser;
	Rva00808CB0Advert *m_advert;
	int m_field10;
	int m_nextLanGameId;
	Rva00808CB0LanGameEntry *m_lanGames[ 16 ];
	Rva00808920LanGame *m_game;
	char m_pad5c[ 0x110 ];
	int m_tid;
};

void Rva00803620Sink::apply( int tid, char *name, int port,
	int maxPlayers, char *ugid )
{
	if( m_lanGames[ 0 ] != 0 )
	{
		Rva007EB810Get()->fail(
			"!mLanGames[0]",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
			0x196 );
	}

	m_lanGames[ 0 ] = new Rva00808CB0LanGameEntry( ++m_nextLanGameId );
	m_game = new Rva00808920LanGame( maxPlayers );
	strncpy( m_game->m_name, name, sizeof( m_game->m_name ) );

	if( ugid != 0 && strlen( ugid ) != 0 )
		Rva007E8640Copy( m_game->m_ugid, sizeof( m_game->m_ugid ), ugid );

	char portText[ 0x100 ];
	sprintf( portText, "%d", port );
	Rva007EA650FieldAddress *address = m_browser->m_address;
	Rva0080EF50( m_advert, address->get(), name, portText );
	m_tid = tid;
}

Rva00808920LanGame::Rva00808920LanGame( int maxPlayers )
{
	m_state = 1;
	m_maxPlayers = maxPlayers;
	Rva007EFFC0Allocator *allocator = (Rva007EFFC0Allocator *)bfmeGo929C();
	m_players = (void **)((Rva007EFFC0AllocateSlot)(*(void ***)allocator)[2])(
		allocator, *(void ***)allocator, m_maxPlayers * 4, 0);
	for( int index = 0; index < m_maxPlayers; ++index )
		m_players[ index ] = 0;

	char text[ 0x24 ];
	int value = Rva007E9B70Get()->v2() * rand() * m_maxPlayers;
	sprintf( text, "%032x", value );
	memset( m_ugid, 0, 0x25 );
	strncpy( m_ugid, text, 8 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 8, 4 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 12, 4 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 16, 4 );
	strcat( m_ugid, "-" );
	strncat( m_ugid, text + 20, 12 );
	m_ugid[ 0x24 ] = 0;
}
