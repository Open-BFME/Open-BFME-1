// cl: /GS
#include <string.h>
#include <stdio.h>

// EA FESL client SDK ("jabba") -- transaction request builders.
//
// The assert strings reached from this span name their own source tree:
//     \views\feslbuild_main\jabba\fesl\source\ariesudp.cpp
// so the whole 0x007F2A50..0x007F9660 cluster is EA's FESL/Aries online SDK
// linked into lotrbfme.exe, not Westwood or EA Pacific game code.
//
// WHAT THE BYTES SHOW.  Every row here is a __stdcall free function whose first
// argument is a pointer to the message object constructed at RVA 0x007E8810.
// That object's layout is forced by its own primitives:
//     +0x10  char *   output buffer          (reset() stores 0 through it)
//     +0x14  int      buffer size
//     +0x18  int      write cursor           (reset() zeroes it)
//     +0x1C  int      FOUR-CHARACTER CATEGORY -- written by every row below
//     +0x24  int      error code             (-100 on overflow)
//     +0x2C  int      set to 4 by reset()
// The store at +0x1C is an imm32 with no relocation, so it is hard evidence:
// 0x66737973, 0x636C7562, 0x72616E6B are the MSVC multi-character literals
// 'fsys', 'club' and 'rank' -- the FESL category codes.  Together with the
// literal key "TXN" pushed immediately after, that is the FESL wire format.
//
// The transaction NAME is not a literal: each row loads a pointer from a fixed
// data address into a register BEFORE calling reset(), then passes it as the
// value of "TXN".  Hoisting a load across a call means the compiler proved the
// call cannot change it, which is what a `const` pointer object gives; the
// spelling below is a local copy of a const global, which is what reproduces
// the schedule. Retail stores these transaction slots in writable .data as
// zero-initialized four-byte words. Each definition below owns a verified data
// row; the local pointer snapshot preserves the load before reset().
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names the transactions, the message
// class, or the argument identifiers.  Key spellings ("clubId", "userId",
// "state", "periodId", ...) are read out of the pushed string literals and are
// therefore real, but the C++ parameter names, the class name and the method
// names are address-derived.  A separate synthetic class is used rather than
// the tree's existing Rva7F4CC0Child (Rva7F4CC0ConstructorThunk.cpp) because
// that model stops at 0x10 bytes while these primitives touch +0x2C; the two
// are the same retail object seen through two windows, and this file does not
// land over that one.

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

// Existing ledger owners of the retail message primitives (callees.py).
class BfmeC994
{
public:
	void addString( const char *key, const char *value );
};
class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *key, void *value );
};
class Rva007E8980
{
public:
	void go( int key, unsigned char value );
};
class Gen_007e88c0
{
public:
	void m( int code );
};

class Rva007E8810Message
{
public:
	void addInt64( const char *key, FeslInt64 value );               // 0x007E8E90

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

// The 12-byte owner descriptor 0x007F30F0 walks: a 64-bit id followed by a type
// word the row REJECTS unless it equals 1.
struct Rva007F30F0Owner
{
	FeslInt64 owner;
	int ownerType;
};

struct Rva007F3B50Attribute
{
	const char *key;
	const char *value;
};

unsigned int g_Va0130A678 = 0;
unsigned int g_Va0130A6D8 = 0;
unsigned int g_Va0130A750 = 0;
unsigned int g_Va0130A78C = 0;
unsigned int g_Va0130A684 = 0;
unsigned int g_Va0130A720 = 0;
unsigned int g_Va0130A72C = 0;
unsigned int g_Va0130A738 = 0;
unsigned int g_Va0130A744 = 0;
unsigned int g_Va0130A75C = 0;
unsigned int g_Va0130A774 = 0;
unsigned int g_Va0130A798 = 0;
unsigned int g_Va0130A7A4 = 0;

void __stdcall Rva007F4310( Rva007E8810Message *msg )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A7A4);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'fsys';
	((BfmeC994 *)msg)->addString( "TXN", txn );
}

void __stdcall Rva007F4340( Rva007E8810Message *msg )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A798);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'fsys';
	((BfmeC994 *)msg)->addString( "TXN", txn );
}

void __stdcall Rva007F3E50( Rva007E8810Message *msg, FeslInt64 clubId )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A774);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'club';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	msg->addInt64( "clubId", clubId );
}

void __stdcall Rva007F3F40( Rva007E8810Message *msg, FeslInt64 clubId )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A744);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'club';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	msg->addInt64( "clubId", clubId );
}

