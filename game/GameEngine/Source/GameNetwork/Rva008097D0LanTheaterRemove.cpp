// cl: /GX- /GS
// Retail 0x008097D0 / 450B: LAN-theater removal transaction.
// The matched 0x008036D0 caller supplies the transaction ID through the
// existing BfmeSinkTCA view. Preserve the observed message-payload store order
// with volatile accesses, matching the recovered BfmeC994 field view.

extern "C" void _WriteBarrier( void );
#pragma intrinsic( _WriteBarrier )

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class BfmeC994
{
public:
	BfmeC994( char *buffer, int capacity );
	void addInt( const char *key, int value );
	void clear();

	char *m_vft;
	int m_field04;
	int m_field08;
	int m_field0c;
	char *m_field10;
	int m_field14;
	int m_field18;
	unsigned int m_category;
	unsigned int m_field20;
	int m_field24;
	int m_field28;
	int m_field2c;
	char m_tail30;
};

class BfmeSinkSKA
{
public:
	void bfmeSendSKA( int category, int transactionId, int depth );
};

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expression, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();

class Rva007F93E0MessageSender
{
};

extern "C" void Rva0080F0D0( unsigned char *object );

void sendFeslMessage( void *message, const char *kind, void *owner );

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( unsigned int size, int flags );
	virtual void release( void *block, int flags );
};

Rva007EFFC0Allocator *Rva007EFFC0Get();

class Gen00809750
{
public:
	static void operator delete( void *block, unsigned int size );
};

struct Rva008097D0Player
{
	char m_pad00[ 4 ];
	int m_field04;
	int m_field08;
	int m_field0c;
	int m_playerId;
	int m_gameId;
};

struct Rva00808920LanGame
{
	~Rva00808920LanGame();

	int m_state;
	int m_maxPlayers;
	Rva008097D0Player **m_players;
	char m_name[ 0x80 ];
	char m_ugid[ 0x25 ];
	char m_tail[ 3 ];
};

Rva00808920LanGame::~Rva00808920LanGame()
{
	int index;
	Rva007E86B0Base *player;

	for ( index = 0; index < m_maxPlayers; ++index )
	{
		player = (Rva007E86B0Base *)m_players[ index ];
		if ( player != 0 )
		{
			player->Rva007E86B0Base::~Rva007E86B0Base();
			Gen00809750::operator delete( player, 0x38 );
		}
		m_players[ index ] = 0;
	}

	Rva007EFFC0Get()->release( m_players, 0 );
	m_players = 0;
}

static __forceinline Rva008097D0Player *Rva008097D0FindPlayer(
	const Rva00808920LanGame *game, int playerId )
{
	for ( int index = 0; index < game->m_maxPlayers; ++index )
	{
		Rva008097D0Player *player = game->m_players[ index ];
		if ( player != 0 && player->m_playerId == playerId )
			return player;
	}
	return 0;
}

class Rva008097D0Item
{
public:
	virtual void v0();
	virtual void v1();
	virtual int *getValue( int *value );
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual int isReady();
};

class Rva008097D0Registry
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual int count();
	virtual Rva008097D0Item *at( int index );
};

struct Rva008097D0Manager
{
	char m_pad00[ 0x2D8 ];
	Rva008097D0Registry *m_registry;
};

class Rva00808CB0Entry : public Rva007E86B0Base
{
public:
	int m_field08;
	int m_field0c;
	int m_field10;
	int m_field14;
	char m_tail18[ 8 ];
};

class BfmeSinkTCA
{
public:
	void bfmeUseTCA( void *value );

	char m_pad00[ 4 ];
	BfmeSinkSKA *m_sender;
	Rva008097D0Manager *m_manager;
	void *m_field0c;
	Rva007F93E0MessageSender *m_field10;
	char m_pad14[ 4 ];
	Rva00808CB0Entry *m_current;
	char m_pad1c[ 0x3C ];
	Rva00808920LanGame *m_game;
};

void BfmeSinkTCA::bfmeUseTCA( void *value )
{
	char buffer[ 0x40 ];
	Rva008097D0Registry *registry = m_manager->m_registry;

	for ( int index = 0; index < registry->count(); ++index )
	{
		Rva008097D0Item *item = registry->at( index );
		if ( item->isReady() )
		{
			int itemValue;
			int itemId = *item->getValue( &itemValue );
			Rva008097D0Player *player = Rva008097D0FindPlayer( m_game, itemId );
			if ( player == 0 )
			{
				Rva007EB810Get()->fail(
					"hlp",
					"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\lantheateremulator.cpp",
					0x1C9 );
			}
			else
			{
				BfmeC994 message( buffer, sizeof( buffer ) );
				message.m_category = 'GREM';
				message.addInt( "LID", -2 );
				message.addInt( "GID", player->m_gameId );
				*reinterpret_cast< volatile int * >( &message.m_field04 ) = player->m_field04;
				_WriteBarrier();
				*reinterpret_cast< volatile int * >( &message.m_field08 ) = *reinterpret_cast< volatile int * >( &player->m_field08 );
				const volatile int *field0c = &player->m_field0c;
				message.m_field0c = *field0c;
				sendFeslMessage( &message, "->L", m_field10 );
				message.clear();
			}
		}
	}

	Rva00808CB0Entry *current = m_current;
	if ( current != 0 )
	{
		if ( current->m_field14 != 0 )
			Rva007EFFC0Get()->release( (void *)current->m_field14, 0 );
		current->m_field14 = 0;
		current->m_field10 = 0;
		current->Rva007E86B0Base::~Rva007E86B0Base();
		Gen00809750::operator delete( current, 0x20 );
	}
	m_current = 0;

	if ( m_game != 0 )
	{
		Rva00808920LanGame *game = m_game;
		game->Rva00808920LanGame::~Rva00808920LanGame();
		Gen00809750::operator delete( game, 0xB4 );
	}
	m_game = 0;
	Rva0080F0D0( (unsigned char *)m_field0c );
	BfmeSinkSKA *sender = m_sender;
	sender->bfmeSendSKA( 'RGAM', (int)value, 0 );
}
