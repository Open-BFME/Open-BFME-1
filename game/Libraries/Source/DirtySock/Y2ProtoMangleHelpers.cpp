// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// EA's DirtySock ProtoMangle -- the file-static helpers that sit between the
// two bodies protomangle.cpp already names.
//
// WHY THIS IS PROTOMANGLE.  0x00804150 and 0x00804330 are named in the ledger
// because each logs its own name ("ProtoMangleCreate: Server:%s Port:%d
// GameID:%s LKey:%s" / "ProtoMangleDestroy: Shutting down").  Every body here
// is reached only from those two, or from the 2668-byte state machine at
// 0x00804920 whose log lines all start "ProtoMangle: ".  0x008042B0 logs
// "ProtoMangleCreate: buffer=%d bytes" under its caller's name, which is what
// keeps its OWN name unknown -- so the names in this file are address-derived
// and disclaim identity.  The struct is address-derived too; only the member
// OFFSETS and the immediates are evidence.
//
// WHY /Od /GZ.  Every body sets up a frame pointer for code with no register
// pressure, keeps each parameter in its stack slot across statements, writes
// 0xCCCCCCCC over its locals before using them, and ends `cmp ebp,esp / call
// 0x009F7502` -- MSVC 7.1's /GZ run-time checks, which cl rejects on the same
// command line as /O2.  This library was NOT built with the settings the rest
// of the image was.  /GS is on the same line for the sibling TU rows that carry
// the 0x012DBDB0 cookie; it instruments only bodies with a stack buffer, so it
// is inert for all four rows here.

// sprintf is called DIRECTLY (rel32 to the import stub at 0x009F6DE2), not
// through __imp__sprintf, so the translation unit did not see <stdio.h>'s
// dllimport declaration.  Declaring it here is what reproduces that.
extern "C" int sprintf( char *buffer, const char *format, ... );

#include <string.h>

struct Rva008042B0Http;

// ---------------------------------------------------------------- callees
// Addresses read from the REL32 at the call sites below; each name is pinned in
// targets/game/reverse/symbols.csv and derived from its address, not recovered.
// RETURNS INT.  The definition in Y4DirtySockDebug.c ends `xor eax,eax`, and
// 0x00805E50 stores that result into a local it never reads -- which is the
// only reason the return type is visible from this side at all.
int   Rva007FE780Printf( const char *format, ... );   // 0x007FE780
void *Rva007F0000Alloc( int size );                   // 0x007F0000
void  Rva007F0030Free( void *block );                 // 0x007F0030
void  Rva007FD4E0SocketShutdown( void *socket, int how );  // 0x007FD4E0
void  Rva007FD3F0SocketClose( void *socket );              // 0x007FD3F0
void *Rva007FDFF0Connect( const char *host, int timeout );  // 0x007FDFF0
// RETURNS THE RESPONSE BODY, not void: 0x008054A0 stores its result, tests it
// for null and hands it to the two parsers.  A one-argument call site cannot
// show that, which is why the earlier declaration here had it as void.
const char *Rva00804920Update( Rva008042B0Http *http );      // 0x00804920
char *Rva007FFB50AddrText( unsigned int addr );             // 0x007FFB50
struct Rva00804440SockAddr;
void  Rva007FE310SocketHost( Rva00804440SockAddr *host, int hostLen,
		Rva00804440SockAddr *dest, int destLen );           // 0x007FE310

// The receiver of 0x008042B0 / 0x008043C0.  ProtoMangleCreate passes
// `ref + 0xC0` with size 0x400, so this is an embedded sub-object, not the
// ProtoMangle module record itself.  Only the four offsets the bodies touch are
// evidence; the padding names nothing.
struct Rva008042B0Http
{
	void        *m_socket;          // +0x000
	void        *m_conn;            // +0x004
	int          m_pad008;
	char         m_host[ 0x100 ];   // +0x00C -- strcpy target, guarded by a strlen < 0x100
	int          m_field10C;        // +0x10C
	int          m_port;            // +0x110
	int          m_state;           // +0x114
	int          m_pad118;
	// THE HTTP RESPONSE CODE.  0x008054A0 compares the reader at 0x00805610 --
	// which is this field seen through the record -- against 400 and against
	// 200; a field tested against two HTTP status codes is one.
	int          m_httpCode;        // +0x11C
	int          m_pad120;
	int          m_field124;        // +0x124
	int          m_pad128;
	int          m_pad12C;
	char        *m_buffer;          // +0x130
	unsigned int m_bufferSize;      // +0x134
	int          m_pad138;
	int          m_pad13C;
	int          m_pad140;
	int          m_field144;        // +0x144
};

// Copy at most size-1 bytes and always terminate.  Note it does NOT stop at a
// NUL in the source: the loop is bounded only by the count, which is why this
// is not strncpy.  A null source yields an empty destination.
void Rva00804250CopyField( char *dst, const char *src, int size )
{
	int i = 0;

	if( src != 0 )
	{
		--size;
		for( ; i < size; ++i )
			dst[ i ] = src[ i ];
	}
	dst[ i ] = 0;
}

