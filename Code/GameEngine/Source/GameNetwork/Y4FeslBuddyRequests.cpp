#include <string.h>

// EA FESL client SDK ("jabba") -- buddy/presence transaction request builders.
//
// RANGE EVIDENCE.  The assert strings reached from 0x007F96C0 and 0x007F97B0
// name their own source tree:
//     \views\feslbuild_main\jabba\fesl\source\transactor.cpp
// which is the SAME \jabba\fesl\source\ tree already identified for
// 0x007F2A50..0x007F9660 (ariesudp.cpp).  The span claimed here therefore
// continues EA's FESL SDK, not game code.  The literal keys pushed by these
// rows -- LKEY PROD VERS PRES RSRC USER PASS DOMN DIST MAXR GROUP LSRC SESS
// TITL ANSW SUBJ BODY SECS ADDR ENAB -- together with the boolean value
// spellings "Y"/"N" and "T"/"F" are the EA buddy/presence wire vocabulary.
//
// Every row below is __stdcall with the FESL message object as first argument
// and follows the shape already established for this SDK in
// V2FeslTxnRequests.cpp: reset(); category = <FourCC>; depth = 3; then a run of
// addString/addInt calls keyed by literal field names.  The FourCC written to
// +0x1C is an imm32 with NO relocation, so it is hard evidence and is spelled
// as an MSVC multi-character literal below: 'AUTH', 'USCH', 'PADD', 'PDEL',
// 'RADM', 'MLST', 'TCKL', 'RDEM', 'GINV', 'GRVK', 'EPST'.
//
// The message class is re-declared here rather than shared through a header:
// this lane may not add a .h file.  It is the same object modelled in
// V2FeslTxnRequests.cpp, method addresses included.

typedef __int64 FeslInt64;

// Class name is the claimed pin (ctor 0x007E8810).  Layout is the same object
// V2FeslTxnRequests.cpp already recovered from reset()/add* stores.
class Rva007E8810Message
{
public:
	void reset( void );                                              // 0x007E8AC0
	void addString( const char *key, const char *value );            // 0x007E8A10
	void addInt( const char *key, int value );                       // 0x007E88D0
	void addInt64( const char *key, FeslInt64 value );               // 0x007E8E90
	void addBool( const char *key, bool value );                     // 0x007E8980
	void setError( int code );                                       // 0x007E88C0

	char m_pad00[ 0x10 ];
	char *m_output;                                                  // +0x10
	int m_bufferSize;                                                // +0x14
	int m_writeCursor;                                               // +0x18
	unsigned int m_category;                                         // +0x1C
	char m_pad20[ 4 ];
	int m_errorCode;                                                 // +0x24
	char m_pad28[ 4 ];
	int m_depth;                                                     // +0x2C
};

typedef Rva007E8810Message FeslTxnMessage;

// ---- 'AUTH' ---------------------------------------------------------------

void __stdcall Rva007FAE40( FeslTxnMessage *msg, const char *lkey,
	const char *prod, const char *vers, const char *pres, const char *rsrc )
{
	msg->reset();
	msg->m_category = 'AUTH';
	msg->m_depth = 3;
	msg->addString( "LKEY", lkey );
	msg->addString( "PROD", prod );
	msg->addString( "VERS", vers );
	msg->addString( "PRES", pres );
	if( rsrc && *rsrc )
		msg->addString( "RSRC", rsrc );
	else
		msg->addString( "RSRC", "CSO" );
}

void __stdcall Rva007FAEE0( FeslTxnMessage *msg, const char *user,
	const char *pass, const char *prod, const char *vers, const char *pres,
	const char *rsrc )
{
	msg->reset();
	msg->m_category = 'AUTH';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	msg->addString( "PASS", pass );
	msg->addString( "PROD", prod );
	msg->addString( "VERS", vers );
	msg->addString( "PRES", pres );
	if( rsrc && *rsrc )
		msg->addString( "RSRC", rsrc );
	else
		msg->addString( "RSRC", "CSO" );
}

// ---- 'USCH' ---------------------------------------------------------------

void __stdcall Rva007FAFB0( FeslTxnMessage *msg, const char *user,
	const char *domain, const char *rsrc, bool dist, int maxResults )
{
	msg->reset();
	msg->m_category = 'USCH';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	if( domain && strlen( domain ) != 0 )
		msg->addString( "DOMN", domain );
	if( rsrc && strlen( rsrc ) != 0 )
		msg->addString( "RSRC", rsrc );
	if( dist )
		msg->addString( "DIST", "T" );
	else
		msg->addString( "DIST", "F" );
	msg->addInt( "MAXR", maxResults );
}

// ---- 'PADD' / 'PDEL' / 'TCKL' ---------------------------------------------

void __stdcall Rva007FB080( FeslTxnMessage *msg, const char *user )
{
	msg->reset();
	msg->m_category = 'PADD';
	msg->m_depth = 3;
	msg->addString( "USER", user );
}

void __stdcall Rva007FB0B0( FeslTxnMessage *msg, const char *user )
{
	msg->reset();
	msg->m_category = 'PDEL';
	msg->m_depth = 3;
	msg->addString( "USER", user );
}

void __stdcall Rva007FB510( FeslTxnMessage *msg, const char *user )
{
	msg->reset();
	msg->m_category = 'TCKL';
	msg->m_depth = 3;
	if( user )
		msg->addString( "USER", user );
}

