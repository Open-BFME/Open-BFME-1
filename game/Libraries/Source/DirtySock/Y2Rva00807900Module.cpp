// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// EA's DirtySock again -- a module in the 0x00807900..0x00808600 span that the
// bytes do NOT name.  Every body here opens a frame for code with no register
// pressure, fills its locals with 0xCCCCCCCC and ends `cmp ebp,esp` into the
// stack-check helper at 0x009F7502, which is the same /Od /GZ signature the
// other files in this directory carry, and the only string reachable from the
// whole span is "$%08x".  The directory and the file name are therefore
// inferences; every function name below is derived from an address and asserts
// nothing about identity.
//
// WHAT THE SPAN DOES SAY ABOUT ITSELF: 0x00807A00 logs a line beginning
// "dirtyaddr: output buffer too small", which is DirtySock naming its address
// module by its own source file.  That covers the three bodies here that
// convert an address between its binary and "$%08x" text forms; it says
// nothing about the other two, which is why the file is still named for its
// address.
//
// sprintf is reached by a DIRECT rel32 to the import stub at 0x009F6DE2 rather
// than through __imp__sprintf, so this TU did not see <stdio.h> -- the same
// reason Y2ProtoMangleHelpers.cpp declares it itself.
extern "C" int sprintf( char *buffer, const char *format, ... );

// ------------------------------------------------------------------ callees
// Addresses read from the REL32 at the call sites; each is pinned in
// targets/game/reverse/symbols.csv and derived from its address.
struct Rva00807BA0Ping;

void *Rva007FDFF0Connect( const char *host, int timeout );  // 0x007FDFF0
int   Rva00807960( const char *host, int timeout );         // 0x00807960
unsigned int Rva007FF9F0Swap32( unsigned int value );       // 0x007FF9F0
// NetConnStatus -- the body at 0x007EB410 names itself in its own warning.
int Rva007EB410NetConnStatus( int selector, void *buffer, int bufferSize );
unsigned int Rva007FFAD0( unsigned int value );             // 0x007FFAD0

// Both reached by a direct rel32 to their import stubs, like sprintf above.
extern "C" unsigned int strtoul( const char *text, char **end, int base );
extern "C" void *memcpy( void *dest, const void *src, unsigned int count );

int  Rva007FE780Printf( const char *format, ... );          // 0x007FE780
int  Rva00808220( Rva00807BA0Ping *ping, unsigned int address,
		const char *text, int length, int id );             // 0x00808220
void Rva007FD3F0SocketClose( void *socket );                // 0x007FD3F0
void Rva007F0030Free( void *block );                        // 0x007F0030
void Rva007FEAA0ListReset( void *list );                    // 0x007FEAA0
void *Rva007FD2D0SocketOpen( int family, int type, int protocol ); // 0x007FD2D0
int   Rva007FD510Bind( void *socket, const void *addr, int addrLen ); // 0x007FD510
void  Rva007FEA20ListInit( void *list );                    // 0x007FEA20
int   Rva007FDE80SetCallback( void *socket, int callback, unsigned int rate,
		void *data, void *proc );                           // 0x007FDE80
int   Rva00807CF0( void *socket, int reason, void *data ); // 0x00807CF0 callback
int   Rva007FDA50Recv( void *socket, char *buffer, int length, int flags,
		char *from, int *fromLength );                      // 0x007FDA50
void  Rva007FEBD0Lock( void *lock );                        // 0x007FEBD0
void  Rva007FECB0Unlock( void *lock );                      // 0x007FECB0
int   Rva007FD920Send( void *socket, const char *buffer, int length,
		int flags, const char *to, int toLength );          // 0x007FD920
unsigned int Rva007FEA00Tick( void );                       // 0x007FEA00
extern "C" unsigned int strlen( const char *text );
void *Rva007F0000Alloc( int size );                         // 0x007F0000
extern "C" void *memset( void *dest, int value, unsigned int count );

// Two 28-byte forwarders that do nothing but pass their two arguments through
// and let /GZ check the frame afterwards.  They are separate functions rather
// than one, and separate from their callees, which is all the bytes say.
void *Rva00807920( const char *host, int timeout )
{
	return Rva007FDFF0Connect( host, timeout );
}

int Rva00807940( const char *host, int timeout )
{
	return Rva00807960( host, timeout );
}

