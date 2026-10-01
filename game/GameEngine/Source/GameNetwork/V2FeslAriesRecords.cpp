// EA FESL client SDK ("jabba") -- Aries record constructors.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp; see that file's head
// comment for how the span was identified (the assert path
// \views\feslbuild_main\jabba\fesl\source\ariesudp.cpp) and for the message
// object at RVA 0x007E8810 whose accessors every row here calls.
//
// WHAT THE BYTES SHOW.  Every row is __thiscall, takes ONE pointer argument,
// returns `this` in eax and ends `ret 4` -- the MSVC shape of a constructor.
// Each fills its object entirely out of the message by key:
//     getInt   ( key, defaultValue )        RVA 0x007E8900, returns int
//     getString( key, dest, destSize )      RVA 0x007E8A80, returns bool
//     getInt64 ( key, defaultValue )        RVA 0x007E8930, returns __int64
// The BUFFER SIZES are immediates with no relocation, so every char array
// length below (0x80, 0x40, 0x400, 0x25, 0x100, 0x20, 8) is hard evidence, as
// is every member OFFSET -- each is either an `lea this+N` handed to getString
// or a `mov [this+N],eax` taking a getInt result.  The key spellings are the
// pushed literals and are real; the C++ member names are not.
//
// Three rows (0x007F5010, 0x007F5080, 0x007F5120) open with a __thiscall call
// to RVA 0x007FBC30 passing the same message pointer, before touching anything
// at or above offset 8.  RVA 0x007FBC30 is itself a two-field constructor of
// this same shape (LID at +0, GID at +4), so that call is a BASE constructor
// and those three objects start with its eight bytes.  It lives outside this
// file's span and is only declared and pinned here, never defined.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names any of these record types or
// the fields whose keys are numeric ("QPOS", "QLEN").  All class and member
// names are address- or key-derived.  0x007F41B0 and 0x007F4E20 are the same
// two-field body under two different keys; the bytes do not say they are
// related types.

typedef __int64 FeslInt64;

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class BfmeThingRF
{
public:
	void *bfmeGoRF( void *one, void *two );                       // 0x007E8900
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *one, char *out, void *two );            // 0x007E8A80
};

class Rva007E8810Message
{
public:
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );   // 0x007E8930
};

// ---------------------------------------------------------------- two-field
class Rva007F41B0Reason
{
public:
	Rva007F41B0Reason( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	int m_reason;
};

Rva007F41B0Reason::Rva007F41B0Reason( Rva007E8810Message *msg )
{
	m_msg = msg;
	m_reason = (int)(long)reinterpret_cast< BfmeThingRF * >( m_msg )->bfmeGoRF( (void *)"reason", (void *)0 );
}

class Rva007F4E20RegionCount
{
public:
	Rva007F4E20RegionCount( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	int m_numRegions;
};

Rva007F4E20RegionCount::Rva007F4E20RegionCount( Rva007E8810Message *msg )
{
	m_msg = msg;
	m_numRegions = (int)(long)reinterpret_cast< BfmeThingRF * >( m_msg )->bfmeGoRF( (void *)"NUM-REGIONS", (void *)0 );
}

// ------------------------------------------------------------ endpoint pair
class Rva007F4130Endpoints
{
public:
	Rva007F4130Endpoints( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	char m_theaterIp[ 0x40 ];
	char m_messengerIp[ 0x40 ];
	char m_addressRemapping[ 0x400 ];
	int m_theaterPort;
	int m_messengerPort;
};

Rva007F4130Endpoints::Rva007F4130Endpoints( Rva007E8810Message *msg )
{
	m_msg = msg;
	m_theaterPort = (int)(long)reinterpret_cast< BfmeThingRF * >( m_msg )->bfmeGoRF( (void *)"theaterPort", (void *)0 );
	m_messengerPort = (int)(long)reinterpret_cast< BfmeThingRF * >( m_msg )->bfmeGoRF( (void *)"messengerPort", (void *)0 );
	reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)"theaterIp", m_theaterIp, (void *)0x40 );
	reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)"messengerIp", m_messengerIp, (void *)0x40 );
	reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)"addressRemapping", m_addressRemapping, (void *)0x400 );
}

// ------------------------------------------------------------------- region
class Rva007F4E50Region
{
public:
	Rva007F4E50Region( Rva007E8810Message *msg );
	int m_rid;
	int m_numGames;
	int m_numPlayers;
	char m_name[ 0x80 ];
	char m_locale[ 8 ];
};

Rva007F4E50Region::Rva007F4E50Region( Rva007E8810Message *msg )
{
	m_rid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"RID", (void *)0 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"NAME", m_name, (void *)0x80 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"LOCALE", m_locale, (void *)8 );
	m_numGames = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"NUM-GAMES", (void *)0 );
	m_numPlayers = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"NUM-PLAYERS", (void *)0 );
}

