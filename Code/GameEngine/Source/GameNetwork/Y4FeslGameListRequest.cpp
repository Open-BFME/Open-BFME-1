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

class Rva007E8810Message
{
public:
	void reset( void );                                              // 0x007E8AC0
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

	msg->reset();
	msg->m_category = 'GLST';
	msg->m_depth = 3;
	msg->addInt( "LID", lid );
	msg->addBool( "FILTER-FAV-ONLY", favOnly );
	msg->addBool( "FILTER-NOT-FULL", notFull );
	msg->addBool( "FILTER-NOT-PRIVATE", notPrivate );
	msg->addInt( "FILTER-MIN-SIZE", minSize );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "FILTER-ATTR-%s", attributes[ index ].m_key );
		msg->addString( key, attributes[ index ].m_value );
	}
	msg->addString( "FAV-PLAYER", favPlayer );
	msg->addString( "FAV-GAME", favGame );
	if( gid )
		msg->addInt( "GID", gid );
	msg->addInt( "COUNT", count );
	msg->addString( "FAV-PLAYER-UID", favPlayerUid );
	msg->addString( "FAV-GAME-UID", favGameUid );
}

void __stdcall Rva007FC290( Rva007E8810Message *msg, bool favOnly,
	bool notFull, bool notPrivate, int minSize,
	const Rva007FC3B0Filter *attributes, unsigned int numAttributes,
	const char *favPlayer, const char *favGame, const char *favPlayerUid,
	const char *favGameUid )
{
	unsigned int index;

	msg->reset();
	msg->m_category = 'LLST';
	msg->m_depth = 3;
	msg->addBool( "FILTER-FAV-ONLY", favOnly );
	msg->addBool( "FILTER-NOT-FULL", notFull );
	msg->addBool( "FILTER-NOT-PRIVATE", notPrivate );
	msg->addInt( "FILTER-MIN-SIZE", minSize );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "FILTER-ATTR-%s", attributes[ index ].m_key );
		msg->addString( key, attributes[ index ].m_value );
	}
	msg->addString( "FAV-PLAYER", favPlayer );
	msg->addString( "FAV-GAME", favGame );
	msg->addString( "FAV-PLAYER-UID", favPlayerUid );
	msg->addString( "FAV-GAME-UID", favGameUid );
}
