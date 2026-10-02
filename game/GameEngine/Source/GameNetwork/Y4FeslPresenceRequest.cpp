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

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class Rva007E8AC0
{
public:
	void run();                                                   // 0x007E8AC0
};

class BfmeC994
{
public:
	void addString( const char *key, const char *value );                       // 0x007E8A10
};

class Rva007E8810Message
{
public:
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
	reinterpret_cast< Rva007E8AC0 * >( msg )->run();
	msg->m_category = 'PSET';
	msg->m_depth = 3;
	if( rsrc )
		reinterpret_cast< BfmeC994 * >( msg )->addString( "RSRC", (const char *)rsrc );
	switch( show )
	{
		case 2:
			reinterpret_cast< BfmeC994 * >( msg )->addString( "SHOW", "CHAT" );
			break;
		case 3:
			reinterpret_cast< BfmeC994 * >( msg )->addString( "SHOW", "AWAY" );
			break;
		case 4:
			reinterpret_cast< BfmeC994 * >( msg )->addString( "SHOW", "XA" );
			break;
		case 5:
			reinterpret_cast< BfmeC994 * >( msg )->addString( "SHOW", "DND" );
			break;
		case 6:
			reinterpret_cast< BfmeC994 * >( msg )->addString( "SHOW", "GAME" );
			break;
	}
	reinterpret_cast< BfmeC994 * >( msg )->addString( "STAT", (const char *)stat );
	if( prod )
		reinterpret_cast< BfmeC994 * >( msg )->addString( "PROD", (const char *)prod );
	if( attributes )
	{
		char attr[ 4 ] = "";

		if( attributes & 1 )
			strcat( attr, "V" );
		if( attributes & 2 )
			strcat( attr, "J" );
		if( attributes & 4 )
			strcat( attr, "P" );
		reinterpret_cast< BfmeC994 * >( msg )->addString( "ATTR", (const char *)attr );
	}
	if( sess )
		reinterpret_cast< BfmeC994 * >( msg )->addString( "SESS", (const char *)sess );
	if( titl )
		reinterpret_cast< BfmeC994 * >( msg )->addString( "TITL", (const char *)titl );
	if( tiid )
		reinterpret_cast< BfmeC994 * >( msg )->addString( "TIID", (const char *)tiid );
	if( extr )
		reinterpret_cast< BfmeC994 * >( msg )->addString( "EXTR", (const char *)extr );
}