// 0x008081C0 IS A SWITCH WITH ONE CASE, and the copy into a stack temp is what
// says so: MSVC spills a switch expression to its own slot at /Od, while an
// `if` compares the parameter where it sits.  The single selector is
// 0x74746C76, i.e. the multi-character literal 'ttlv' -- the same DirtySock
// control-selector convention 0x007FDEB0's 'xmap'/'xdns' pair and 0x008053C0's
// 'bind' use -- and it stores its third argument at +0x38.  The receiver's
// layout is not known here, so the store is written through the address rather
// than given an invented field name.
void Rva008081C0( void *ref, int selector, int value )
{
	switch( selector )
	{
	case 'ttlv':
		*(int *)( (char *)ref + 0x38 ) = value;
		break;
	}
}

// 0x00807AB0 FORMATS A DWORD AS "$%08x", and the guard in front of it is an
// ALIGNMENT test: the source pointer is rejected when it is null OR when its
// low two bits are set, so the dword is read directly rather than byte-wise.
// Both rejections share one `return 0`, which is why retail's second test jumps
// FORWARD over that return instead of into it -- the `||` shape, not `&&`.
//
// The value passes through 0x007FF9F0 on the way.  Its sibling at 0x007FFAD0,
// already ledgered, is a byte swap over the same one-dword-in one-dword-out
// shape; nothing in THIS body proves that is what happens here, only that the
// value is transformed before it is printed.
int Rva00807AB0( char *dest, const void *src )
{
	unsigned int value;

	if( src == 0 || ( (unsigned int)src & 3 ) != 0 )
		return 0;

	value = Rva007FF9F0Swap32( *(const unsigned int *)src );
	sprintf( dest, "$%08x", value );
	return 1;
}

// 0x00807B10 asks NetConnStatus at 0x007EB410 for the selector 0x61646472
// -- 'addr' -- and runs the answer straight through the formatter above.  /GZ
// names the local uLocalAddr and guards it on both sides because its address is
// taken, which is what makes the frame 0x0C rather than 0x04.  The return is a
// constant 1: this body cannot fail, and does not look at whether either
// callee did.
int Rva00807B10( char *dest )
{
	unsigned int uLocalAddr;

	uLocalAddr = Rva007EB410NetConnStatus( 'addr', 0, 0 );
	Rva00807AB0( dest, &uLocalAddr );
	return 1;
}

// 0x00807A00 IS THE INVERSE of the two bodies above: it reads a "$xxxxxxxx"
// text form back into four bytes.  The parse starts at text + 1, which is what
// skips the '$' the formatter writes, and it is base 16; the result goes
// through the same transform at 0x007FFAD0 that the sibling at 0x007FF9F0
// applies in the other direction.
//
// THE RETURN IS A CHARACTER COUNT, NOT A STATUS.  Nine is exactly the width of
// "$" plus eight hex digits, so the caller is being told how much text was
// consumed; the failure arm returns zero for the same reason.  That failure is
// a BUFFER check and not an input check -- the only thing tested is that the
// caller offered four bytes, and it is the check that logs the module's name.
//
// The address is copied out with memcpy rather than stored, so the destination
// needs no alignment -- the opposite of the guard 0x00807AB0 puts on its own
// source pointer, and worth noticing because the two are a pair.
int Rva00807A00( void *dest, int destSize, const char *text )
{
	unsigned int uAddress;

	if( destSize < 4 )
	{
		Rva007FE780Printf( "dirtyaddr: output buffer too small\n" );
		return 0;
	}

	uAddress = strtoul( text + 1, 0, 16 );
	uAddress = Rva007FFAD0( uAddress );
	memcpy( dest, &uAddress, 4 );
	return 9;
}

// THREE wrappers over the 841-byte body at 0x00808220, and the differences
// between them are the whole point.  0x00808630, at the end of this file,
// appends a ONE where these two append a zero -- and that one is the byte the
// echo request writes at +0x18, which 0x00807FB0 reads back and prints as
// "server=%s".  A request sent that way is marked as coming from the server,
// and the reply says so; neither end alone could explain that field.
//
// These two both append a zero, and differ only in how the address arrives:
// 0x008085A0 first runs the text form through the parser above and passes what
// came out, while 0x008081F0 passes its caller's second argument straight
// through.  So the pair is one entry point in a binary flavour and a text
// flavour, which is also why the parser's nine-character return is discarded
// here -- the caller of the text flavour never sees it.
int Rva008081F0( Rva00807BA0Ping *ping, unsigned int address,
		const char *text, int length )
{
	return Rva00808220( ping, address, text, length, 0 );
}