// Allocate the sub-object's transfer buffer.  Returns 1 or -1, not 0.
int Rva008042B0HttpCreate( Rva008042B0Http *http, int bufferSize )
{
	http->m_socket = 0;
	http->m_state = 0;
	http->m_bufferSize = bufferSize;
	Rva007FE780Printf( "ProtoMangleCreate: buffer=%d bytes\n", http->m_bufferSize );
	http->m_buffer = (char *)Rva007F0000Alloc( http->m_bufferSize );
	if( http->m_buffer == 0 )
		return -1;
	return 1;
}

// Shut the socket down for both directions, then close it.  Idempotent.
void Rva00804380CloseSocket( Rva008042B0Http *http )
{
	if( http->m_socket != 0 )
	{
		Rva007FD4E0SocketShutdown( http->m_socket, 2 );
		Rva007FD3F0SocketClose( http->m_socket );
	}
	http->m_socket = 0;
}

void Rva008043C0HttpDestroy( Rva008042B0Http *http )
{
	Rva00804380CloseSocket( http );
	Rva007F0030Free( http->m_buffer );
}

// Case-insensitive string compare, folding only A-Z.  The `char` locals are
// signed (movsx at every read), and the loop is a do/while: the terminator is
// compared before the loop can exit, so equal strings return 0.
int Rva00804890StrCaseCmp( const char *left, const char *right )
{
	int diff;
	char cl;
	char cr;

	do
	{
		cl = *left++;
		if( cl >= 'A' && cl <= 'Z' )
			cl ^= 0x20;
		cr = *right++;
		if( cr >= 'A' && cr <= 'Z' )
			cr ^= 0x20;
		diff = cl - cr;
	}
	while( cl != 0 && diff == 0 );

	return diff;
}

// Start one HTTP request.  Reuses the connection only when the host, the port
// and the state all still agree; otherwise it drops the socket and reconnects.
// -1 = host too long for the 0x100-byte field, -2 = request longer than the
// buffer 0x008042B0 allocated.
int Rva008046E0HttpRequest( Rva008042B0Http *http, const char *host, int port,
		const char *request )
{
	if( strlen( host ) >= 0x100 )
		return -1;
	if( strlen( request ) + 1 > http->m_bufferSize )
		return -2;

	if( Rva00804890StrCaseCmp( host, http->m_host ) != 0 || port != http->m_port )
	{
		Rva00804380CloseSocket( http );
		http->m_state = 0;
	}
	if( http->m_state != 7 || http->m_field124 != 0 || http->m_socket == 0 )
	{
		Rva00804380CloseSocket( http );
		http->m_state = 0;
	}

	strcpy( http->m_buffer, request );
	Rva007FE780Printf( "HTTP request:\n%s\n", http->m_buffer );
	http->m_field144 = 3;

	if( http->m_state == 7 && Rva00804890StrCaseCmp( host, http->m_host ) == 0
			&& port == http->m_port )
	{
		http->m_state = 3;
	}
	else
	{
		strcpy( http->m_host, host );
		http->m_port = port;
		http->m_conn = Rva007FDFF0Connect( http->m_host, 0x1E );
		http->m_field10C = 0;
		http->m_state = 1;
	}

	http->m_httpCode = 0;
	Rva00804920Update( http );
	return 0;
}

// The ProtoMangle module record ProtoMangleCreate allocates 0x214 bytes for.
// Every field name below is derived from the log line or the format specifier
// the byte is fed to; the OFFSETS are the evidence.
struct Rva00804150ProtoMangleRef
{
	void            *m_socket;          // +0x000
	// THE CALLER'S SOCKET, and 0x008053C0 is what says so: it stores its own
	// socket argument here and then queries THAT for its bound address.  It is
	// also the counterweight ProtoMangleDestroy compares +0x00 against before
	// closing it -- a socket the caller handed in must not be closed on the
	// caller's behalf, which is exactly what that guard buys.
	void            *m_userSocket;      // +0x004
	unsigned int     m_localAddr;       // +0x008
	int              m_myPort;          // +0x00C
	// THE TWO PEER FIELDS, named by the tags 0x00805870 parses into them: it
	// pulls "peerIP" out of a response blob, runs it through the dotted-quad
	// parser and stores the result here, then does the same for "peerPort"
	// through atoi.  The names are retail's own tag spellings.
	unsigned int     m_peerAddr;        // +0x010
	int              m_peerPort;        // +0x014
	char             m_sessID[ 0x20 ];  // +0x018
	char             m_gameID[ 0x20 ];  // +0x038
	char             m_lkey[ 0x40 ];    // +0x058
	char             m_server[ 0x20 ];  // +0x098
	int              m_port;            // +0x0B8
	// The status word 0x00805620 writes through a pointer: 0 success, 1 probe,
	// 2 failure, -1 for a response carrying no status at all.
	int              m_status;          // +0x0BC
	Rva008042B0Http  m_http;            // +0x0C0
	int              m_pad208;
	// THE ROLLING LOCAL PORT, not a timeout.  0x00804150 seeds it from the tick
	// as `tick % 8000 + 2000`, which is an ephemeral port range rather than a
	// duration, and 0x00805C70 binds probe sockets to it and steps it as it
	// goes.
	int              m_localPort;       // +0x20C
	// The module's own state.  0x008054A0 dispatches on it being 1 or 4 and
	// writes 2 or 3 back; 0x00804150 leaves it zero.
	int              m_state;           // +0x210
};

