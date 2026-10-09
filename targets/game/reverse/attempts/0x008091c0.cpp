// ?d_008091c0@@YAXXZ
// partial score=0.4072 date=2026-10-09
// cl: /O2 /GX- /GS
// The owner and attribute offsets are taken from the matched dispatcher and
// player-data neighbours.  Unknown private fields retain address-derived names.

#include <stdio.h>

class BfmeC994
{
public:
	void addString( const char *key, const char *value );
};

class BfmeThingCIB {
public: void bfmeGoCIB(void *key, void *value);
};

class Energy
{
};

class Player
{
public:
	Energy *getEnergy();
};

struct Rva008091C0Attribute
{
	const char *m_key;
	int m_tag;
};

struct Rva008091C0Attributes
{
	__forceinline const Rva008091C0Attribute *at( int index ) const
	{
		if( index >= m_count )
			return 0;
		return m_data + index;
	}

	Rva008091C0Attribute *m_data;
	int m_count;
};

class Rva00802040Owner
{
public:
	virtual void slot00();
	virtual void *valueForKey( const char *key );
	void rva00801ae0( int *outMatches, int *outOther );
};

struct Rva008091C0OwnerData
{
	char m_pad00[ 0x0c ];
	Player *m_player;
	char m_pad10[ 0x18 ];
	void *m_field28;
	void *m_field2c;
	char m_pad30[ 0x278 ];
	Rva008091C0Attributes m_attributes;
	char m_pad2b0[ 0x28 ];
	Rva00802040Owner *m_registry;
};

struct Rva008091C0Game
{
	char m_pad00[ 4 ];
	int m_maxPlayers;
	char m_pad08[ 0x20 ];
	void *m_field28;
	void *m_field2c;
};

class Rva008091C0Owner
{
public:
	void handle( BfmeC994 *message, int gid, char *name );

	void *m_vtable;
	int m_registrationValue;
	Rva008091C0OwnerData *m_owner;
	char m_pad0c[ 0x4c ];
	Rva008091C0Game *m_game;
	char m_pad5c[ 0x118 ];
	char m_field174;
};

void Rva008091C0Owner::handle( BfmeC994 *message, int gid, char *name )
{
	Rva00802040Owner *registry = m_owner->m_registry;
	((BfmeThingCIB*)message)->bfmeGoCIB( (void *)"LID", (void *)-2 );
	((BfmeThingCIB*)message)->bfmeGoCIB( (void *)"GID", (void *)gid );
	message->addString( "V", (const char *)m_owner->m_player->getEnergy() );
	message->addString( "N", (char *)m_game + 0x0c );
	((BfmeThingCIB*)message)->bfmeGoCIB( (void *)"MP", (void *)m_game->m_maxPlayers );
	message->addString( "I", name );

	void *value = m_owner->m_field2c != 0
		? m_owner->m_field2c : m_owner->m_field28;
	((BfmeThingCIB*)message)->bfmeGoCIB( (void *)"P", value );
	message->addString( "HN", &m_field174 );

	int matches;
	int other;
	registry->rva00801ae0( &matches, &other );
	((BfmeThingCIB*)message)->bfmeGoCIB( (void *)"AP", (void *)matches );
	((BfmeThingCIB*)message)->bfmeGoCIB( (void *)"JP", (void *)other );

	Rva008091C0Attributes *attributes = &m_owner->m_attributes;
	int count = attributes->m_count;
	for( int index = 0; index < count; ++index )
	{
		char key[ 0x40 ];
		const char *attribute = attributes->at( index )->m_key;
		sprintf( key, "B-%.60s", attribute );
		message->addString( key, (const char *)registry->valueForKey( attribute ) );
	}
}