int Rva008085A0( Rva00807BA0Ping *ping, const char *address,
		const char *text, int length )
{
	unsigned int uAddress;

	Rva00807A00( &uAddress, 4, address );
	return Rva00808220( ping, uAddress, text, length, 0 );
}

// The record 0x00808140 tears down.  Only the three offsets that body touches
// are evidence: a socket at +0x00, something 0x007FEAA0 resets at +0x0C, and a
// singly linked list at +0x30 whose nodes link through their own first word.
// The span between is padding here and names nothing.
struct Rva00808140Node
{
	Rva00808140Node *m_next;         // +0x00
};

struct Rva00808140Ref
{
	void            *m_socket;       // +0x00
	int              m_pad04;
	int              m_pad08;
	char             m_sub0C[ 0x24 ];// +0x0C
	Rva00808140Node *m_list;         // +0x30
};

// 0x00808140 IS A DESTRUCTOR, and the ORDER is what it says: close the socket
// first, then drain the list, then tear down the sub-object at +0x0C, then free
// the record itself.  Nothing is nulled on the way out, so this is the last
// thing that ever touches the record.
//
// THE WHOLE BODY IS WRAPPED IN A NULL CHECK RATHER THAN GUARDED BY AN EARLY
// RETURN.  Retail's is one `je` over everything; an early return compiles to a
// short `jne` over a `jmp`, two instructions where retail has one, and shifts
// every displacement after it.
//
// The drain re-reads the head each time round instead of walking a cursor --
// it unlinks the first node, frees it, and tests the head again -- so the list
// is left consistent at every step even though nothing else can see it.
void Rva00808140( Rva00808140Ref *ref )
{
	Rva00808140Node *node;

	if( ref != 0 )
	{
		Rva007FD3F0SocketClose( ref->m_socket );

		while( ref->m_list != 0 )
		{
			node = ref->m_list;
			ref->m_list = node->m_next;
			Rva007F0030Free( node );
		}

		Rva007FEAA0ListReset( ref->m_sub0C );
		Rva007F0030Free( ref );
	}
}

// The object 0x007FDFF0 hands back.  Two of its words are CALLED with the
// object itself as the only argument and the stack cleaned by the caller, so
// they are __cdecl function pointers and not a C++ vtable -- a thiscall slot
// would pass the object in ecx and pop nothing.  Only the three offsets
// 0x00807960 touches are evidence.
struct Rva00807960Conn;
typedef int ( __cdecl *Rva00807960Proc )( Rva00807960Conn *conn );

struct Rva00807960Conn
{
	int             m_pad00;
	int             m_result;       // +0x04
	Rva00807960Proc m_poll;         // +0x08
	Rva00807960Proc m_close;        // +0x0C
};

__declspec(dllimport) void __stdcall Rva01358F30Sleep( unsigned int ms );

// 0x00807960 IS THE BLOCKING FORM of the connect at 0x007FDFF0, which is
// itself non-blocking: it starts the connection, then spins on the object's
// own poll until that reports non-zero, sleeping ten milliseconds between
// tries, and only then reads the result out of +0x04 and closes.
//
// THE SLEEP IS UNCONDITIONAL AND THERE IS NO DEADLINE.  The timeout argument
// goes to the connect and is never looked at again here, so if the poll never
// succeeds this loop never ends -- whatever bounds it lives inside the object,
// not in this body.
//
// The result is read BEFORE the close and the close's own return is dropped,
// so the object is expected to still be readable at that point and the caller
// learns nothing about whether tearing it down worked.  On a failed connect
// the zero the function starts with is what comes back, which is the same
// value a poll that succeeded with a zero result would give.
int Rva00807960( const char *host, int timeout )
{
	Rva00807960Conn *conn;
	int result;

	result = 0;
	conn = (Rva00807960Conn *)Rva007FDFF0Connect( host, timeout );

	if( conn != 0 )
	{
		while( conn->m_poll( conn ) == 0 )
			Rva01358F30Sleep( 10 );

		result = conn->m_result;
		conn->m_close( conn );
	}

	return result;
}

// The record 0x00807BA0 builds.  Only the offsets it writes are evidence:
// the socket at +0x00, a one at +0x04, a list object at +0x0C that the same
// initialiser 0x007FEA20 sets up everywhere else, and two constants at +0x34
// and +0x38.  0x3C is the allocation size, so the tail is real, not padding.
struct Rva00807EE0Entry;

