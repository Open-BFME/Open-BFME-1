// cl: /GS
#include <stdio.h>

// EA FESL client SDK ("jabba") -- the game-list ('GLST') query builder.
//
// Same SDK cluster and same message object as Y4FeslBuddyRequests.cpp.  This
// is the widest row in the span: fourteen __stdcall arguments, `ret 0x38`.
// Its literal keys are the whole filter vocabulary of the EA game browser --
// FILTER-FAV-ONLY, FILTER-NOT-FULL, FILTER-NOT-PRIVATE, FILTER-MIN-SIZE,
// FILTER-ATTR-%s, FAV-PLAYER, FAV-GAME, FAV-PLAYER-UID, FAV-GAME-UID -- which
// is the strongest single piece of evidence that 0x007F96C0..0x007FCF80 is the
// FESL browser/buddy client and not game code.
//
// The attribute filters are formatted one key per array element with sprintf
// into a 64-byte stack scratch, so the body carries a /GS cookie prologue and
// this TU needs its own `// cl: /GS`.  The attribute count is compared with
// `jbe`/`jb`, so it is UNSIGNED -- that is hard evidence and it differs from
// the otherwise identical loop in Y4FeslAttributeRequests.cpp, which uses
// signed `jle`/`jl`.

typedef __int64 FeslInt64;

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
	void addString( const char *key, const char *value );            // 0x007E8A10
	void addInt( const char *key, int value );                       // 0x007E88D0
	void addBool( const char *key, bool value );                     // 0x007E8980

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

struct Rva007FC3B0Filter
{
	const char *m_key;
	const char *m_value;
};

void __stdcall Rva007FC3B0( Rva007E8810Message *msg, int lid, bool favOnly,
	bool notFull, bool notPrivate, int minSize,
	const Rva007FC3B0Filter *attributes, unsigned int numAttributes,
	const char *favPlayer, const char *favGame, int gid, int count,
	const char *favPlayerUid, const char *favGameUid )
{
	unsigned int index;

	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'GLST';
	msg->m_depth = 3;
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"LID", (void *)( lid ) );
	( (Rva007E8980 *)msg )->go( (int)"FILTER-FAV-ONLY", favOnly );
	( (Rva007E8980 *)msg )->go( (int)"FILTER-NOT-FULL", notFull );
	( (Rva007E8980 *)msg )->go( (int)"FILTER-NOT-PRIVATE", notPrivate );
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"FILTER-MIN-SIZE", (void *)( minSize ) );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "FILTER-ATTR-%s", attributes[ index ].m_key );
		( (BfmeC994 *)msg )->addString( key, attributes[ index ].m_value );
	}
	( (BfmeC994 *)msg )->addString( "FAV-PLAYER", favPlayer );
	( (BfmeC994 *)msg )->addString( "FAV-GAME", favGame );
	if( gid )
		( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"GID", (void *)( gid ) );
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"COUNT", (void *)( count ) );
	( (BfmeC994 *)msg )->addString( "FAV-PLAYER-UID", favPlayerUid );
	( (BfmeC994 *)msg )->addString( "FAV-GAME-UID", favGameUid );
}

void __stdcall Rva007FC290( Rva007E8810Message *msg, bool favOnly,
	bool notFull, bool notPrivate, int minSize,
	const Rva007FC3B0Filter *attributes, unsigned int numAttributes,
	const char *favPlayer, const char *favGame, const char *favPlayerUid,
	const char *favGameUid )
{
	unsigned int index;

	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'LLST';
	msg->m_depth = 3;
	( (Rva007E8980 *)msg )->go( (int)"FILTER-FAV-ONLY", favOnly );
	( (Rva007E8980 *)msg )->go( (int)"FILTER-NOT-FULL", notFull );
	( (Rva007E8980 *)msg )->go( (int)"FILTER-NOT-PRIVATE", notPrivate );
	( (BfmeThingCIB *)msg )->bfmeGoCIB( (void *)"FILTER-MIN-SIZE", (void *)( minSize ) );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "FILTER-ATTR-%s", attributes[ index ].m_key );
		( (BfmeC994 *)msg )->addString( key, attributes[ index ].m_value );
	}
	( (BfmeC994 *)msg )->addString( "FAV-PLAYER", favPlayer );
	( (BfmeC994 *)msg )->addString( "FAV-GAME", favGame );
	( (BfmeC994 *)msg )->addString( "FAV-PLAYER-UID", favPlayerUid );
	( (BfmeC994 *)msg )->addString( "FAV-GAME-UID", favGameUid );
}