// The local address the peer server should see: ask the stack which interface
// reaches 192.168.1.1:79 and read the address back out big-endian.  The two
// byte-at-a-time loops are DirtySock's SockaddrInSetAddr/SockaddrInGetAddr
// macros, which is why the shifts are written into a local rather than kept in
// a register.
struct Rva00804440SockAddr
{
	unsigned short sa_family;
	char           sa_data[ 14 ];
};

unsigned int Rva00804440LocalAddr( void )
{
	Rva00804440SockAddr inet;
	Rva00804440SockAddr host;
	unsigned int work;

	memset( &inet, 0, 16 );
	inet.sa_family = 2;
	inet.sa_data[ 0 ] = 0;
	inet.sa_data[ 1 ] = 0x4F;
	work = 0xC0A80101;
	inet.sa_data[ 5 ] = (char)work; work >>= 8;
	inet.sa_data[ 4 ] = (char)work; work >>= 8;
	inet.sa_data[ 3 ] = (char)work; work >>= 8;
	inet.sa_data[ 2 ] = (char)work;
	memset( &host, 0, 16 );
	Rva007FE310SocketHost( &host, 16, &inet, 16 );
	return ( ( ( ( ( (unsigned char)host.sa_data[ 2 ] << 8 )
			| (unsigned char)host.sa_data[ 3 ] ) << 8 )
			| (unsigned char)host.sa_data[ 4 ] ) << 8 )
			| (unsigned char)host.sa_data[ 5 ];
}

void Rva00804630HttpGet( Rva008042B0Http *http, const char *host, int port,
		const char *url, const char *sessID )
{
	char query[ 0x200 ];

	sprintf( query, "GET %s HTTP/1.1\r\nCookie: sessionID=%s\r\nAccept: */*\r\n"
			"Content-Length: 0\r\nUser-Agent: Custom/1.0\r\nHost: %s\r\n\r\n",
			url, sessID, host );
	Rva008046E0HttpRequest( http, host, port, query );
}

void Rva00804550RequestPeerAddress( Rva00804150ProtoMangleRef *ref )
{
	char strUrl[ 0x100 ];

	sprintf( strUrl, "/getPeerAddress?myIP=%s&myPort=%d&version=1.0",
			Rva007FFB50AddrText( ref->m_localAddr ), ref->m_myPort );
	Rva00804630HttpGet( &ref->m_http, ref->m_server, ref->m_port, strUrl, ref->m_sessID );
	ref->m_state = 1;
}

void Rva008043F0Connect( Rva00804150ProtoMangleRef *ref, int myPort, const char *sessID )
{
	ref->m_localAddr = Rva00804440LocalAddr();
	ref->m_myPort = myPort;
	Rva00804250CopyField( ref->m_sessID, sessID, 0x20 );
	Rva00804550RequestPeerAddress( ref );
}

// 0x007FEA00, the no-argument tick forwarder already converted in
// Y4DirtySockSocket.c; ProtoMangleCreate seeds its timeout from it.
unsigned int Rva007FEA00Tick( void );

