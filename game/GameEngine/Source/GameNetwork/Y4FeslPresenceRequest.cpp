#include <string.h>

// EA FESL client SDK ("jabba") -- the presence-set request builder.
//
// Same SDK cluster and same message object as Y4FeslBuddyRequests.cpp.  This
// row is the widest of the family (10 __stdcall arguments, `ret 0x28`) and is
// the one that shows the ATTR field is a FLAG SET, not a string: three
// independent `test cl,1` / `test cl,2` / `test cl,4` guards each append one
// character to a stack scratch through MSVC's inline strcat, and the joined
// result is sent as the value of "ATTR".  The bit-to-character mapping is the
// hard evidence; the flag NAMES are not recoverable from the bytes.
//
// The presence-state switch is a jump table over cases 2..6 whose arms each
// call addString directly and are tail-merged onto one `push "SHOW"` -- the
// same shape (and the same source form) as the TYPE switch in
// Y4FeslBuddyRequests2.cpp.
//
// The scratch has no frame of its own: MSVC reuses the incoming argument home
// area for it, which is why there is no `sub esp` in the prologue.

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

void __stdcall Rva007FB0E0( Rva007E8810Message *msg, const char *rsrc, int show,
	const char *stat, const char *prod, int attributes, const char *sess,
	const char *titl, const char *tiid, const char *extr )
{
	msg->reset();
	msg->m_category = 'PSET';
	msg->m_depth = 3;
	if( rsrc )
		msg->addString( "RSRC", rsrc );
	switch( show )
	{
		case 2:
			msg->addString( "SHOW", "CHAT" );
			break;
		case 3:
			msg->addString( "SHOW", "AWAY" );
			break;
		case 4:
			msg->addString( "SHOW", "XA" );
			break;
		case 5:
			msg->addString( "SHOW", "DND" );
			break;
		case 6:
			msg->addString( "SHOW", "GAME" );
			break;
	}
	msg->addString( "STAT", stat );
	if( prod )
		msg->addString( "PROD", prod );
	if( attributes )
	{
		char attr[ 4 ] = "";

		if( attributes & 1 )
			strcat( attr, "V" );
		if( attributes & 2 )
			strcat( attr, "J" );
		if( attributes & 4 )
			strcat( attr, "P" );
		msg->addString( "ATTR", attr );
	}
	if( sess )
		msg->addString( "SESS", sess );
	if( titl )
		msg->addString( "TITL", titl );
	if( tiid )
		msg->addString( "TIID", tiid );
	if( extr )
		msg->addString( "EXTR", extr );
}
