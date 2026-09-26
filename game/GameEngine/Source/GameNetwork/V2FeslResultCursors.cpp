// cl: /GS
// EA FESL client SDK ("jabba") -- indexed result-set cursors and the two
// request builders that format indexed keys.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp / V2FeslAriesRecords.cpp;
// see the first of those for how the span was identified (the assert path
// \views\feslbuild_main\jabba\fesl\source\ariesudp.cpp) and for the message
// object at RVA 0x007E8810 that every row here drives.
//
// WHAT THE BYTES SHOW, AND WHY THIS FILE CARRIES ITS OWN FLAG.  Every row here
// opens by loading the dword at 0x012DBDB0 into the frame slot immediately
// above its locals, and ends by passing that slot in ecx to RVA 0x009F74F4.
// That is MSVC 7.1's /GS stack-cookie prologue and __security_check_cookie
// epilogue.  /GS is not on the command line the rest of the binary was built
// with, so these bodies need their own translation unit -- and the rows that
// need it are exactly the ones with a local char buffer, which is what /GS
// instruments.  The `// cl:` line above is the claim those bytes force.
//
// THE SHAPE.  A cursor holds the message pointer at +0x00 and a running index;
// each `next` formats that index into a stack buffer with sprintf, looks the
// resulting key up in the message, and advances the index only on success.
// The index OFFSET differs per cursor (+0x2C, +0x24, +0x58) and each offset is
// a plain displacement, not a relocation -- so those really are three distinct
// types, not one type seen three times.
//
// Buffer sizes are immediates (0x40, 0x20, 0xFF, 0x40) and member offsets are
// displacements, so both are hard evidence.  Key spellings are the pushed
// literals and are real.  Class and member NAMES are address- or key-derived;
// nothing in the bytes names any of these types.

#include <stdio.h>

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset( void );                                              // 0x007E8AC0
	void addString( const char *key, const char *value );            // 0x007E8A10
	void addInt( const char *key, int value );                       // 0x007E88D0
	void addInt64( const char *key, FeslInt64 value );               // 0x007E8E90
	int getInt( const char *key, int defaultValue );                 // 0x007E8900
	bool getString( const char *key, char *dest, int destSize );     // 0x007E8A80
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );   // 0x007E8930

	char m_head[ 0x1C ];
	unsigned int m_category;
};

// The 12-byte owner descriptor, same shape 0x007F30F0 walks.
struct Rva007F2A50Owner
{
	FeslInt64 owner;
	int ownerType;
};

struct Rva007F3870Attribute
{
	const char *key;
	const char *value;
};

extern const char * const g_Rva0130A708;

// ------------------------------------------------------- key/value cursors
class Rva007F2EA0Cursor
{
public:
	bool next( char *key, int keySize, char *value, int valueSize );

	Rva007E8810Message *m_msg;
	char m_pad[ 0x28 ];
	int m_index;
};

bool Rva007F2EA0Cursor::next( char *key, int keySize, char *value, int valueSize )
{
	char name[ 0x40 ];

	sprintf( name, "Values.%d.Key", m_index );
	if( !m_msg->getString( name, key, keySize ) )
		return false;
	sprintf( name, "Values.%d.Value", m_index );
	m_msg->getString( name, value, valueSize );
	++m_index;
	return true;
}

class Rva007F35D0Cursor
{
public:
	bool next( char *key, int keySize, char *value, int valueSize );

	Rva007E8810Message *m_msg;
	char m_pad[ 0x20 ];
	int m_index;
};

bool Rva007F35D0Cursor::next( char *key, int keySize, char *value, int valueSize )
{
	char name[ 0x40 ];

	sprintf( name, "Attributes.%d.Key", m_index );
	if( !m_msg->getString( name, key, keySize ) )
		return false;
	sprintf( name, "Attributes.%d.Value", m_index );
	m_msg->getString( name, value, valueSize );
	++m_index;
	return true;
}

// ------------------------------------------------------------ member record
class Rva007F3710Member
{
public:
	bool load( Rva007E8810Message *msg, int memberIndex );
	bool nextAttribute( char *key, int keySize, char *value, int valueSize );

	Rva007E8810Message *m_msg;
	char m_name[ 0x40 ];
	int m_pad;
	FeslInt64 m_userId;
	int m_state;
	int m_memberIndex;
	int m_attributeIndex;
};

bool Rva007F3710Member::load( Rva007E8810Message *msg, int memberIndex )
{
	char name[ 0x40 ];

	m_msg = msg;
	m_memberIndex = memberIndex;
	sprintf( name, "Members.%d.Name", m_memberIndex );
	if( !m_msg->getString( name, m_name, 0x40 ) )
		return false;
	sprintf( name, "Members.%d.UserId", m_memberIndex );
	m_userId = m_msg->getInt64( name, 0 );
	sprintf( name, "Members.%d.State", m_memberIndex );
	m_state = m_msg->getInt( name, 0 );
	m_attributeIndex = 0;
	return true;
}