struct Rva00807BA0Ping
{
	void *m_socket;              // +0x00
	// The ICMP sequence number: set to 1 when the record is made, stepped by
	// 0x00808220 on every request, split into the packet's two sequence bytes
	// and handed back to that caller as its request id.
	int   m_sequence;            // +0x04
	int   m_pad08;
	// The object 0x007FEA20 initialises and 0x007FEBD0/0x007FECB0 take and
	// release around every mutation of the list below it.
	char  m_lock0C[ 0x24 ];      // +0x0C .. +0x2F
	// Head of the result list, walked to its tail by 0x00807CF0.  It sits
	// INSIDE what an earlier reading of this struct called the list object;
	// 0x00807CF0 taking the lock at +0x0C and the head at +0x30 separately
	// is what splits them.
	Rva00807EE0Entry *m_list;    // +0x30
	int   m_credits;             // +0x34
	// The IP header's TTL byte.  0x00807BA0 sets it to 0x40 and 0x00808220
	// copies its low byte into the packet at +0x08, which is where a TTL
	// lives -- and a settable TTL is what makes this module a traceroute.
	int   m_ttl;                 // +0x38
};

// 0x00807BA0 OPENS A RAW ICMP SOCKET, and the three immediates handed to the
// socket open say exactly that: family 2 is AF_INET, type 3 is SOCK_RAW and
// protocol 1 is IPPROTO_ICMP.  That, with the 0x424 `echo` and `response`
// buffers /GZ names in the two bodies this one wires together, is what makes
// this span a ping module rather than a general socket one.
//
// THE BIND ADDRESS IS BUILT TWICE OVER, and both passes are retail's.  The
// family and port are written as words and the rest as dwords, and then the
// two port BYTES are written again individually -- zero then one, i.e. port 1
// big-endian.  Rewriting the same two bytes a second time is redundant and is
// in the bytes; folding it into the word store above does not reproduce them.
//
// The callback installed on the socket is 0x00807CF0 at a 5000-unit rate, and
// the record itself is the user data -- so the receive half of this module is
// reached from here and nowhere else.
//
// A FAILED ALLOCATION AND A FAILED SOCKET RETURN THE SAME NULL, and the socket
// is NOT closed on the allocation path: the local holding it simply goes out
// of scope.  That is a leak and it is retail's.
Rva00807BA0Ping *Rva00807BA0( void )
{
	Rva00807BA0Ping *ping;
	void *sock;
	char bind[ 0x10 ];

	ping = 0;
	sock = Rva007FD2D0SocketOpen( 2, 3, 1 );

	if( sock != 0 )
	{
		*(unsigned short *)( bind + 0 ) = 2;
		*(unsigned short *)( bind + 2 ) = 0;
		*(int *)( bind + 4 ) = 0;
		*(int *)( bind + 8 ) = 0;
		*(int *)( bind + 12 ) = 0;
		bind[ 2 ] = 0;
		bind[ 3 ] = 1;

		Rva007FD510Bind( sock, bind, 0x10 );

		ping = (Rva00807BA0Ping *)Rva007F0000Alloc( 0x3C );
		if( ping != 0 )
		{
			memset( ping, 0, 0x3C );
			ping->m_socket = sock;
			ping->m_sequence = 1;
			ping->m_credits = 8;
			ping->m_ttl = 0x40;

			Rva007FEA20ListInit( ping->m_lock0C );
			Rva007FDE80SetCallback( ping->m_socket, 2, 5000, ping,
					(void *)Rva00807CF0 );
		}
	}

	return ping;
}