// ---------------------------------------------------------------- public
// The two bodies retail names itself, moved here out of protomangle.cpp, where
// they were byte lifts rather than source.  Both were readable all along -- a
// lift reproduces the bytes by construction and converts nothing -- and this
// file already carries every struct and callee they need.
extern "C" {

// THE ARGUMENT LIST COMES OUT OF THE LOG LINE, not out of the frame.  Retail's
// own format is "ProtoMangleCreate: Server:%s Port:%d GameID:%s LKey:%s\n" and
// the four stack slots are pushed in exactly that order, so the names and the
// types are retail's rather than address-derived.  Where each one lands
// afterwards agrees: the server string goes to +0x98, the port to +0xB8, the
// game id to +0x38 and the key to +0x58 with a 0x40 bound, which is the only
// field wide enough to be a key.
//
// THE NULL DEREFERENCE IS RETAIL'S AND IS REPRODUCED.  When the sub-object's
// buffer allocation fails, the record is freed and the local set to null -- and
// the very next statement writes the timeout through that null.  A `return 0`
// in the failure arm would be the obvious fix and it is not what the bytes do:
// there is no branch around the store.  It is left exactly as retail has it.
//
// The initial timeout is `tick % 8000 + 2000`, spelled with an unsigned DIV
// because /Od does no strength reduction and the tick is unsigned.
Rva00804150ProtoMangleRef *ProtoMangleCreate( const char *server, int port,
		const char *gameID, const char *lkey )
{
	Rva00804150ProtoMangleRef *ref;

	Rva007FE780Printf( "ProtoMangleCreate: Server:%s Port:%d GameID:%s LKey:%s\n",
			server, port, gameID, lkey );

	ref = (Rva00804150ProtoMangleRef *)Rva007F0000Alloc( 0x214 );
	memset( ref, 0, 0x214 );

	if( Rva008042B0HttpCreate( &ref->m_http, 0x400 ) <= 0 )
	{
		Rva007F0030Free( ref );
		ref = 0;
	}

	ref->m_localPort = Rva007FEA00Tick() % 8000 + 2000;

	Rva00804250CopyField( ref->m_server, server, 0x20 );
	ref->m_port = port;
	Rva00804250CopyField( ref->m_gameID, gameID, 0x20 );
	Rva00804250CopyField( ref->m_lkey, lkey, 0x40 );

	return ref;
}

// Logs "ProtoMangleDestroy: Shutting down\n", then tears the record down in the
// order the bytes give: the record's own socket first -- and only when the two
// pointers at +0x00 and +0x04 disagree -- then the embedded sub-object, then
// the record itself.  The record is handed to the sub-object's socket closer
// unchanged, which is what says the first two words of both objects have the
// same shape.
void ProtoMangleDestroy( Rva00804150ProtoMangleRef *ref )
{
	Rva007FE780Printf( "ProtoMangleDestroy: Shutting down\n" );

	if( ref->m_socket != ref->m_userSocket )
		Rva00804380CloseSocket( (Rva008042B0Http *)ref );

	Rva008043C0HttpDestroy( &ref->m_http );
	Rva007F0030Free( ref );
}

}

// 0x007FDB60, the DirtySock socket query.  0x008053C0 calls it with the
// selector 0x62696E64 -- 'bind' as a multi-character literal, the same
// convention 0x007FDEB0's 'xmap'/'xdns' pair uses -- and a 0x10-byte buffer,
// which is a sockaddr.  The name is address-derived; the selector is evidence.
void Rva007FDB60SocketInfo( void *socket, int selector, void *buffer,
		int bufferSize );  // 0x007FDB60

// 0x008053C0 is the CONNECT entry, and it logs itself: "protomangle: connecting
// with sockref 0x%08x\n".  What it does with that sockref is what names +0x04 --
// it stores the caller's socket there and immediately asks THAT socket for its
// bound address, so the record keeps the caller's socket separately from its
// own.  ProtoMangleDestroy's otherwise puzzling +0x00 versus +0x04 comparison is
// an ownership test once that is known.
//
// THE PORT IS BIG-ENDIAN AND IS READ AS TWO BYTES, not as a swapped short:
// bytes 2 and 3 of the sockaddr are each widened with movzx and folded with a
// shift and an or.  That is the same SockaddrInGetPort spelling 0x00804440 uses
// for the address, and reading it as a short and swapping does not reproduce it.
//
// The frame is 0x1C: cookie, guard, the 0x10 buffer /GZ names `SockAddr`,
// guard.  Nothing else is on the stack.
void Rva008053C0Connect( Rva00804150ProtoMangleRef *ref, void *socket,
		const char *sessID )
{
	char SockAddr[ 0x10 ];

	Rva007FE780Printf( "protomangle: connecting with sockref 0x%08x\n", socket );

	ref->m_localAddr = Rva00804440LocalAddr();
	ref->m_userSocket = socket;

	Rva007FDB60SocketInfo( ref->m_userSocket, 'bind', SockAddr, 0x10 );
	ref->m_myPort = ( (unsigned char)SockAddr[ 2 ] << 8 )
			| (unsigned char)SockAddr[ 3 ];

	Rva00804250CopyField( ref->m_sessID, sessID, 0x20 );
	Rva00804550RequestPeerAddress( ref );
}

// A one-line reader for the sub-object's +0x11C, reached through the record at
// +0x1DC -- 0xC0 + 0x11C, which is what ties the two structs together here.  It
// takes no frame beyond ebp and makes no call, so /GZ leaves it alone.  What it
// reads is the HTTP response code: 0x008054A0 compares this call against 400
// and against 200.
int Rva00805610HttpCode( Rva00804150ProtoMangleRef *ref )
{
	return ref->m_http.m_httpCode;
}

// The two callees 0x00805870 needs, both address-derived and both pinned.
// 0x00805710 copies one named tag out of a text blob into a bounded buffer and
// returns negative when the tag is absent; 0x007FFC10 turns a dotted quad into
// an address.
int  Rva00805710TagFieldGet( char *dest, int destSize, const char *text,
		const char *tag, int flags );          // 0x00805710
unsigned int Rva007FFC10TextAddr( const char *text );  // 0x007FFC10

// Called directly through the import stub at 0x009F6DEE rather than through
// __imp__atoi, so this TU did not see <stdlib.h> either.
extern "C" int atoi( const char *text );