bool Rva007F3710Member::nextAttribute( char *key, int keySize, char *value, int valueSize )
{
	char name[ 0x40 ];

	sprintf( name, "Members.%d.MemberAttributes.%d.Key", m_memberIndex, m_attributeIndex );
	if( !m_msg->getString( name, key, keySize ) )
		return false;
	sprintf( name, "Members.%d.MemberAttributes.%d.Value", m_memberIndex, m_attributeIndex );
	m_msg->getString( name, value, valueSize );
	++m_attributeIndex;
	return true;
}

// -------------------------------------------------------------- club record
class Rva007F3440Club
{
public:
	bool load( Rva007E8810Message *msg, int index );

	char m_head[ 8 ];
	FeslInt64 m_clubId;
	char m_name[ 0x40 ];
	char m_description[ 0xFF ];
	int m_access;
	int m_state;
	int m_userState;
};

bool Rva007F3440Club::load( Rva007E8810Message *msg, int index )
{
	char name[ 0x40 ];

	sprintf( name, "Clubs.%d.ClubId", index );
	m_clubId = msg->getInt64( name, 0 );
	if( m_clubId == 0 )
		return false;
	sprintf( name, "Clubs.%d.Name", index );
	msg->getString( name, m_name, 0x40 );
	sprintf( name, "Clubs.%d.Description", index );
	msg->getString( name, m_description, 0xFF );
	sprintf( name, "Clubs.%d.Access", index );
	m_access = msg->getInt( name, 0 );
	sprintf( name, "Clubs.%d.State", index );
	m_state = msg->getInt( name, 0 );
	sprintf( name, "Clubs.%d.UserState", index );
	m_userState = msg->getInt( name, 0 );
	return true;
}

// ------------------------------- the two-field walkers over those records
class Rva007F35A0ClubWalk
{
public:
	bool next( Rva007F3440Club *club );

	Rva007E8810Message *m_msg;
	int m_index;
};

bool Rva007F35A0ClubWalk::next( Rva007F3440Club *club )
{
	if( !club->load( m_msg, m_index ) )
		return false;
	++m_index;
	return true;
}

class Rva007F3820MemberWalk
{
public:
	bool next( Rva007F3710Member *member );

	Rva007E8810Message *m_msg;
	int m_index;
};

bool Rva007F3820MemberWalk::next( Rva007F3710Member *member )
{
	if( !member->load( m_msg, m_index ) )
		return false;
	++m_index;
	return true;
}

#pragma pack( push, 4 )
struct Rva007F1C90Record
{
	FeslInt64 m_userId;
	int m_score;
};
#pragma pack( pop )

class Rva007F1C90Cursor
{
public:
	bool next( Rva007F1C90Record *record );

	Rva007E8810Message *m_msg;
	int m_index;
};

bool Rva007F1C90Cursor::next( Rva007F1C90Record *record )
{
	bool result;
	char name[ 0x40 ];
	int score;
	Rva007F1C90Record *out;
	int zero2;

	result = false;
	zero2 = 0;
	out = record;
	out->m_userId = result;
	out->m_score = zero2;
	sprintf( name, "reputations.%d.UserId", m_index );
	score = m_msg->getInt( name, -1 );
	if( score > -1 )
	{
		out->m_userId = score;
		sprintf( name, "reputations.%d.Score", m_index );
		out->m_score = m_msg->getInt( name, result );
		++m_index;
		result = true;
	}
	return result;
}

// ------------------------------ request builders that format indexed keys
void __stdcall Rva007F2A50( Rva007E8810Message *msg, const Rva007F2A50Owner *owner,
	const char * const *keys, int count, int periodId, int periodPast )
{
	char name[ 0x20 ];
	int i;

	if( owner )
	{
		msg->addInt64( "owner", owner->owner );
		msg->addInt( "ownerType", owner->ownerType );
	}
	msg->addInt( "periodId", periodId );
	msg->addInt( "periodPast", periodPast );
	for( i = 0; i < count; ++i )
	{
		sprintf( name, "keys.%d", i );
		msg->addString( name, keys[ i ] );
	}
	msg->addInt( "keys.[]", count );
}

void __stdcall Rva007F3870( Rva007E8810Message *msg, const char *name,
	const char *description, int access, int state,
	const Rva007F3870Attribute *attributes, unsigned int count )
{
	const char *txn = g_Rva0130A708;
	unsigned int i;

	msg->reset();
	msg->m_category = 'club';
	msg->addString( "TXN", txn );
	msg->addString( "name", name );
	msg->addString( "description", description );
	msg->addInt( "access", access );
	msg->addInt( "state", state );
	msg->addInt( "attributes.[]", count );
	for( i = 0; i < count; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "attributes.%d.key", i );
		msg->addString( key, attributes[ i ].key );
		sprintf( key, "attributes.%d.value", i );
		msg->addString( key, attributes[ i ].value );
	}
}