// THE MODULE NAMES ITSELF HERE.  0x00807EE0 logs "_ProtoPingCallback:
// ICMP_TIMEEXCEEDED from=%08x" -- so the raw ICMP socket opened at 0x00807BA0,
// the callback it installs, and the 0x424 echo and response buffers /GZ names
// around them are DirtySock's protoping, and the TIMEEXCEEDED path makes this
// module a traceroute and not only a ping.
//
// The constant stored at +0x14 is 0x0B, which is ICMP type 11, TIME EXCEEDED --
// the same thing the log line says in words.  That names +0x14 the ICMP type,
// and 0x00807FB0 confirms it by storing 0 there, ICMP ECHOREPLY.  The other
// field names come from that body's log line rather than from this one.
//
// The address and the port are read BYTE BY BYTE, big-endian, straight out of
// the packet at +0x0C and +0x1A -- not swapped from a word -- which is the same
// SockaddrIn spelling the rest of this library uses, and the address is what
// the log's "from=%08x" prints.
//
// The entry is 0x18 bytes of header plus whatever the caller asked for, and
// the SECOND ARGUMENT IS NEVER READ.  It is retail's; dropping it from the
// signature changes every caller's stack.
struct Rva00807EE0Entry
{
	Rva00807EE0Entry *m_next;       // +0x00
	int               m_sequence;   // +0x04
	unsigned int      m_from;       // +0x08
	int               m_elapsed;    // +0x0C
	int               m_length;     // +0x10
	unsigned char     m_icmpType;   // +0x14
	unsigned char     m_server;     // +0x15
	// The payload starts at +0x16, not at +0x18: 0x00807FB0 copies into
	// `entry + 0x16` while allocating 0x18 more than it copies, so the last
	// two header bytes are slack the allocation pays for and nothing uses.
	unsigned char     m_pad16;
	unsigned char     m_pad17;
};

Rva00807EE0Entry *Rva00807EE0( const unsigned char *packet, void *unused,
		int payload )
{
	Rva00807EE0Entry *entry;

	entry = (Rva00807EE0Entry *)Rva007F0000Alloc( payload + 0x18 );
	if( entry != 0 )
	{
		entry->m_next = 0;
		entry->m_from = ( packet[ 0x0C ] << 24 ) | ( packet[ 0x0D ] << 16 )
				| ( packet[ 0x0E ] << 8 ) | packet[ 0x0F ];
		entry->m_elapsed = 0;
		entry->m_sequence = ( packet[ 0x1A ] << 8 ) | packet[ 0x1B ];
		entry->m_length = 0;
		entry->m_server = packet[ 0x18 ];
		entry->m_icmpType = 0x0B;

		Rva007FE780Printf(
				"_ProtoPingCallback: ICMP_TIMEEXCEEDED from=%08x\n",
				entry->m_from );
	}

	return entry;
}

// 0x00807FB0 IS THE ECHO REPLY HALF, and its log line spells the record out:
// "_ProtoPingCallback: ICMP_ECHOREPLY from=%08x, time=%dms, data=%s,
// server=%s".  Four of the entry's fields are named by that one string --
// +0x08 is the address, +0x0C is a time in milliseconds, +0x16 onward is text,
// and +0x15 selects between "true" and "false" for a `server` flag.  It also
// stores 0 at +0x14, ICMP ECHOREPLY, against the 0x0B the TIMEEXCEEDED body
// stores there.
//
// THE PAYLOAD IS AUTHENTICATED BY A MAGIC WORD before anything is allocated:
// the dword at packet + 0x1C must equal 0x67535073, which is the literal
// 'gSPs' and reads "sPSg" in memory order.  A reply that does not carry it is
// dropped, so this module ignores echo replies it did not send.
//
// THE TIME IS A SUBTRACTION OF TWO STAMPS AND BOTH ARE IN THE PACKETS.  The
// arrival stamp is read big-endian out of the FROM ADDRESS at +0x08 -- which is
// exactly where 0x007FDA50 writes the tick it receives a datagram at, so this
// body is reading a field the socket layer stamped -- and the send stamp is a
// plain dword the sender put in its own payload at +0x20.
//
// A ZERO ELAPSED TIME IS FORCED TO 1 AFTER IT HAS BEEN LOGGED, so the log can
// print 0ms while the caller never sees a zero.  That ordering is retail's and
// it means the printed value and the stored value can differ by one.
//
// The 0x400 bound and the 0x24 header are checked on the length BEFORE the
// magic word, and the length is decremented in the caller's own parameter
// slot; a negative result and an oversized one share the same `return 0`.
//
// Two spellings had to be measured.  `entry` is declared BEFORE `server`, so
// it takes the slot next to the frame pointer; the other order moves both.
// And the elapsed time is ONE expression -- the subtraction folded into the
// same statement as the four byte reads -- because writing it as an assignment
// followed by a `-=` stores the sum, reloads it and stores again, twelve bytes
// retail does not have.
Rva00807EE0Entry *Rva00807FB0( const unsigned char *packet,
		const unsigned char *from, int length )
{
	Rva00807EE0Entry *entry;
	const char *server;

	length -= 0x24;
	if( length < 0 || length > 0x400 )
		return 0;

	if( *(const int *)( packet + 0x1C ) != 'gSPs' )
		return 0;

	entry = (Rva00807EE0Entry *)Rva007F0000Alloc( length + 0x18 );
	if( entry != 0 )
	{
		entry->m_next = 0;
		entry->m_from = ( packet[ 0x0C ] << 24 ) | ( packet[ 0x0D ] << 16 )
				| ( packet[ 0x0E ] << 8 ) | packet[ 0x0F ];
		entry->m_elapsed = ( ( ( ( ( ( from[ 8 ] << 8 ) | from[ 9 ] ) << 8 )
				| from[ 10 ] ) << 8 ) | from[ 11 ] )
				- *(const int *)( packet + 0x20 );
		entry->m_sequence = ( packet[ 0x1A ] << 8 ) | packet[ 0x1B ];
		entry->m_length = length;
		entry->m_server = packet[ 0x18 ];
		entry->m_icmpType = 0;

		memcpy( (char *)entry + 0x16, packet + 0x24, length );

		if( entry->m_server != 0 )
			server = "true";
		else
			server = "false";

		Rva007FE780Printf(
				"_ProtoPingCallback: ICMP_ECHOREPLY from=%08x, time=%dms, "
				"data=%s, server=%s\n",
				entry->m_from, entry->m_elapsed, (char *)entry + 0x16, server );

		if( entry->m_elapsed == 0 )
			entry->m_elapsed = 1;
	}

	return entry;
}