// 0x00805870 PARSES THE PEER OUT OF A RESPONSE, and its two tag strings name
// the fields it fills: "peerIP" through the dotted-quad parser into +0x10, and
// "peerPort" through atoi into +0x14.  Neither field had a name before this
// body; both now have retail's own.
//
// THE RETURN IS AN ALL-OR-NOTHING TEST, not a count.  Retail counts the two
// successes into a local and then returns `count == 2` through a sete -- so a
// response carrying only one of the two tags reports failure, and the caller
// cannot tell which half arrived.  A blank address is treated as absent even
// when the tag parsed, which is why the first arm counts only after checking
// the stored value; the port arm has no such check and counts unconditionally.
//
// The frame is 0x30: cookie, guard, the 0x20 buffer /GZ names `strParm`, guard,
// the counter.  strParm is declared first; the other order moves the guarded
// pair and every offset with it.
int Rva00805870ParsePeer( Rva00804150ProtoMangleRef *ref, const char *text )
{
	char strParm[ 0x20 ];
	int count;

	count = 0;

	if( Rva00805710TagFieldGet( strParm, 0x20, text, "peerIP", 0 ) >= 0 )
	{
		ref->m_peerAddr = Rva007FFC10TextAddr( strParm );
		if( ref->m_peerAddr != 0 )
			++count;
	}

	if( Rva00805710TagFieldGet( strParm, 0x20, text, "peerPort", 0 ) >= 0 )
	{
		ref->m_peerPort = atoi( strParm );
		++count;
	}

	return count == 2;
}

// The two bodies 0x008054A0 dispatches to that live elsewhere.  0x00805620 is
// the status-line parser in Y2ProtoMangleTagField.cpp; 0x00805960 is still a
// dump and is pinned by address.
const char *Rva00805620ParseStatus( const char *text, int *status );  // 0x00805620
int Rva00805960( Rva00804150ProtoMangleRef *ref, const char *text );  // 0x00805960
// Also in Y2ProtoMangleTagField.cpp: finds a marker and steps past newlines.
const char *Rva00805830SkipNewlines( const char *text, const char *find );
// Three more DirtySock callees, all C++ spellings of bodies converted in
// Y4DirtySockSocket.c.
void *Rva007FD2D0SocketOpen( int family, int type, int protocol );
int   Rva007FD510Bind( void *socket, const void *addr, int addrLen );
void  Rva007FDB60SocketInfo( void *socket, int selector, void *buffer,
		int bufferSize );
int   Rva007FD920Send( void *socket, const char *buffer, int length,
		int flags, const char *to, int toLength );

// 0x008054A0 IS THE MODULE'S STATE MACHINE, driven by whatever the HTTP
// sub-object has finished.  It runs at most two steps per call: state 1 reads a
// response and decides what the peer said, state 4 reads a second response and
// grades it by HTTP code alone.
//
// THE STATUS DISPATCH IS A SWITCH WITH A DELIBERATE FALLTHROUGH.  Case 1 --
// "probe" -- calls the probe handler and, when that reports negative, drops
// into the default arm's `state = 3` rather than jumping past it: retail's
// `jl` targets the default's own store, not a copy of it.  Writing the failure
// arm out separately duplicates that store and does not reproduce the bytes.
//
// TWO CONDITIONAL STORES ARE SPELLED DIFFERENTLY AND BOTH SPELLINGS ARE
// RETAIL'S.  The peer result becomes 2 or 3 through `neg`/`sbb`, which is what
// MSVC emits for a ternary between two constants one apart; the HTTP code
// becomes 2 or 3 through `setne` and an add, which is what it emits for a
// comparison used as a number.  Swapping the two forms changes six bytes.
//
// THERE IS NO STATUS LOCAL.  The frame is two slots: the response body and
// MSVC's own switch temporary, which is what the load from +0xBC into -8 is.
// Reading the status into a named local first adds a third slot and moves
// every offset in the body.
//
// The 400-or-stuck check sits OUTSIDE the response test: a state-1 update with
// no body still gets graded, so a stalled HTTP sub-object -- state 8 -- fails
// the module rather than hanging it.
//
// Both log lines are "HTTP Data:\n%s\n" and they are TWO SEPARATE
// LITERALS at 0x012C42A4 and 0x012C42B4.  Retail wrote the string twice and the
// build did not pool it, so writing it twice is what reproduces the two
// relocations.
void Rva008054A0( Rva00804150ProtoMangleRef *ref )
{
	const char *body;

	if( ref->m_state == 1 )
	{
		body = Rva00804920Update( &ref->m_http );
		if( body != 0 )
		{
			Rva007FE780Printf( "HTTP Data:\n%s\n", body );
			body = Rva00805620ParseStatus( body, &ref->m_status );

			switch( ref->m_status )
			{
			case 0:
				ref->m_state = Rva00805870ParsePeer( ref, body ) ? 2 : 3;
				break;
			case 1:
				if( Rva00805960( ref, body ) >= 0 )
				{
					Rva00804550RequestPeerAddress( ref );
					break;
				}
				// falls through
			default:
				ref->m_state = 3;
				break;
			}
		}

		if( Rva00805610HttpCode( ref ) == 400 || ref->m_http.m_state == 8 )
			ref->m_state = 3;
	}

	if( ref->m_state == 4 )
	{
		body = Rva00804920Update( &ref->m_http );
		if( body != 0 )
		{
			Rva007FE780Printf( "HTTP Data:\n%s\n", body );
			ref->m_state = ( Rva00805610HttpCode( ref ) != 200 ) + 2;
		}
	}
}

