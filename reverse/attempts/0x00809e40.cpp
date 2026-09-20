// ?d_00809e40@@YAXXZ
// partial score=0.31 date=2026-09-20
// cl: /O2 /GX- /GS
// Retail 0x00809E40: FESL game-browser record admission and request.

#include <new>

extern "C" __declspec( dllimport ) char *__cdecl strncpy(
	char *destination, const char *source, unsigned int count );
#pragma intrinsic( strncpy )

class BfmeC994
{
public:
	BfmeC994( char *buffer, int capacity );
	void addInt( const char *key, int value );
	void addString( const char *key, const char *value );

	char m_pad00[ 4 ];
	int m_field04;
	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_category;
	int m_field20;
	char m_pad24[ 0x0c ];
	char m_tail30;
};

class Gen_007e86c0
{
public:
	void m();
};

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );
	bool getString( const char *key, char *out, int capacity );

	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_category;
};

class Rva00802040Owner;

class Rva00802680Owner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual int getIndex();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
};

class Rva00802040Owner
{
public:
	Rva00802680Owner *findFree();
};

class Rva008038F0Sender
{
public:
	void send( BfmeC994 *message );
};

class Rva00809E40Record;

class Rva00808920LanGame
{
public:
	int m_state;
	int m_maxPlayers;
	Rva00809E40Record **m_players;
};

class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class Energy : public SnapshotDupReplica
{
public:
	Energy();

	void *m_owner;
	int m_energyProduction;
	int m_energyConsumption;
	int m_powerSabotagedTillFrame;
};

class Rva00809E40Record : public Energy
{
public:
	int m_field14;
	char m_field18[ 0x20 ];
};

struct Rva00809E40State
{
	char m_pad00[ 0x2d8 ];
	Rva00802040Owner *m_manager;
};

class Rva00809E40Owner
{
public:
	void rva00809E40( Rva007E8810Message *input );

	char m_pad00[ 4 ];
	Rva008038F0Sender *m_sender;
	Rva00809E40State *m_state;
	char m_pad0c[ 4 ];
	void *m_routeOwner;
	char m_pad14[ 0x44 ];
	Rva00808920LanGame *m_game;
};

struct Rva007EB810Diag
{
	virtual void v00();
	virtual void report( const char *text );
	virtual void v08();
	virtual void fail( const char *expression, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();
void *Rva007F93E0( void *message, void *route, void *owner );
extern int g_bfmeKeyVHE;

class Gen007F0130
{
public:
	static void *operator new( unsigned int size );
};

void Rva00809E40Owner::rva00809E40( Rva007E8810Message *input )
{
	char buffer[ 0x40 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	message.m_category = input->m_category;
	void *value = (void *)( long )input->getInt(
		(const char *)&g_bfmeKeyVHE, -1 );
	if( value != (void *)-1 )
		message.addInt( (const char *)&g_bfmeKeyVHE, (int)( long )value );

	message.m_field04 = input->m_field04;
	message.m_field08 = input->m_field08;
	message.m_field0c = input->m_field0c;

	Rva00809E40State *state = m_state;
	if( state->m_manager == 0 )
	{
		message.m_field20 = 'ngam';
		Rva007F93E0( &message, (void *)0x0112C7C0, m_routeOwner );
		reinterpret_cast< Gen_007e86c0 * >( &message )->m();
		return;
	}

	Rva00802680Owner *slot = state->m_manager->findFree();
	if( slot == 0 )
	{
		message.m_field20 = 'jden';
		Rva007EB810Get()->report( (const char *)0x0112C8B8 );
		message.addString(
			(const char *)0x0112B588, (const char *)0x0112C89C );
		Rva007F93E0( &message, (void *)0x0112C7C0, m_routeOwner );
		reinterpret_cast< Gen_007e86c0 * >( &message )->m();
		return;
	}

	int index = slot->getIndex();
	Rva00808920LanGame *game = m_game;
	if( game->m_players[ index ] != 0 )
		Rva007EB810Get()->fail(
			(const char *)0x0112C878,
			(const char *)0x0112C7D8,
			0x307 );

	void *raw = Gen007F0130::operator new( 0x38 );
	Rva00809E40Record *record = raw != 0
		? new( raw ) Rva00809E40Record
		: (Rva00809E40Record *)0;
	((Rva00809E40Record **)game->m_players)[ index ] = record;
	record->m_owner = (void *)( long )input->m_field04;
	record->m_energyProduction = input->m_field08;
	record->m_energyConsumption = input->m_field0c;
	record->m_powerSabotagedTillFrame = game->m_state++;
	record->m_field14 = reinterpret_cast< Rva007E8810Message * >( input )->getInt(
		(const char *)0x0112B568, 0 );
	Rva007F93E0( &message, (void *)0x0112C7C0, m_routeOwner );

	{
		char first[ 0x20 ];
		input->getString( (const char *)0x010F91BC, first, 0x20 );
		{
			char second[ 0x20 ];
			input->getString( (const char *)0x01102DE0, second, 0x20 );
			strncpy( record->m_field18, second, 0x20 );
		}

		BfmeC994 request( buffer, sizeof( buffer ) );
		request.m_category = 'RQGE';
		request.addString( (const char *)0x010F91BC, first );
		request.addInt( (const char *)0x0112B554, record->m_field14 );
		request.addString( (const char *)0x0112B590, (const char *)0x01118E50 );
		m_sender->send( &request );
		reinterpret_cast< Gen_007e86c0 * >( &request )->m();
	}
	reinterpret_cast< Gen_007e86c0 * >( &message )->m();
}