// The ICMP packet as this module reads it -- an IP header with the ICMP type
// at +0x14.  Only that one field is touched through the pointer; everything
// else the two builders need they index out of the raw buffer themselves.
struct Rva00807CF0Packet
{
	char          m_ip[ 0x14 ];   // +0x00
	unsigned char m_type;         // +0x14
};

// 0x00807CF0 IS THE CALLBACK 0x00807BA0 INSTALLS, and it is a DRAIN LOOP: it
// keeps receiving until the socket has nothing left, rather than handling one
// datagram per call.  Its first two arguments -- the socket and the reason the
// socket layer is calling -- are never read; only the user data is, which is
// the ping record.
//
// THE DISPATCH IS A SWITCH, NOT AN IF CHAIN.  Both type tests sit together
// before either body, each a forward `je` to its own arm, which is MSVC's /Od
// switch shape; an if/else-if compiles to a test, a body, a jump over the rest,
// then the next test.  The switch temp is ONE BYTE, which is why the type is
// read through a struct pointer rather than out of the buffer directly -- a
// promoted `response[0x14]` would give a four-byte temp.
//
// Type 0 is ECHOREPLY and type 0x0B is TIMEEXCEEDED, matching the two builders
// and their own log lines; anything else is logged as "Unhandled ICMP type %d"
// and dropped, and the default arm re-reads the field rather than using the
// switch temp.
//
// THE CREDIT CHECK COMES BEFORE THE DISPATCH AND CONSUMES A DATAGRAM.  A reply
// that arrives with the counter at zero is received and then thrown away
// unparsed, not left in the socket; the counter is only decremented when an
// entry was actually built.
//
// The append walks to the tail with a POINTER-TO-POINTER: retail starts at the
// head slot itself and advances to whatever it holds, so the empty list and
// the non-empty one take the same path.  The loop is a `for` with an empty
// body -- retail jumps forward over the advance to the test, which is what a
// for-loop does and a while-loop does not.
//
// THE RECEIVE IS THE LOOP'S CONDITION, COMMA AND ALL.  Retail leaves the loop
// with a single `jle`, which is what a while-condition compiles to; an
// `if( len <= 0 ) break;` inside a for(;;) gives `jg` over a `jmp` instead --
// one byte longer and enough to move every displacement after it.  The length
// has to be re-armed to 0x10 before each receive because the call overwrites
// it with the datagram size, and putting that back inside the condition with a
// comma is what keeps it at the top of the loop where the bytes have it.
int Rva00807CF0( void *socket, int reason, void *ref )
{
	int len;
	char sin[ 0x10 ];
	char response[ 0x424 ];
	Rva00807EE0Entry *entry;
	Rva00807EE0Entry **link;
	Rva00807BA0Ping *ping;
	Rva00807CF0Packet *packet;

	ping = (Rva00807BA0Ping *)ref;
	packet = (Rva00807CF0Packet *)response;

	while( len = 0x10,
			( len = Rva007FDA50Recv( ping->m_socket, response, 0x424, 0,
				sin, &len ) ) > 0 )
	{
		if( ping->m_credits < 1 )
			continue;

		entry = 0;
		switch( packet->m_type )
		{
		case 0:
			entry = Rva00807FB0( (const unsigned char *)response,
					(const unsigned char *)sin, len );
			break;
		case 0x0B:
			entry = Rva00807EE0( (const unsigned char *)response,
					sin, len );
			break;
		default:
			Rva007FE780Printf(
					"_ProtoPingCallback: Unhandled ICMP type %d\n",
					packet->m_type );
			break;
		}

		if( entry != 0 )
		{
			Rva007FEBD0Lock( ping->m_lock0C );

			for( link = &ping->m_list; *link != 0;
					link = (Rva00807EE0Entry **)*link )
				;
			*link = entry;

			ping->m_credits = ping->m_credits - 1;
			Rva007FECB0Unlock( ping->m_lock0C );
		}
	}

	return 0;
}

