// cl: /GX- /GS
// Retail 0x00809100 is the two-integer sink reached by the matched
// BfmeHostSA::bfmeGoSA body at 0x008037A0.  That caller reads TID and PID
// through the complete signed-decimal FESL getter at 0x007E8900.
//
// The owner is the LAN theater emulator: its +0x58 object is the same LAN
// game allocated by the matched 0x00808CB0 sink.  The game's complete
// constructor at 0x00808920 establishes the count at +4 and pointer array at
// +8.  The inline search is the counted-pointer shape independently matched
// at 0x00808E60; each non-null player is selected by its +0x10 integer.
// BfmeC994's matched constructor starts with the 0x007E86B0 base constructor;
// the terminal 0x007E86C0 call installs that same base vtable.  Modeling the
// actual base and an implicit derived destructor gives the observed cleanup as
// a normal stack-object lifetime, without an explicit pseudo-clear call.

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

class BfmeC994 : public Rva007E86B0Base
{
public:
	BfmeC994( char *buffer, int capacity );
	void addInt( const char *key, int value );

	char m_pad08[ 0x14 ];
	unsigned int m_category;
	unsigned int m_field20;
	char m_tail24[ 0x10 ];
};

class Rva008038F0Sender
{
public:
	void send( BfmeC994 *message );
};

struct Rva00809100Player
{
	char m_pad00[ 0x10 ];
	int m_pid;
};

class Rva00808920LanGame
{
public:
	int m_state;
	int m_maxPlayers;
	Rva00809100Player **m_players;
};

static __forceinline Rva00809100Player *Rva00809100FindPlayer(
	const Rva00808920LanGame *game, int pid )
{
	for( int index = 0; index < game->m_maxPlayers; ++index )
	{
		Rva00809100Player *player = game->m_players[ index ];
		if( player != 0 && player->m_pid == pid )
			return player;
	}
	return 0;
}

class BfmeSinkSA
{
public:
	void bfmeUseSA( int tid, int pid );

	char m_pad00[ 4 ];
	Rva008038F0Sender *m_sender;
	char m_pad08[ 0x50 ];
	Rva00808920LanGame *m_game;
};

void BfmeSinkSA::bfmeUseSA( int tid, int pid )
{
	char buffer[ 0x40 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	Rva00809100Player *player = Rva00809100FindPlayer( m_game, pid );

	message.m_category = 'PENT';
	message.m_field20 = player != 0 ? 0 : 'ntfn';
	message.addInt( "TID", tid );
	message.addInt( "PID", pid );
	m_sender->send( &message );
}