// The 0x58-byte block /GZ names `Probe`.  Only the three fields 0x00805960
// touches are evidence: an index and a count it loops between at +0x00 and
// +0x04, and a serial at +0x14 it checks against its own counter.  The rest is
// filled and read by bodies still unconverted.
struct Rva00805960Probe
{
	int  m_index;                // +0x00
	int  m_count;                // +0x04
	// The peer this probe is aimed at, named by 0x00805E50 writing them into a
	// sockaddr's address and port slots.
	unsigned int m_peerAddr;     // +0x08
	int  m_peerPort;             // +0x0C
	// The port to probe, or -1 for "pick one".  0x00805C70 compares it against
	// the module's own port and logs it as "probe port %d".
	int  m_port;                 // +0x10
	int  m_serial;               // +0x14
	// Passed to "tag=%s" in the probe message, so it is text.
	char m_tag[ 0x40 ];          // +0x18
};

// Three neighbours 0x00805960 drives, pinned by address. The first is now
// recovered in Y2ProtoMangleNextProbe.cpp. This call site proves its cdecl
// three-argument interface and the former NAT::doThisConnectionRound ledger
// identity has been corrected. The actual NAT method is at 0x006726B0.
int  Rva00805A70NextProbe( Rva00805960Probe *probe,
		Rva00804150ProtoMangleRef *ref, const char *text );  // 0x00805A70
int  Rva00805C70( Rva00804150ProtoMangleRef *ref, Rva00805960Probe *probe );
void Rva00805E50( Rva00804150ProtoMangleRef *ref, Rva00805960Probe *probe,
		int result, int serial );

// 0x00805960 WALKS THE PROBE LIST in a response, and its own warning names the
// field it checks: "ProtoMangle: Warning, probe sequence mismatch".  It counts
// probes from 1 and compares that counter against the serial the parser put at
// +0x14, so the serials are expected to be dense and in order -- and a mismatch
// is only WARNED about, never acted on.
//
// THE PARSE IS THE LOOP'S CONDITION.  Retail tests the parser's result with a
// single `je` out of the loop and jumps forward past the increment on entry,
// which is a for-loop with a call for a condition; an `if( ... ) break;` inside
// a for(;;) is a byte longer at that test and moves everything after it.
//
// THE TEXT POINTER IS ADVANCED THROUGH THE CALLER'S OWN PARAMETER SLOT, by
// searching for the blank line that separates one probe from the next.  There
// is no bound other than the parser refusing: an input whose separator never
// appears leaves this loop running on the same text.
//
// The inner loop counts through the probe's own +0x00 field rather than a
// local, so the callee at 0x00805E50 can see which entry it is being handed;
// and the only fatal error is a negative from 0x00805C70, which returns -1
// immediately and leaves the rest of the response unread.
int Rva00805960( Rva00804150ProtoMangleRef *ref, const char *text )
{
	Rva00805960Probe Probe;
	int serial;
	int result;

	for( serial = 1; Rva00805A70NextProbe( &Probe, ref, text ) != 0; ++serial )
	{
		if( serial != Probe.m_serial )
			Rva007FE780Printf(
					"ProtoMangle: Warning, probe sequence mismatch\n" );

		result = Rva00805C70( ref, &Probe );
		if( result < 0 )
			return -1;

		for( Probe.m_index = 0; Probe.m_index < Probe.m_count; ++Probe.m_index )
			Rva00805E50( ref, &Probe, result, serial );

		text = Rva00805830SkipNewlines( text, "\n\n" );
	}

	return 0;
}