// 0x00808220 SENDS THE ECHO REQUEST, and it builds the whole IP datagram
// itself rather than letting the stack do it -- which is what the raw socket
// at 0x00807BA0 is for.  Four bytes name the layout without any guessing:
// 0x45 at +0x00 is IPv4 with a five-word header, 1 at +0x09 is IPPROTO_ICMP,
// 8 at +0x14 is ICMP ECHO, and the record's TTL goes to +0x08 -- exactly the
// IP header's own field order.  The destination goes to +0x10 big-endian,
// which is where an IP header carries it.
//
// The payload is stamped with the same two things 0x00807FB0 checks on the way
// back: 'gSPs' at +0x1C and the tick at +0x20.  So the round trip is closed
// here -- this body writes the magic and the send stamp, that one verifies the
// magic and subtracts the stamp.
//
// THE CHECKSUM IS BUILT BIG-ENDIAN BY HAND, byte pair by byte pair over
// everything from +0x14 on, with the odd trailing byte handled separately and
// the carry folded twice before the complement.  Folding twice is not
// redundant: the first fold can itself carry.
//
// TWO PARAMETERS ARE OVERWRITTEN IN PLACE and both matter.  A negative length
// means "text", so it is replaced by strlen + 1; and the length is then
// clamped to 0x400, rounded up to a multiple of four through `(len + 3) &
// 0x7FFC` -- which also caps it a second time -- and finally has the 0x24
// header added.  The text pointer is overwritten with the packet buffer and
// never read again; that store is dead and is retail's.
//
// The return is the sequence number, not a byte count, so the caller can match
// a reply to its request; a failed send reports -1 instead.
int Rva00808220( Rva00807BA0Ping *ping, unsigned int address, const char *text,
		int length, int id )
{
	int count;
	unsigned char echo[ 0x424 ];
	char sin[ 0x10 ];
	unsigned int sum;
	unsigned char *p;
	unsigned int work;

	if( ping == 0 )
		return -1;

	if( length < 0 )
		length = strlen( text ) + 1;

	*(unsigned short *)( sin + 0 ) = 2;
	*(unsigned short *)( sin + 2 ) = 0;
	*(int *)( sin + 4 ) = 0;
	*(int *)( sin + 8 ) = 0;
	*(int *)( sin + 12 ) = 0;

	work = address;
	sin[ 7 ] = (char)work;  work >>= 8;
	sin[ 6 ] = (char)work;  work >>= 8;
	sin[ 5 ] = (char)work;  work >>= 8;
	sin[ 4 ] = (char)work;

	ping->m_sequence = ping->m_sequence + 1;

	memset( echo, 0, 0x424 );
	echo[ 0x00 ] = 0x45;
	echo[ 0x10 ] = (unsigned char)( address >> 24 );
	echo[ 0x11 ] = (unsigned char)( address >> 16 );
	echo[ 0x12 ] = (unsigned char)( address >> 8 );
	echo[ 0x13 ] = (unsigned char)address;
	echo[ 0x09 ] = 1;
	echo[ 0x08 ] = (unsigned char)ping->m_ttl;
	echo[ 0x14 ] = 8;
	echo[ 0x18 ] = (unsigned char)id;
	echo[ 0x19 ] = 0;
	echo[ 0x1A ] = (unsigned char)( ping->m_sequence >> 8 );
	echo[ 0x1B ] = (unsigned char)ping->m_sequence;

	if( length > 0x400 )
		length = 0x400;
	memcpy( echo + 0x24, text, length );
	length = ( length + 3 ) & 0x7FFC;
	text = (const char *)echo;
	length += 0x24;

	*(int *)( echo + 0x1C ) = 'gSPs';
	*(unsigned int *)( echo + 0x20 ) = Rva007FEA00Tick();

	sum = 0;
	p = echo + 0x14;
	for( count = length - 0x14; count > 1; count -= 2 )
	{
		sum += *p << 8;
		++p;
		sum += *p;
		++p;
	}
	if( count > 0 )
	{
		sum += *p << 8;
		++p;
	}

	sum = ( sum >> 16 ) + ( sum & 0xFFFF );
	sum = ( sum >> 16 ) + ( sum & 0xFFFF );
	sum = ~sum;

	echo[ 0x16 ] = (unsigned char)( sum >> 8 );
	echo[ 0x17 ] = (unsigned char)sum;

	count = Rva007FD920Send( ping->m_socket, (const char *)echo, length, 0,
			sin, 0x10 );
	if( count < 0 )
		return -1;

	return ping->m_sequence;
}