// ---- 'RADM' / 'MLST' / 'RDEM' ---------------------------------------------

void __stdcall Rva007FB390( FeslTxnMessage *msg, const char *user,
	const char *group, const char *lsrc, bool pres )
{
	msg->reset();
	msg->m_category = 'RADM';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	if( group )
		msg->addString( "GROUP", group );
	if( lsrc )
		msg->addString( "LSRC", lsrc );
	msg->addString( "PRES", pres ? "Y" : "N" );
}

void __stdcall Rva007FB4B0( FeslTxnMessage *msg, const char *user,
	const char *group, const char *lsrc )
{
	msg->reset();
	msg->m_category = 'MLST';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	if( group )
		msg->addString( "GROUP", group );
	if( lsrc )
		msg->addString( "LSRC", lsrc );
}

void __stdcall Rva007FB620( FeslTxnMessage *msg, const char *user,
	const char *group, const char *lsrc, bool pres )
{
	msg->reset();
	msg->m_category = 'RDEM';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	if( group && strlen( group ) != 0 )
		msg->addString( "GROUP", group );
	if( lsrc && strlen( lsrc ) != 0 )
		msg->addString( "LSRC", lsrc );
	msg->addString( "PRES", pres ? "Y" : "N" );
}

// ---- 'GINV' / 'GRVK' / 'EPST' ---------------------------------------------

void __stdcall Rva007FB7B0( FeslTxnMessage *msg, const char *user,
	const char *sess, const char *titl )
{
	msg->reset();
	msg->m_category = 'GINV';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	msg->addString( "SESS", sess );
	msg->addString( "TITL", titl );
}

void __stdcall Rva007FB890( FeslTxnMessage *msg, const char *user,
	const char *sess )
{
	msg->reset();
	msg->m_category = 'GRVK';
	msg->m_depth = 3;
	msg->addString( "USER", user );
	msg->addString( "SESS", sess );
}

void __stdcall Rva007FB9F0( FeslTxnMessage *msg, const char *addr, bool enab )
{
	msg->reset();
	msg->m_category = 'EPST';
	msg->m_depth = 3;
	msg->addString( "ADDR", addr );
	if( enab )
		msg->addString( "ENAB", "T" );
	else
		msg->addString( "ENAB", "F" );
}

// ---- 'CONN' / 'USER' ------------------------------------------------------

// The PROT value is read from a fixed data address AFTER reset(), so it is an
// ordinary mutable global rather than the const-hoisted TXN pointers of
// V2FeslTxnRequests.cpp.  Its four bytes are a DIR32 site copied from retail.
static char *g_Rva012C3BC4;

void __stdcall Rva007FC170( FeslTxnMessage *msg, const char *prod,
	const char *vers, const char *plat, const char *locale )
{
	msg->reset();
	msg->m_category = 'CONN';
	msg->m_depth = 3;
	msg->addString( "PROT", g_Rva012C3BC4 );
	msg->addString( "PROD", prod );
	msg->addString( "VERS", vers );
	if( plat && strlen( plat ) != 0 )
		msg->addString( "PLAT", plat );
	msg->addString( "LOCALE", locale );
}

void __stdcall Rva007FC210( FeslTxnMessage *msg, const char *hid,
	const char *lkey, const char *name )
{
	msg->reset();
	msg->m_category = 'USER';
	msg->m_depth = 3;
	msg->addString( "HID", hid );
	msg->addString( "LKEY", lkey );
	msg->addString( "NAME", name );
}

// ---- game-session ids -----------------------------------------------------

void __stdcall Rva007FC510( FeslTxnMessage *msg, int lid, int gid )
{
	msg->reset();
	msg->m_category = 'GDAT';
	msg->m_depth = 3;
	msg->addInt( "LID", lid );
	msg->addInt( "GID", gid );
}

void __stdcall Rva007FCA40( FeslTxnMessage *msg, bool start )
{
	msg->reset();
	msg->m_category = 'UBRA';
	msg->m_depth = 3;
	msg->addBool( "START", start );
}

void __stdcall Rva007FCA70( FeslTxnMessage *msg, int lid, int gid, int port )
{
	msg->reset();
	msg->m_category = 'EGAM';
	msg->m_depth = 3;
	msg->addInt( "LID", lid );
	msg->addInt( "GID", gid );
	msg->addInt( "PORT", port );
}

void __stdcall Rva007FCAD0( FeslTxnMessage *msg, int lid, int gid )
{
	msg->reset();
	msg->m_category = 'ECNL';
	msg->m_depth = 3;
	msg->addInt( "LID", lid );
	msg->addInt( "GID", gid );
}

void __stdcall Rva007FCC50( FeslTxnMessage *msg, int pid )
{
	msg->reset();
	msg->m_category = 'PLVT';
	msg->m_depth = 3;
	msg->addInt( "PID", pid );
}

void __stdcall Rva007FCE70( FeslTxnMessage *msg, int timeout )
{
	msg->reset();
	msg->m_category = 'KEEP';
	msg->m_depth = 3;
	msg->addInt( "TIMO", timeout );
}

void __stdcall Rva007FCEA0( FeslTxnMessage *msg, const char *ugid,
	const char *secret, int port )
{
	msg->reset();
	msg->m_category = 'HGAM';
	msg->m_depth = 3;
	msg->addString( "SECRET", secret );
	msg->addString( "UGID", ugid );
	msg->addInt( "PORT", port );
}