// 0x00805C70 GETS A SOCKET FOR ONE PROBE, and its four log lines carry the
// whole decision: "tearing down probe socket", "using shared socket ref
// 0x%08x to probe port %d", "Error creating probe socket", "created probe
// socket".  It reuses the CALLER'S socket when there is one and the probe asks
// for the port the module is already on; otherwise it opens a datagram socket
// of its own and binds it.
//
// Any socket left over from a previous probe is closed first, and the test for
// that is `own != caller's` -- the same ownership comparison ProtoMangleDestroy
// makes, which is what stops it closing a socket it was handed.
//
// THE PORT PAIR IS A RETAIL BUG AND IS REPRODUCED.  When the probe asks for any
// port, the high byte is taken from the rolling counter, the counter is
// stepped, the low byte is taken, and the counter is stepped AGAIN -- so the
// two bytes come from different numbers and the counter advances by two per
// probe.  Reading it once into the pair is one instruction shorter and is not
// what the bytes do.
//
// The bound port is read back through the same 'bind' selector 0x008053C0 uses
// and returned big-endian from the two bytes, so the caller learns the port the
// stack actually gave -- which is the point of asking for -1 in the first place.
int Rva00805C70( Rva00804150ProtoMangleRef *ref, Rva00805960Probe *probe )
{
	char bindaddr[ 0x10 ];

	if( ref->m_socket != ref->m_userSocket )
	{
		Rva007FE780Printf(
				"protomangle: tearing down probe socket 0x%08x\n",
				ref->m_socket );
		Rva00804380CloseSocket( (Rva008042B0Http *)ref );
	}

	if( ref->m_userSocket != 0 && probe->m_port == ref->m_myPort )
	{
		Rva007FE780Printf(
				"protomangle: using shared socket ref 0x%08x to probe port %d\n",
				ref->m_userSocket, ref->m_myPort );
		ref->m_socket = ref->m_userSocket;
	}
	else
	{
		ref->m_socket = Rva007FD2D0SocketOpen( 2, 2, 0 );
		if( ref->m_socket == 0 )
		{
			Rva007FE780Printf(
					"ProtoMangle: Error creating probe socket\n" );
			return -1;
		}

		Rva007FE780Printf(
				"protomangle: created probe socket 0x%08x\n",
				ref->m_socket );

		*(unsigned short *)( bindaddr + 0 ) = 2;
		*(unsigned short *)( bindaddr + 2 ) = 0;
		*(int *)( bindaddr + 4 ) = 0;
		*(int *)( bindaddr + 8 ) = 0;
		*(int *)( bindaddr + 12 ) = 0;

		if( probe->m_port != -1 )
		{
			bindaddr[ 2 ] = (char)( probe->m_port >> 8 );
			bindaddr[ 3 ] = (char)probe->m_port;
		}
		else
		{
			bindaddr[ 2 ] = (char)( ref->m_localPort >> 8 );
			ref->m_localPort = ref->m_localPort + 1;
			bindaddr[ 3 ] = (char)ref->m_localPort;
			ref->m_localPort = ref->m_localPort + 1;
		}

		Rva007FD510Bind( ref->m_socket, bindaddr, 0x10 );
	}

	Rva007FDB60SocketInfo( ref->m_socket, 'bind', bindaddr, 0x10 );
	return ( (unsigned char)bindaddr[ 2 ] << 8 ) | (unsigned char)bindaddr[ 3 ];
}

// 0x00805E50 SENDS ONE PROBE, and the message it builds is a tag=value block:
// "sourceIP=%s\r\nsourcePort=%d\r\ntag=%s\r\nsendCount=%d\r\n" -- the same
// shape 0x00805710 reads on the way back in.  Four of the probe block's fields
// get names from it and from the sockaddr it fills: +0x08 and +0x0C are the
// peer's address and port, +0x18 is the tag text, and +0x00 is the send count
// the caller was already using as a loop index.
//
// THE WHOLE MESSAGE IS ONE sprintf WITH A NESTED CALL.  Retail pushes the last
// three arguments, then evaluates the address-to-text helper and pushes its
// result, then the format and the buffer -- MSVC's right-to-left order, which
// is what puts the helper's own argument push and its `add esp,4` in the middle
// of sprintf's argument list.  Splitting it into a temporary does not
// reproduce that.
//
// The length sent is strlen + 1, so the terminator goes on the wire.  Success
// is judged by the byte count matching exactly -- a short send is reported as
// an error with its count, and neither branch returns anything: this body only
// logs.  The printer's return is stored into a local and never read, which is
// retail's and is why that local exists at all.
//
// The trailing line -- "sending probe %d/%d (%d) from port %d\n" -- is
// logged AFTER the send rather than before it, and its third number is the
// serial the caller counts, not anything in the block.
void Rva00805E50( Rva00804150ProtoMangleRef *ref, Rva00805960Probe *probe,
		int sourcePort, int serial )
{
	char peeraddr[ 0x10 ];
	char strMesg[ 0x80 ];
	int sent;
	int length;
	unsigned int work;
	int result;

	*(unsigned short *)( peeraddr + 0 ) = 2;
	*(unsigned short *)( peeraddr + 2 ) = 0;
	*(int *)( peeraddr + 4 ) = 0;
	*(int *)( peeraddr + 8 ) = 0;
	*(int *)( peeraddr + 12 ) = 0;

	work = probe->m_peerAddr;
	peeraddr[ 7 ] = (char)work;  work >>= 8;
	peeraddr[ 6 ] = (char)work;  work >>= 8;
	peeraddr[ 5 ] = (char)work;  work >>= 8;
	peeraddr[ 4 ] = (char)work;
	peeraddr[ 2 ] = (char)( probe->m_peerPort >> 8 );
	peeraddr[ 3 ] = (char)probe->m_peerPort;

	sprintf( strMesg,
			"sourceIP=%s\r\nsourcePort=%d\r\ntag=%s\r\nsendCount=%d\r\n",
			Rva007FFB50AddrText( ref->m_localAddr ), sourcePort, probe->m_tag,
			probe->m_index );

	length = strlen( strMesg ) + 1;
	sent = Rva007FD920Send( ref->m_socket, strMesg, length, 0, peeraddr, 0x10 );

	if( sent == length )
		result = Rva007FE780Printf( "ProtoMangle: Success " );
	else
		result = Rva007FE780Printf( "ProtoMangle: Error %d ", sent );

	Rva007FE780Printf( "sending probe %d/%d (%d) from port %d\n",
			probe->m_index, probe->m_count, serial, sourcePort );
}