// The server-marked flavour; see the note above the other two wrappers.
int Rva00808630( Rva00807BA0Ping *ping, unsigned int address,
		const char *text, int length )
{
	return Rva00808220( ping, address, text, length, 1 );
}

// What 0x00808660 fills in for its caller.  Its size, 0x2C, is the memset
// length; the text at the front is the "$%08x" form 0x00807AB0 writes, and
// every other field is copied straight out of the entry.
struct Rva00808660Result
{
	char         m_text[ 0x14 ];   // +0x00
	unsigned int m_from;           // +0x14
	int          m_elapsed;        // +0x18
	int          m_sequence;       // +0x1C
	int          m_icmpType;       // +0x20
	int          m_server;         // +0x24
	int          m_pad28;          // +0x28
};

// 0x00808660 IS THE RESULT FETCH, and it PUMPS BEFORE IT LOOKS: the first thing
// it does is call the receive callback directly, with the socket and a zero
// reason, so a caller polling this never has to run the socket layer itself.
//
// It then takes the head of the list the callback appends to, under the same
// lock, copies out of it, unlinks it, frees it, and GIVES A CREDIT BACK -- the
// counter the callback spends to accept a reply.  So the credit is a bound on
// unread results, not on replies in flight.
//
// THE TWO OUT PARAMETERS ARE INDEPENDENT AND BOTH OPTIONAL.  The struct is
// zeroed and filled only if supplied; the payload is copied only if BOTH a
// length pointer and a buffer are supplied, and the length is clamped down to
// what arrived and written back either way -- so a caller can ask how big the
// payload was by passing a length and no buffer, and it still loses the entry.
//
// A zero sequence number is reported as 1.  Nothing here explains why; the
// substitution is in the bytes and only affects the value handed out, not the
// entry.
//
// The return is the elapsed time, read BEFORE the copies and returned even when
// both out parameters were null -- which is what makes this usable as a bare
// "was there a reply, and how long did it take".
int Rva00808660( Rva00807BA0Ping *ping, void *data, int *dataLen,
		Rva00808660Result *result )
{
	int elapsed;
	Rva00807EE0Entry *entry;
	int sequence;

	elapsed = 0;

	Rva00807CF0( ping->m_socket, 0, ping );

	if( ping != 0 )
	{
		entry = ping->m_list;
		if( entry != 0 )
		{
			Rva007FEBD0Lock( ping->m_lock0C );

			elapsed = entry->m_elapsed;

			if( result != 0 )
			{
				memset( result, 0, 0x2C );
				Rva00807AB0( result->m_text, &entry->m_from );
				result->m_from = entry->m_from;
				result->m_elapsed = entry->m_elapsed;
				result->m_icmpType = entry->m_icmpType;

				if( entry->m_sequence != 0 )
					sequence = entry->m_sequence;
				else
					sequence = 1;

				result->m_sequence = sequence;
				result->m_server = entry->m_server;
			}

			if( dataLen != 0 )
			{
				if( *dataLen > entry->m_length )
					*dataLen = entry->m_length;

				if( data != 0 )
					memcpy( data, (char *)entry + 0x16, *dataLen );
			}

			ping->m_list = entry->m_next;
			Rva007F0030Free( entry );
			ping->m_credits = ping->m_credits + 1;
			Rva007FECB0Unlock( ping->m_lock0C );
		}
	}

	return elapsed;
}
