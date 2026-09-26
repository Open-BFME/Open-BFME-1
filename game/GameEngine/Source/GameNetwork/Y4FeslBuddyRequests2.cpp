#include <string.h>

// EA FESL client SDK ("jabba") -- buddy/presence request builders whose
// argument selection is a small switch over an answer/message kind.
//
// Same SDK and same message object as Y4FeslBuddyRequests.cpp; see that file
// for the range evidence.  Split into its own translation unit only to keep
// the switch experiments from disturbing rows already verified there.

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset( void );                                              // 0x007E8AC0
	void addString( const char *key, const char *value );            // 0x007E8A10
	void addInt( const char *key, int value );                       // 0x007E88D0
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
	msg->reset();
	msg->m_category = 'GRSP';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	switch( answer )
	{
		case 0:
			msg->addString( "ANSW", "Y" );
			break;
		case 1:
			msg->addString( "ANSW", "N" );
			break;
		case 2:
			msg->addString( "ANSW", "R" );
			break;
	}
}

void __stdcall Rva007FB8D0( Rva007E8810Message *msg, int kind, const char *user,
	const char *subject, const char *body, int secs )
{
	msg->reset();
	msg->m_category = 'SEND';
	msg->m_depth = 3;
	switch( kind )
	{
		case 1:
			msg->addString( "TYPE", "C" );
			break;
		case 2:
			msg->addString( "TYPE", "A" );
			break;
	}
	msg->addString( "USER", user );
	msg->addString( "SUBJ", subject );
	msg->addString( "BODY", body );
	msg->addInt( "SECS", secs );
}

void __stdcall Rva007FB960( Rva007E8810Message *msg, int kind, const char *user,
	const char *subject, const char *body, int secs )
{
	msg->reset();
	msg->m_category = 'BRDC';
	msg->m_depth = 3;
	switch( kind )
	{
		case 1:
			msg->addString( "TYPE", "C" );
			break;
		case 2:
			msg->addString( "TYPE", "A" );
			break;
	}
	msg->addString( "USER", user );
	msg->addString( "SUBJ", subject );
	msg->addString( "BODY", body );
	msg->addInt( "SECS", secs );
}

void __stdcall Rva007FB410( Rva007E8810Message *msg, const char *user,
	int answer, bool pres )
{
	msg->reset();
	msg->m_category = 'RRSP';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	switch( answer )
	{
		case 0:
			msg->addString( "ANSW", "Y" );
			break;
		case 1:
			msg->addString( "ANSW", "N" );
			break;
		case 2:
			msg->addString( "ANSW", "B" );
			break;
	}
	if( answer == 0 )
		msg->addString( "PRES", pres ? "Y" : "N" );
}

void __stdcall Rva007FB6D0( Rva007E8810Message *msg, int list, const char *group,
	const char *lsrc, bool pres, bool pend )
{
	msg->reset();
	msg->m_category = 'RGET';
	msg->m_depth = 3;
	switch( list )
	{
		case 1:
			msg->addString( "LIST", "B" );
			break;
		case 2:
			msg->addString( "LIST", "I" );
			break;
	}
	if( group && strlen( group ) != 0 )
		msg->addString( "GROUP", group );
	if( lsrc && strlen( lsrc ) != 0 )
		msg->addString( "LSRC", lsrc );
	msg->addString( "PRES", pres ? "Y" : "N" );
	msg->addString( "PEND", pend ? "T" : "F" );
}