// -------------------------------------------------------------------- lobby
class Rva007F4EF0Lobby
{
public:
	Rva007F4EF0Lobby( Rva007E8810Message *msg );
	int m_lid;
	int m_passing;
	int m_favoriteGames;
	int m_favoritePlayers;
	int m_maxGames;
	int m_numGames;
	char m_name[ 0x80 ];
	char m_locale[ 8 ];
};

Rva007F4EF0Lobby::Rva007F4EF0Lobby( Rva007E8810Message *msg )
{
	m_lid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"LID", (void *)0 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"NAME", m_name, (void *)0x80 );
	m_passing = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"PASSING", (void *)0 );
	m_favoriteGames = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"FAVORITE-GAMES", (void *)0 );
	m_favoritePlayers = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"FAVORITE-PLAYERS", (void *)0 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"LOCALE", m_locale, (void *)8 );
	m_maxGames = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"MAX-GAMES", (void *)0 );
	m_numGames = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"NUM-GAMES", (void *)0 );
}

class Rva007F4F90LobbyCounts
{
public:
	Rva007F4F90LobbyCounts( Rva007E8810Message *msg );
	int m_numGames;
	int m_lid;
	int m_lobbyMaxGames;
	int m_lobbyNumGames;
};

Rva007F4F90LobbyCounts::Rva007F4F90LobbyCounts( Rva007E8810Message *msg )
{
	m_numGames = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"NUM-GAMES", (void *)0 );
	m_lid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"LID", (void *)0 );
	m_lobbyMaxGames = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"LOBBY-MAX-GAMES", (void *)0 );
	m_lobbyNumGames = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"LOBBY-NUM-GAMES", (void *)0 );
}

// ------------------------------------------------------------- ticket record
class Rva007F51D0Ticket
{
public:
	Rva007F51D0Ticket( Rva007E8810Message *msg );
	int m_pid;
	FeslInt64 m_uid;
	int m_port;
	char m_name[ 0x80 ];
	char m_ip[ 0x20 ];
	char m_ticket[ 0x80 ];
};

Rva007F51D0Ticket::Rva007F51D0Ticket( Rva007E8810Message *msg )
{
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"NAME", m_name, (void *)0x80 );
	m_uid = msg->getInt64( "UID", 0 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"IP", m_ip, (void *)0x20 );
	m_pid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"PID", (void *)0 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"TICKET", m_ticket, (void *)0x80 );
	m_port = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"PORT", (void *)0 );
}

// ------------------------------------- LID/GID base and the three rows on it
class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey( Rva007E8810Message *msg );                    // 0x007FBC30
	int m_lid;
	int m_gid;
};

class Rva007F5010Player : public Rva007FBC30GameKey
{
public:
	Rva007F5010Player( Rva007E8810Message *msg );
	Rva007E8810Message *m_msg;
	int m_pid;
	char m_name[ 0x80 ];
	FeslInt64 m_uid;
};

Rva007F5010Player::Rva007F5010Player( Rva007E8810Message *msg )
	: Rva007FBC30GameKey( msg )
{
	m_msg = msg;
	m_pid = (int)(long)reinterpret_cast< BfmeThingRF * >( m_msg )->bfmeGoRF( (void *)"PID", (void *)0 );
	reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)"NAME", m_name, (void *)0x80 );
	m_uid = m_msg->getInt64( "UID", 0 );
}

class Rva007F5080Game : public Rva007FBC30GameKey
{
public:
	Rva007F5080Game( Rva007E8810Message *msg );
	int m_maxPlayers;
	char m_ugid[ 0x25 ];
	char m_secret[ 0x80 ];
	int m_lobbyId;
	int m_gameId;
};

Rva007F5080Game::Rva007F5080Game( Rva007E8810Message *msg )
	: Rva007FBC30GameKey( msg )
{
	m_maxPlayers = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"MAX-PLAYERS", (void *)0 );
	m_lobbyId = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"LID", (void *)0 );
	m_gameId = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"GID", (void *)0 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"SECRET", m_secret, (void *)0x80 );
	reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"UGID", m_ugid, (void *)0x25 );
}

class Rva007F5120Queue : public Rva007FBC30GameKey
{
public:
	Rva007F5120Queue( Rva007E8810Message *msg );
	char m_reason[ 0x100 ];
	int m_qpos;
	int m_qlen;
};

Rva007F5120Queue::Rva007F5120Queue( Rva007E8810Message *msg )
	: Rva007FBC30GameKey( msg )
{
	if( !reinterpret_cast< BfmeThingUPB * >( msg )->bfmeGoUPB( (void *)"REASON", m_reason, (void *)0x100 ) )
		m_reason[ 0 ] = 0;
	m_qpos = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"QPOS", (void *)0 );
	m_qlen = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"QLEN", (void *)0 );
}