// 0x00806200 is 0x00804630's POST counterpart and its format says so outright:
// the same request line, cookie and Host header, plus a content type, a
// Content-Length and a body.  The length is strlen of that body, computed
// INSIDE the sprintf argument list -- MSVC evaluates right to left, so retail's
// strlen call and its `add esp,4` land between the last argument's push and the
// next one's, which is what says it was written there rather than hoisted.
//
// The body is passed twice: once to strlen and once as the last %s.  Both are
// the same parameter, so a caller that hands in a buffer it mutates between
// them would be reporting one length and sending another; nothing here guards
// against that.
void Rva00806200HttpPost( Rva008042B0Http *http, const char *host, int port,
		const char *url, const char *sessID, const char *body )
{
	char query[ 0x200 ];

	sprintf( query,
			"POST %s HTTP/1.1\r\nCookie: sessionID=%s\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: %d\r\nHost: %s\r\n\r\n%s\r\n",
			url, sessID, strlen( body ), host, body );
	Rva008046E0HttpRequest( http, host, port, query );
}

// The two words the connection status can carry, read out of retail's .rdata
// at 0x012C3D4C and 0x012C3D58 with the pointer table indexing them at
// 0x012C3D60.  There are exactly two, which is what the caller's `> 1` reject
// is guarding.
static const char *s_connectionStatus[ 2 ] = { "connected", "failed" };

// 0x008060B0 REPORTS THE RESULT back to the server as a POST to
// "/connectionStatus", and its two format strings are the whole shape:
// "myIP=%s&myPort=%d&version=1.0&status=%s&gameFeatureID=%s\n" with an
// optional "&latency=%d" appended.
//
// THE PORT IT CALLS "myPort" IS THE ONE AT +0x14, the field the peer
// reported back through 0x00805870, not the module's own at +0x0C that
// 0x00804550 uses under the same name.  That is not a slip to tidy up: after
// the probes, the port the peer saw IS this side's externally visible port, and
// it is the one the server needs.
//
// The latency is appended only when it is not negative, through a second
// buffer and a strcat rather than a second format -- so a caller with no
// latency to report passes anything below zero and the field is simply absent.
//
// The state goes to 4 on the way out, which is the arm of 0x008054A0 that
// grades a response by HTTP code alone: nothing more is parsed after this.
int Rva008060B0( Rva00804150ProtoMangleRef *ref, int status, int latency )
{
	char strData[ 0x80 ];
	char strData2[ 0x20 ];

	if( status > 1 )
		return -1;

	sprintf( strData,
			"myIP=%s&myPort=%d&version=1.0&status=%s&gameFeatureID=%s\n",
			Rva007FFB50AddrText( ref->m_localAddr ), ref->m_peerPort,
			s_connectionStatus[ status ], ref->m_gameID );

	if( latency >= 0 )
	{
		sprintf( strData2, "&latency=%d", latency );
		strcat( strData, strData2 );
	}

	Rva00806200HttpPost( &ref->m_http, ref->m_server, ref->m_port,
			"/connectionStatus", ref->m_sessID, strData );
	ref->m_state = 4;
	return 0;
}

// 0x00806040 IS THE POLL, and it reads as one because of what it does with the
// state rather than because of its shape.  State 2 is done and succeeded: it
// closes the probe socket, hands back the peer address and port the probes
// established, and reports 1.  States 1 and 4 are the two the machine at
// 0x008054A0 drives, so they report 0 for "still running".  Anything else --
// including the 3 that every failure path writes -- is -1.
//
// THE TWO OUT POINTERS ARE ALL-OR-NOTHING: both are tested and neither is
// written unless both are non-null, so a caller that wants only the port still
// has to supply somewhere for the address.  The socket is closed either way,
// which means a caller polling with two nulls still ends the probe.
int Rva00806040( Rva00804150ProtoMangleRef *ref, unsigned int *addr, int *port )
{
	if( ref->m_state == 2 )
	{
		Rva00804380CloseSocket( (Rva008042B0Http *)ref );

		if( addr != 0 && port != 0 )
		{
			*addr = ref->m_peerAddr;
			*port = ref->m_peerPort;
		}
		return 1;
	}

	if( ref->m_state == 1 || ref->m_state == 4 )
		return 0;

	return -1;
}
