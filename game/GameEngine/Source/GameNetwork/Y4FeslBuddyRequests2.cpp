#include <string.h>

// EA FESL client SDK ("jabba") -- buddy/presence request builders whose
// argument selection is a small switch over an answer/message kind.
//
// Same SDK and same message object as Y4FeslBuddyRequests.cpp; see that file
// for the range evidence.  Split into its own translation unit only to keep
// the switch experiments from disturbing rows already verified there.

typedef __int64 FeslInt64;

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class Rva007E8AC0
{
public:
	void run();                                                   // 0x007E8AC0
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *one, void *two );                       // 0x007E8A10
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *one, void *two );                       // 0x007E88D0
};

class Rva007E8810Message
{
public:
	void addInt64( const char *key, FeslInt64 value );               // 0x007E8E90
	void addBool( const char *key, bool value );                     // 0x007E8980
	void setError( int code );                                       // 0x007E88C0

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

void __stdcall Rva007FB810( Rva007E8810Message *msg, const char *user, int answer )
{
	reinterpret_cast< Rva007E8AC0 * >( msg )->run();
	msg->m_category = 'GRSP';
	msg->m_depth = 3;
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"USER", (void *)user );
	switch( answer )
	{
		case 0:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"ANSW", (void *)"Y" );
			break;
		case 1:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"ANSW", (void *)"N" );
			break;
		case 2:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"ANSW", (void *)"R" );
			break;
	}
}

void __stdcall Rva007FB8D0( Rva007E8810Message *msg, int kind, const char *user,
	const char *subject, const char *body, int secs )
{
	reinterpret_cast< Rva007E8AC0 * >( msg )->run();
	msg->m_category = 'SEND';
	msg->m_depth = 3;
	switch( kind )
	{
		case 1:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"TYPE", (void *)"C" );
			break;
		case 2:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"TYPE", (void *)"A" );
			break;
	}
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"USER", (void *)user );
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"SUBJ", (void *)subject );
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"BODY", (void *)body );
	reinterpret_cast< BfmeThingCIB * >( msg )->bfmeGoCIB( (void *)"SECS", (void *)secs );
}

void __stdcall Rva007FB960( Rva007E8810Message *msg, int kind, const char *user,
	const char *subject, const char *body, int secs )
{
	reinterpret_cast< Rva007E8AC0 * >( msg )->run();
	msg->m_category = 'BRDC';
	msg->m_depth = 3;
	switch( kind )
	{
		case 1:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"TYPE", (void *)"C" );
			break;
		case 2:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"TYPE", (void *)"A" );
			break;
	}
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"USER", (void *)user );
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"SUBJ", (void *)subject );
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"BODY", (void *)body );
	reinterpret_cast< BfmeThingCIB * >( msg )->bfmeGoCIB( (void *)"SECS", (void *)secs );
}

void __stdcall Rva007FB410( Rva007E8810Message *msg, const char *user,
	int answer, bool pres )
{
	reinterpret_cast< Rva007E8AC0 * >( msg )->run();
	msg->m_category = 'RRSP';
	msg->m_depth = 3;
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"USER", (void *)user );
	switch( answer )
	{
		case 0:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"ANSW", (void *)"Y" );
			break;
		case 1:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"ANSW", (void *)"N" );
			break;
		case 2:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"ANSW", (void *)"B" );
			break;
	}
	if( answer == 0 )
		reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"PRES", (void *)pres ? "Y" : "N" );
}

void __stdcall Rva007FB6D0( Rva007E8810Message *msg, int list, const char *group,
	const char *lsrc, bool pres, bool pend )
{
	reinterpret_cast< Rva007E8AC0 * >( msg )->run();
	msg->m_category = 'RGET';
	msg->m_depth = 3;
	switch( list )
	{
		case 1:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"LIST", (void *)"B" );
			break;
		case 2:
			reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"LIST", (void *)"I" );
			break;
	}
	if( group && strlen( group ) != 0 )
		reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"GROUP", (void *)group );
	if( lsrc && strlen( lsrc ) != 0 )
		reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"LSRC", (void *)lsrc );
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"PRES", (void *)pres ? "Y" : "N" );
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"PEND", (void *)pend ? "T" : "F" );
}

// FESL 'RADD' friend-list request with an optional single-letter attribute.
void __stdcall Rva007FB260( Rva007E8810Message *msg, int list,
	const char *user, const char *group, const char *lsrc, bool pres,
	int attribute )
{
	reinterpret_cast< Rva007E8AC0 * >( msg )->run();
	msg->m_category = 'RADD';
	msg->m_depth = 3;
	switch( list )
	{
		case 1: reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"LIST", (void *)"B" ); break;
		case 2: reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"LIST", (void *)"I" ); break;
	}
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"USER", (void *)user );
	if( group )
		reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"GROUP", (void *)group );
	if( lsrc )
		reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"LSRC", (void *)lsrc );
	reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"PRES", (void *)pres ? "Y" : "N" );
	if( attribute )
	{
		char text[ 4 ] = "";
		if( attribute == 1 )
			strcat( text, "A" );
		else if( attribute == 2 )
			strcat( text, "M" );
		else if( attribute == 3 )
			strcat( text, "I" );
		reinterpret_cast< BfmeThingCIC * >( msg )->bfmeGoCIC( (void *)"ATTR", (void *)text );
	}
}