void __stdcall Rva007F3F90( Rva007E8810Message *msg, FeslInt64 clubId, int state )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A738);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'club';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	msg->addInt64( "clubId", clubId );
	if( state )
		((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"state", (void *)(state) );
}

void __stdcall Rva007F3AF0( Rva007E8810Message *msg, FeslInt64 clubId, FeslInt64 userId )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A720);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'club';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	msg->addInt64( "clubId", clubId );
	msg->addInt64( "userId", userId );
}

void __stdcall Rva007F3A80( Rva007E8810Message *msg, FeslInt64 clubId, FeslInt64 userId, int state )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A72C);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'club';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	msg->addInt64( "clubId", clubId );
	msg->addInt64( "userId", userId );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"state", (void *)(state) );
}

void __stdcall Rva007F3B50( Rva007E8810Message *msg, FeslInt64 clubId,
	FeslInt64 userId, const Rva007F3B50Attribute *attributes, unsigned int count )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A75C);
	unsigned int i;

	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'club';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	msg->addInt64( "clubId", clubId );
	msg->addInt64( "userId", userId );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"attributes.[]", (void *)(count) );
	for( i = 0; i < count; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "attributes.%d.key", i );
		((BfmeC994 *)msg)->addString( key, attributes[ i ].key );
		sprintf( key, "attributes.%d.value", i );
		((BfmeC994 *)msg)->addString( key, attributes[ i ].value );
	}
}

void __stdcall Rva007F2D10( Rva007E8810Message *msg, const char *key, int periodId )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A678);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'rank';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	((BfmeC994 *)msg)->addString( "key", key );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"periodId", (void *)(periodId) );
}

void __stdcall Rva007F2B70( Rva007E8810Message *msg, const char *key, int ownerType,
	int minRank, int maxRank, int periodId, int periodPast )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A684);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'rank';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	((BfmeC994 *)msg)->addString( "key", key );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"ownerType", (void *)(ownerType) );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"minRank", (void *)(minRank) );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"maxRank", (void *)(maxRank) );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"periodId", (void *)(periodId) );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"periodPast", (void *)(periodPast) );
}

void __stdcall Rva007F30F0( Rva007E8810Message *msg, const Rva007F30F0Owner *owner,
	const char *recordName )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A6D8);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'recp';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	if( owner )
	{
		if( owner->ownerType == 1 )
		{
			msg->addInt64( "owner", owner->owner );
			((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"ownerType", (void *)(owner->ownerType) );
		}
		else
		{
			((Gen_007e88c0 *)msg)->m( -113 );
			return;
		}
	}
	((BfmeC994 *)msg)->addString( "recordName", recordName );
}

void __stdcall Rva007F3EA0( Rva007E8810Message *msg, bool memberOnly,
	const char *lookupString, FeslInt64 userId, int state )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A750);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'club';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	((Rva007E8980 *)msg)->go( (int)"memberOnly", memberOnly );
	if( lookupString && strlen( lookupString ) != 0 )
		((BfmeC994 *)msg)->addString( "lookupString", lookupString );
	if( userId )
		msg->addInt64( "userId", userId );
	if( state )
		((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"state", (void *)(state) );
}

void __stdcall Rva007F4240( Rva007E8810Message *msg, const char *clientString,
	const char *sku, const char *locale, const char *clientVersion,
	const char *SDKVersion, const char *clientPlatform, const char *clientType )
{
	const char *txn = reinterpret_cast<const char *>(g_Va0130A78C);
	((Rva007E8AC0 *)msg)->run();
	msg->m_category = 'fsys';
	((BfmeC994 *)msg)->addString( "TXN", txn );
	((BfmeC994 *)msg)->addString( "clientString", clientString );
	((BfmeC994 *)msg)->addString( "sku", sku );
	((BfmeC994 *)msg)->addString( "locale", locale );
	((BfmeC994 *)msg)->addString( "clientPlatform", clientPlatform );
	((BfmeC994 *)msg)->addString( "clientVersion", clientVersion );
	((BfmeC994 *)msg)->addString( "SDKVersion", SDKVersion );
	((BfmeC994 *)msg)->addString( "protocolVersion", "2.0" );
	((BfmeThingCIB *)msg)->bfmeGoCIB( (void *)"fragmentSize", (void *)(2048) );
	msg->m_depth = 3;
	if( clientType )
		((BfmeC994 *)msg)->addString( "clientType", clientType );
}
