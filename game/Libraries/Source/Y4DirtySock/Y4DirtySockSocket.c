// cl: /Od /GZ /GS /MD /DNDEBUG

/* EA DirtySock ("DirtySDK") -- Windows socket layer, dirtynetwin.c.
 *
 * WHAT THIS RANGE IS.  0x007FD080..0x007FEF60 is NOT the FESL/jabba C++ SDK
 * that occupies 0x007F96C0..0x007FCF80; it is a separate C library linked into
 * the same image, and it was built WITHOUT OPTIMISATION.  Three independent
 * tells agree:
 *   - every body opens `push ebp / mov ebp,esp` and fills its locals with
 *     0xCCCCCCCC, and every one that makes a call ends `cmp ebp,esp` followed
 *     by a call to the MSVC 7.1 stack-check helper at 0x009F7502 (__chkesp);
 *     that is /Od plus /GZ, and it is why this file carries its own
 *     `// cl: /Od /GZ /MD` directive instead of the tree default /O2;
 *   - the only string literal reachable from the span is
 *     "dirtynetwin: addr remap %s" at 0x007FD660, which names DirtySock's
 *     Windows socket module by its own source file name;
 *   - 0x007FDEB0 dispatches on the un-relocated imm32s 0x786D6170 and
 *     0x78646E73, i.e. the multi-character literals 'xmap' and 'xdns' -- the
 *     DirtySock SocketControl selector convention.
 * None of that is shape: it is strings, immediates and a compiler-flag
 * signature.
 *
 * The socket object's member OFFSETS below (+0x16, +0x18, +0x3C..+0x4C) are
 * immediates and are hard evidence; the C member names are address-derived.
 * This lane may not add a .h file, so the struct and the two Winsock
 * prototypes are declared here.
 */

int __stdcall shutdown( unsigned int socket, int how );

struct Rva007FD4E0Socket
{
	/* TWO LINKS, NOT ONE, and the idle pump at 0x007FD170 is what proves it.
	 * That body walks the list through +0x00, and separately drains a SECOND
	 * list rooted at 0x0130AB5C whose nodes link through +0x04 -- feeding each
	 * one to the same destroyer the socket teardown at 0x007FE210 uses.  So a
	 * socket sits on an active list and a deferred-destroy list at the same
	 * time, through different pointers. */
	struct Rva007FD4E0Socket *m_next;       /* +0x00 */
	struct Rva007FD4E0Socket *m_killNext;   /* +0x04 */
	/* ADDRESS FAMILY, and the accept at 0x007FD7D0 is what names it: that body
	 * refuses to run unless this word is 2, then copies it, the type and the
	 * word after it into the child socket.  2 is AF_INET, and a socket layer
	 * that tests a word for AF_INET before accepting is testing the family. */
	int m_family;                   /* +0x08 */
	/* SOCK_* type.  The send path at 0x007FD920 branches on this being 3,
	 * i.e. SOCK_RAW, and strips a caller-supplied IP header when it is. */
	int m_type;                     /* +0x0C */
	/* Protocol, from the same three-field copy at 0x007FD7D0. */
	int m_protocol;                 /* +0x10 */
	/* OPEN FLAG.  Three writes fix it and none of them is shape: the connect
	 * wrapper clears it as a connect begins, the destroy at 0x007FD3F0 clears
	 * it alongside setting the handle to -1, and the accept at 0x007FD7D0 sets
	 * it to 1 on a socket that arrives already connected. */
	char m_opened;                  /* +0x14 */
	char m_reserved15;              /* +0x15 */
	short m_shutdownFlags;          /* +0x16 */
	unsigned int m_socket;          /* +0x18 */
	char m_gap[ 0x20 ];
	void *m_callback;               /* +0x3C */
	/* THE NEXT FOUR FIELDS ARE RENAMED ON THE STRENGTH OF 0x007FD170, WHICH
	 * REFUTES WHAT THE SETTER AT 0x007FDE80 SUGGESTED.  That setter only
	 * stores, so its parameter order was all the earlier names had to go on.
	 * The pump USES them: +0x40 is compared against a tick count and rewritten
	 * with a fresh one, so it is a timestamp; +0x44 bounds the elapsed delta
	 * with an UNSIGNED compare, so it is a rate; and +0x4C is CALLED, with the
	 * socket, a zero, and +0x48 as its three arguments -- so it is the
	 * callback procedure and +0x48 is its user data.  A field that is called
	 * is not "extra". */
	unsigned int m_lastTick;        /* +0x40 */
	unsigned int m_rate;            /* +0x44 */
	void *m_callbackData;           /* +0x48 */
	void ( __cdecl *m_callbackProc )( struct Rva007FD4E0Socket *socket,
		int reason, void *data );   /* +0x4C */
};

/* The 'xmap' remap table head and the 'xdns' value, both set through
 * 0x007FDEB0 and read back by the remap walk at 0x007D660. */
void *g_Rva0130AB60;
int g_Rva0130AB64;

int Rva007FD4E0( struct Rva007FD4E0Socket *socket, int how )
{
	socket->m_shutdownFlags |= how;
	shutdown( socket->m_socket, how );
	return 0;
}

int Rva007FDE80( struct Rva007FD4E0Socket *socket, void *callback,
	unsigned int rate, void *data,
	void ( __cdecl *proc )( struct Rva007FD4E0Socket *, int, void * ) )
{
	socket->m_rate = rate;
	socket->m_callback = callback;
	socket->m_callbackData = data;
	socket->m_callbackProc = proc;
	return 0;
}

int Rva007FDEB0( int control, int value, void *pointer )
{
	if( control == 'xmap' )
		g_Rva0130AB60 = pointer;
	if( control == 'xdns' )
		g_Rva0130AB64 = value;
	return -1;
}

int Rva007FE200( const int *p )
{
	return *p;
}

/* Bounded string compare.  A NEGATIVE length selects the unbounded form, which
 * is why there are two separate loops rather than one; both operands are read
 * with `movzx`, so they are UNSIGNED char -- hard evidence, and it is what
 * makes the returned difference non-negative for high-bit bytes. */
int Rva007FE6C0( const char *string1, const char *string2, int length )
{
	int difference;
	const unsigned char *p1;
	const unsigned char *p2;

	p1 = (const unsigned char *)string1;
	p2 = (const unsigned char *)string2;
	if( length < 0 )
	{
		for( ; *p1 != 0; p1++, p2++ )
		{
			if( *p1 != *p2 )
				return *p1 - *p2;
		}
		return 0;
	}
	for( ; length > 0; p1++, p2++, length-- )
	{
		difference = *p1 - *p2;
		if( difference != 0 )
			return difference;
	}
	return 0;
}

/* The idle-callback table: pairs of { function, ref } at 0x0130AB90 with the
 * used count at 0x0130ACB4.  The 8-byte stride is an immediate (`[i*8 + base]`
 * and `[i*8 + base + 4]`) and is hard evidence for the pair layout. */
struct Rva0130AB90Entry
{
	void *m_function;
	void *m_ref;
};

struct Rva0130AB90Entry g_Rva0130AB90[ 64 ];
int g_Rva0130ACB4;

void Rva007FED40( void *function, void *ref )
{
	if( function == 0 || ref == 0 )
		return;
	g_Rva0130AB90[ g_Rva0130ACB4 ].m_function = function;
	g_Rva0130AB90[ g_Rva0130ACB4 ].m_ref = ref;
	g_Rva0130ACB4++;
}

void Rva007FED90( void *function, void *ref )
{
	int index;

	if( function == 0 || ref == 0 )
		return;
	for( index = 0; index < g_Rva0130ACB4; index++ )
	{
		if( g_Rva0130AB90[ index ].m_function == function &&
			g_Rva0130AB90[ index ].m_ref == ref )
		{
			g_Rva0130AB90[ index ].m_function = 0;
			g_Rva0130AB90[ index ].m_ref = 0;
			break;
		}
	}
}

/* Winsock wrappers.  Both hand the raw return straight to the shared error
 * translator at 0x007FD540, which is why the call is nested rather than
 * sequenced -- there is no intermediate store. */
int __stdcall bind( unsigned int socket, const void *address, int addressLength );
int __stdcall listen( unsigned int socket, int backlog );

int Rva007FD540( int result );

int Rva007FD510( struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength )
{
	return Rva007FD540( bind( socket->m_socket, address, addressLength ) );
}

int Rva007FD7A0( struct Rva007FD4E0Socket *socket, int backlog )
{
	return Rva007FD540( listen( socket->m_socket, backlog ) );
}

/* Idle-list teardown: the same global list head is handed to both halves. */
extern int g_Rva0130AC90;

void Rva007FEBD0( void *list );
void Rva007FECB0( void *list );

void Rva007FEE10( void )
{
	Rva007FEBD0( &g_Rva0130AC90 );
	Rva007FECB0( &g_Rva0130AC90 );
}

long __cdecl time( long *destination );

/* 0x007FEF60 IS THE CURRENT TIME, and it RETURNS A VALUE despite there being
 * no move to make that visible in the bytes -- time() leaves the result in eax
 * and nothing here disturbs it.  This was written as void when it was landed,
 * which is byte-neutral and was therefore never contradicted by the gate; the
 * timestamp parser at 0x007EF780 USES the value, which is what settled it.
 * A byte-exact body does not pin its own return type. */
unsigned int Rva007FEF60( void )
{
	return time( 0 );
}

/* Module shutdown at 0x007FD270.  The first call takes a FUNCTION POINTER:
 * the pushed immediate 0x00BFD170 is a virtual address, and its RVA is
 * 0x007FD170 -- the per-socket destroy helper called directly further down.
 * So the module registers its own destroyer, drains the list head until it is
 * empty, then tears the head down itself.  The trailing call is an import
 * thunk the ledger already names.  Every name here is address-derived. */
extern void *g_Rva0130AB58Head;

int Rva007FD3F0( struct Rva007FD4E0Socket *socket );
void Rva007FD170( void *head );
void Rva007FE670( void );
void Rva0081BDE4( void );

void Rva007FD270( void )
{
	Rva007FED90( (void *)Rva007FD170, &g_Rva0130AB58Head );
	Rva007FEE10();

	while ( g_Rva0130AB58Head != 0 )
		Rva007FD3F0( (struct Rva007FD4E0Socket *)g_Rva0130AB58Head );

	Rva007FD170( &g_Rva0130AB58Head );
	Rva007FE670();
	Rva0081BDE4();
}

/* Winsock error translation at 0x007FD540, already forward-declared above and
 * called by the bind and listen wrappers.  A negative return means the Winsock
 * call failed, so the real code is fetched and mapped onto this library's own
 * small negative vocabulary.  THE IMMEDIATES ARE THE EVIDENCE: 0x2733 10035
 * WSAEWOULDBLOCK, 0x2746 10054 WSAECONNRESET, 0x2743 10051 WSAENETUNREACH,
 * 0x2751 10065 WSAEHOSTUNREACH, 0x2749 10057 WSAENOTCONN and 0x274D 10061
 * WSAECONNREFUSED -- a contiguous run of the WSAE* block, which is what says
 * this is an errno mapper rather than an ordinary switch.  The pairs that share
 * a result share an `if`: would-block and connection-reset both report success,
 * which is this library's convention rather than anything the bytes explain. */
int __stdcall WSAGetLastError( void );

int Rva007FD540( int result )
{
	if ( result < 0 )
	{
		result = WSAGetLastError();

		if ( result == 10035 || result == 10054 )
			result = 0;
		else if ( result == 10051 || result == 10065 )
			result = -5;
		else if ( result == 10057 )
			result = -2;
		else if ( result == 10061 )
			result = -6;
		else
			result = -7;
	}

	return result;
}

/* 0x007FE210.  The call is `ff 15` through an IAT slot, i.e. a __declspec
 * (dllimport) __stdcall taking two arguments -- nothing is popped afterwards.
 * THE IMPORT'S NAME NEVER REACHES THESE BYTES: an IAT call site is a DIR32
 * relocation and the gate fills those four bytes from retail, so the name below
 * is address-derived on purpose and asserts nothing about which API this is.
 * What the bytes do fix is the shape: a two-argument stdcall probe over a
 * sub-object at +0x54 that, when it reports non-zero, hands the whole object to
 * a one-argument cdecl helper. */
__declspec(dllimport) int __stdcall Rva01358E58Probe( void *object, int flag );

void Rva007F0030( void *object );

void Rva007FE210( void *object )
{
	if ( Rva01358E58Probe( (char *)object + 0x54, 1 ) )
		Rva007F0030( object );
}

/* 0x007FEA00: a bare forwarder onto a no-argument stdcall import.  Nothing but
 * the /GZ esp check surrounds it. */
__declspec(dllimport) unsigned int __stdcall Rva01358E0CImport( void );

/* RETURNS ITS RESULT.  Nothing in this body shows that -- a forwarder that
 * drops the value and one that returns it compile to the same bytes, because
 * eax already holds it.  The pump at 0x007FD170 is what settles it: it stores
 * this call's eax and then uses it as a tick count, so the forwarder is
 * typed from its CALLER rather than from itself. */
unsigned int Rva007FEA00( void )
{
	return Rva01358E0CImport();
}

/* 0x007FE620: the shutdown drain.  A flag is raised, the worker is pumped until
 * a second flag clears, and the first flag is lowered again.  The 0x32 pushed
 * to the one-argument stdcall import is a 50-unit wait -- a poll interval,
 * which is what makes this a drain rather than a single hand-off.  Both globals
 * and the import are address-derived; the import name never reaches the bytes,
 * since an IAT call site is a DIR32 the gate fills from retail. */
extern int g_Rva012C3CDCDraining;
/* Holds the worker THREAD HANDLE: the startup at 0x007FE520 stores
 * CreateThread's return here, and the drain loops treat non-zero as
 * "worker still running". It is set to 1 first and then overwritten
 * with the handle, so the same word doubles as the running flag. */
extern int g_Rva0130ACB8Thread;

__declspec(dllimport) void __stdcall Rva01358F30Wait( int interval );

void Rva007FEE40( void );

void Rva007FE620( void )
{
	g_Rva012C3CDCDraining = 1;

	while ( g_Rva0130ACB8Thread != 0 )
	{
		Rva007FEE40();
		Rva01358F30Wait( 0x32 );
	}

	g_Rva012C3CDCDraining = 0;
}

/* 0x007FEAA0: reset one list, defaulting to the module's own when handed a null
 * pointer.  TWO stack slots hold what reads as one value because /Od
 * materialises a ternary into a temporary and then assigns it -- the second
 * slot is the compiler's, not a second variable in the source.  The trailing
 * one-argument stdcall import is handed the sub-object at +0xC. */
struct Rva0130AB68List
{
	/* A RECURSIVE LOCK, and the acquire at 0x007FEB00 is what proves each
	 * field. It compares +0x00 against the return of a no-argument import and,
	 * on a match, bumps +0x04 and succeeds without locking anything -- that is
	 * an owner-thread check guarding a recursion count. +0x08 is handed to the
	 * same two-argument probe the socket body at 0x007FE210 uses, and +0x0C to
	 * the enter/init/destroy slots. The release tests +0x04 with an UNSIGNED
	 * `cmp ..,1 / jbe`, so the depth is unsigned. */
	unsigned int m_ownerThread;     /* +0x00 */
	unsigned int m_depth;           /* +0x04 */
	int m_state;                    /* +0x08 */
	char m_body[ 4 ];               /* +0x0C */
};

extern struct Rva0130AB68List g_Rva0130AB68Default;

__declspec(dllimport) void __stdcall Rva01358D0CReset( void *body );

void Rva007FEAA0( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	node->m_state = 0;
	Rva01358D0CReset( node->m_body );
}

/* 0x007FE670: the other half of the shutdown handshake at 0x007FE620.  That one
 * raises the draining flag and pumps while work is pending; this one clears the
 * pending flag and waits for the drain COUNT to fall to zero -- `jle` is a
 * SIGNED test, so the flag at 0x012C3CDC is a count rather than a boolean --
 * before resetting both lists.  Passing null to the reset selects the module's
 * own list, which is why one call has no argument of its own. */
void Rva007FE670( void )
{
	g_Rva0130ACB8Thread = 0;

	while ( g_Rva012C3CDCDraining > 0 )
		Rva01358F30Wait( 1 );

	Rva007FEAA0( 0 );
	Rva007FEAA0( (struct Rva0130AB68List *)&g_Rva0130AC90 );
}

/* 0x007FEA20: the initialiser counterpart of the reset at 0x007FEAA0 -- same
 * null-defaulting selection, but it clears all three head words rather than the
 * count alone, and hands the +0xC sub-object to a DIFFERENT import slot.  One
 * slot initialising what the other tears down is the usual pairing for an
 * embedded lock, though the bytes fix only that the two slots differ. */
__declspec(dllimport) void __stdcall Rva01358E4CInit( void *body );

void Rva007FEA20( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	node->m_ownerThread = 0;
	node->m_depth = 0;
	node->m_state = 0;
	Rva01358E4CInit( node->m_body );
}

/* 0x007FECB0: release one reference.  Above one, the count simply drops; at one
 * or zero the object is cleared and its +0xC sub-object handed to a THIRD
 * import slot -- distinct from both the initialiser's and the reset's, which is
 * what says these bodies touch one embedded object through its own entry
 * points rather than sharing one call.
 *
 * CORRECTION, from the blocking acquire at 0x007FEBD0: that body calls THIS
 * SAME SLOT to give the section back after its probe reports busy, which a
 * destroy could not be.  The slot is a LEAVE, so the last release here is
 * `clear the ownership words and leave`, not `tear the object down`. */
__declspec(dllimport) void __stdcall Rva01358E74Leave( void *body );

void Rva007FECB0( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	if ( node->m_depth > 1 )
	{
		node->m_depth = node->m_depth - 1;
	}
	else
	{
		node->m_ownerThread = 0;
		node->m_depth = 0;
		node->m_state = 0;
		Rva01358E74Leave( node->m_body );
	}
}

/* 0x007FEB00: acquire, and the body that fixes the whole layout.  If the caller
 * already owns the lock the depth simply rises and no locking happens -- that
 * early return is what makes this recursive.  Otherwise the state word is
 * probed through the SAME two-argument import the socket body at 0x007FE210
 * uses, a non-zero answer meaning busy, and only then is the critical section
 * entered and ownership recorded.  Note the owner is re-read from the import
 * AFTER entering rather than reused from the first call: the compiler was given
 * no licence to cache it across the lock. */
__declspec(dllimport) unsigned int __stdcall Rva01358D7CCurrentId( void );
__declspec(dllimport) void __stdcall Rva01358D18Enter( void *body );

int Rva007FEB00( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	if ( node->m_ownerThread == Rva01358D7CCurrentId() )
	{
		node->m_depth = node->m_depth + 1;
		return 1;
	}

	if ( Rva01358E58Probe( &node->m_state, 1 ) )
		return 0;

	Rva01358D18Enter( node->m_body );

	node->m_ownerThread = Rva01358D7CCurrentId();
	node->m_depth = node->m_depth + 1;
	return 1;
}

/* 0x007FEBD0: the blocking acquire built on the try-acquire above.  Each round
 * first attempts the cheap path, then takes the section, and only claims
 * ownership if the state word is still clear; if it is not, the section is
 * given straight back and the thread waits before trying again.  That
 * give-it-back call is what proves slot 0x1358E74 is a leave.
 *
 * One source detail the bytes fix: the try-acquire is called with the RAW
 * PARAMETER, not with the already-defaulted local -- so a null argument is
 * re-defaulted inside the callee on every round, and the loop re-enters at the
 * call rather than at the selection. */
void Rva007FEBD0( struct Rva0130AB68List *list )
{
	struct Rva0130AB68List *node = list ? list : &g_Rva0130AB68Default;

	while ( !Rva007FEB00( list ) )
	{
		Rva01358D18Enter( node->m_body );

		if ( !Rva01358E58Probe( &node->m_state, 1 ) )
		{
			node->m_ownerThread = Rva01358D7CCurrentId();
			node->m_depth = node->m_depth + 1;
			return;
		}

		Rva01358E74Leave( node->m_body );
		Rva01358F30Wait( 1 );
	}
}


/* 0x007FE250: name resolution.  The hostname buffer lives at +0x10 of the
 * request and is handed to a stdcall lookup; on success the FOUR BYTES at
 * offset +0x0C of the returned record are assembled MOST SIGNIFICANT FIRST
 * ((b[0]<<24)|(b[1]<<16)|(b[2]<<8)|b[3]) and stored at +0x04.  That
 * byte-at-a-time big-endian assembly, rather than a dword load, is what says
 * the source is reading a network-order address out of a pointer-to-list at
 * +0x0C -- a dword load would have been one instruction.  Status is 1 on
 * success and -1 on failure, and the tail is the same probe-then-helper pair
 * the socket body at 0x007FE210 ends with. */
struct Rva0081BDEAHostRecord
{
	char m_head[ 0x0C ];
	unsigned char **m_addressList;  /* +0x0C */
};

struct Rva007FE250Request
{
	int m_status;                   /* +0x00, 1 resolved, -1 failed */
	unsigned int m_address;         /* +0x04, host byte order */
	char m_gap[ 8 ];
	char m_hostname[ 0x44 ];        /* +0x10 */
	int m_state;                    /* +0x54, probed like the lock's */
};

struct Rva0081BDEAHostRecord * __stdcall Rva0081BDEA( const char *name );

int Rva007FE250( struct Rva007FE250Request *request )
{
	/* DECLARATION ORDER IS LOAD-BEARING: /Od hands the first-declared local
	 * the slot nearest the frame pointer, and retail puts the byte pointer
	 * there, so it was declared first. */
	unsigned char *bytes;
	struct Rva0081BDEAHostRecord *record;

	record = Rva0081BDEA( request->m_hostname );

	if ( record != 0 )
	{
		bytes = *record->m_addressList;
		request->m_address = ( bytes[ 0 ] << 24 ) | ( bytes[ 1 ] << 16 )
		                   | ( bytes[ 2 ] << 8 ) | bytes[ 3 ];
		request->m_status = 1;
	}
	else
	{
		request->m_status = -1;
	}

	if ( Rva01358E58Probe( &request->m_state, 1 ) )
		Rva007F0030( request );

	return 0;
}

/* 0x007FE520: module startup.  The fifth argument pushed to the six-argument
 * stdcall creator is 0x00BFE620 -- a VIRTUAL address whose RVA is 0x007FE620,
 * the drain loop already converted above -- so this is thread creation and that
 * loop is the worker body.  The frame descriptor /GZ left after this function
 * names the sixth argument's local `pid`, which is retail's own name.
 *
 * The tail is DEAD CODE: `xor ecx,ecx` immediately followed by `je` always
 * jumps, so the call it skips can never run.  That is what a debug print looks
 * like once its guard has folded to a constant zero, and it is reproduced here
 * rather than dropped because the bytes carry it. */
__declspec(dllimport) int __stdcall Rva01358D00CreateWorker(
	void *security, unsigned int stackSize, void *start, void *parameter,
	unsigned int flags, unsigned int *identifier );
__declspec(dllimport) void __stdcall Rva01358F20SetPriority( int thread, int priority );
__declspec(dllimport) void __stdcall Rva01358CCCRelease( int thread );

extern int g_Rva0130ACB4;

/* Two message objects the printer is handed.  Both were written as CAST
 * ABSOLUTE ADDRESSES before; an extern is the honest spelling, because
 * retail's operand is a RELOCATION and a bare integer literal only
 * happens to agree with it at this image base. */
extern char g_Rva012C3CE0Message[];

/* The diagnostic printer, which lives in Y4DirtySockDebug.c.  It is
 * VARARGS -- proven there by the format-string fast path -- and returns
 * int.  Neither fact is visible at a one-argument call site, since a
 * cdecl call with one argument compiles the same either way, so this
 * declaration is corrected from the DEFINITION rather than from use. */
int Rva007FE780( const char *pFormat, ... );

void Rva007FE520( int priority )
{
	unsigned int pid;

	g_Rva0130ACB4 = 0;
	g_Rva012C3CDCDraining = -1;

	Rva007FEA20( 0 );
	Rva007FEA20( (struct Rva0130AB68List *)&g_Rva0130AC90 );

	g_Rva0130ACB8Thread = 1;
	g_Rva0130ACB8Thread = Rva01358D00CreateWorker( 0, 0, (void *)Rva007FE620,
	                                               0, 0, &pid );

	if ( g_Rva0130ACB8Thread != 0 )
	{
		Rva01358F20SetPriority( g_Rva0130ACB8Thread, priority );
		Rva01358CCCRelease( g_Rva0130ACB8Thread );
	}

	if ( 0 )
		Rva007FE780( g_Rva012C3CE0Message );
}

/* A ROTATING-XOR STRING HASH, and every part of it is legible in the bytes
 * rather than inferred.  Per character: the top five bits of the accumulator
 * are saved off, the accumulator is shifted left by five, the saved bits are
 * brought back in at the bottom by an ARITHMETIC shift right of 27 -- which is
 * what makes the accumulator a SIGNED int rather than unsigned, since a
 * logical shift would have been shr -- and the character is folded in last.
 *
 * The character is read with movsx, so the text is plain `char` and not
 * `unsigned char`; that distinction is visible and therefore not a guess.
 *
 * THE THIRD LOCAL IS REAL, NOT A COMPILER TEMPORARY.  The saved-bits value at
 * -0x0C is written and then read back on the next instruction, which a /Od
 * temporary would also do -- so the frame size is what settles it: three
 * declared locals give exactly the 0x0C frame retail has.
 *
 * The loop is MSVC's ordinary /Od `for` layout: initialisers, a jump forward
 * to the test, the increment sitting BEFORE the test in address order, and the
 * body jumping back to it.  Writing it as a while loop puts the increment
 * after the body instead and does not reproduce these bytes.
 */
int __cdecl Rva007FF080( const char *pText )
{
	int i;
	int uHash;
	int uCarry;

	for ( i = 0, uHash = 0; pText[ i ] != 0; i++ )
	{
		uCarry = uHash & 0xF8000000;
		uHash = uHash << 5;
		uHash = ( uCarry >> 27 ) ^ uHash;
		uHash = pText[ i ] ^ uHash;
	}
	return uHash;
}

/* 0x007FD5C0 is the CONNECT wrapper, and it is the same family as the bind and
 * listen ones above: hand the raw Winsock result to the error translator.  Two
 * things make it longer than its siblings.
 *
 * First, the address is TRANSLATED rather than passed through -- the helper at
 * 0x007FD660 fills a 16-byte scratch buffer and returns a pointer to it, which
 * is what connect actually receives.  Retail's own name for that buffer, taken
 * from the /GZ frame descriptor, is `temp`, and its declared width there is
 * 0x10; neither is a name or a size I chose.
 *
 * Second, a byte at +0x14 is cleared first.  It sits in the same head region
 * the shutdown-flag word occupies, and nothing in THIS body says what it means,
 * so it is left as a byte store into the existing head array rather than given
 * an invented field name.
 *
 * The whole outer expression is one statement: MSVC evaluates arguments
 * right-to-left, so the length is pushed BEFORE the translation helper runs,
 * and the helper's own two arguments are cleaned with `add esp,8` in the middle
 * of connect's argument list.  That interleaving is what the bytes show, and
 * splitting the call across statements does not reproduce it.
 */
int __stdcall connect( unsigned int socket, const void *address,
	int addressLength );

void *Rva007FD660( char *temp, void *address );

int Rva007FD5C0( struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength )
{
	char temp[ 0x10 ];

	socket->m_opened = 0;
	return Rva007FD540( connect( socket->m_socket,
		Rva007FD660( temp, (void *)address ), addressLength ) );
}

/* 0x007FDEE0 ASKS THE STACK FOR THIS MACHINE'S OWN ADDRESS.
 *
 * CORRECTED IDENTIFICATION.  This was first read as a round-trip self test of
 * the translator at 0x007FE310, because in isolation that is what it looks
 * like: build one address, push it through, read it back.  Its caller settles
 * it -- the comm transport at 0x00816160 calls this with no arguments and
 * stores the result as its LOCAL address, next to the local port it reads out
 * of a bind query.  Nothing about a self test would be stored that way.
 *
 * What it actually does follows from what the translator is: a routing query.
 * Asking "which local address would I use to reach 192.168.1.1" and keeping
 * the ANSWER rather than comparing it is how you discover your own address
 * without enumerating interfaces.  0xC0A80101 is not a test vector, it is a
 * plausible LAN gateway -- any routable address would do, and the result is
 * the interface the stack would send from.
 *
 * The byte-level reading below was right and is unchanged; only what the body
 * is FOR was wrong.
 *
 * The layout is read off the byte order, not assumed.  The address goes into a
 * local and is shifted right eight bits at a time with the LOW byte written to
 * the HIGHEST offset first, so +4..+7 is big-endian; the read-back reassembles
 * from +4 downwards with movzx, so those bytes are unsigned.  The port at
 * +2..+3 is written high half first and needs no temporary, because both
 * halves of a constant fold at compile time.  That inconsistency between how
 * the port and the address are spelled is real and is reproduced rather than
 * tidied.
 */
struct Rva007FDEE0Addr
{
	short m_family;                 /* +0x00 */
	unsigned char m_data[ 14 ];     /* +0x02 */
};

void *__cdecl memset( void *destination, int value, unsigned int count );

int Rva007FE310( void *host, int hostLength, const void *inet, int inetLength );

int Rva007FDEE0( void )
{
	struct Rva007FDEE0Addr inet;
	struct Rva007FDEE0Addr host;
	unsigned int uAddress;

	memset( &inet, 0, sizeof inet );
	inet.m_family = 2;
	inet.m_data[ 0 ] = (unsigned char)( 0x004F >> 8 );
	inet.m_data[ 1 ] = (unsigned char)0x004F;

	uAddress = 0xC0A80101;
	inet.m_data[ 5 ] = (unsigned char)uAddress;  uAddress >>= 8;
	inet.m_data[ 4 ] = (unsigned char)uAddress;  uAddress >>= 8;
	inet.m_data[ 3 ] = (unsigned char)uAddress;  uAddress >>= 8;
	inet.m_data[ 2 ] = (unsigned char)uAddress;

	memset( &host, 0, sizeof host );
	Rva007FE310( &host, sizeof host, &inet, sizeof inet );

	return ( ( ( ( host.m_data[ 2 ] << 8 ) | host.m_data[ 3 ] ) << 8
		| host.m_data[ 4 ] ) << 8 ) | host.m_data[ 5 ];
}

/* 0x007FD170 is the IDLE PUMP, and it is the body that gave the socket struct
 * above its real field names.  It does three things under one lock: fire any
 * socket whose callback is due, drain the deferred-destroy list, unlock.
 *
 * A callback is due only if all four guards pass, and each is a separate fact
 * about the object: a rate is set, a procedure is installed, the timestamp is
 * not the in-progress sentinel -1, and the elapsed time exceeds the rate.  The
 * elapsed comparison is `jbe`, i.e. UNSIGNED, which is what makes the
 * subtraction wrap correctly across a tick-counter rollover -- so the tick
 * source and both fields are unsigned, and that is read from the bytes.
 *
 * THE SENTINEL IS THE INTERESTING PART.  The timestamp is set to -1 BEFORE the
 * callback runs and to a FRESH tick count after, not to the tick count taken at
 * the top.  Both details are load-bearing: -1 makes the entry ineligible for
 * the duration of the call, which is what keeps a re-entrant pump from firing
 * the same socket twice, and re-reading the clock afterwards means the rate
 * measures the gap BETWEEN calls rather than including the call itself.
 *
 * The second loop links through +0x04 rather than +0x00 and hands each node to
 * the same destroyer the socket teardown uses -- a deferred-free list, drained
 * inside the lock so nothing can be resurrected while it empties.
 */
extern struct Rva007FD4E0Socket *g_Rva0130AB5CKillList;

void Rva007FD170( struct Rva007FD4E0Socket *head )
{
	struct Rva007FD4E0Socket *pSocket;
	struct Rva007FD4E0Socket *pList;
	unsigned int uTick;

	pList = head;
	uTick = Rva007FEA00();
	Rva007FEBD0( 0 );

	for ( pSocket = pList->m_next; pSocket != 0; pSocket = pSocket->m_next )
	{
		if ( pSocket->m_rate != 0 && pSocket->m_callbackProc != 0
			&& pSocket->m_lastTick != 0xFFFFFFFF
			&& uTick - pSocket->m_lastTick > pSocket->m_rate )
		{
			pSocket->m_lastTick = 0xFFFFFFFF;
			pSocket->m_callbackProc( pSocket, 0, pSocket->m_callbackData );
			uTick = Rva007FEA00();
			pSocket->m_lastTick = uTick;
		}
	}

	while ( ( pSocket = g_Rva0130AB5CKillList ) != 0 )
	{
		g_Rva0130AB5CKillList = pSocket->m_killNext;
		Rva007F0030( pSocket );
	}

	Rva007FECB0( 0 );
}

/* 0x007FD3F0 is socket DESTROY, and it is the other half of the pump above:
 * unlink from the active list, close the handle, then push the object onto the
 * deferred-destroy list the pump drains.  The unlink walks a POINTER TO the
 * link rather than the node, so the head and every interior link are the same
 * case and there is no special first-element branch -- that is why the loop
 * variable is initialised to the ADDRESS of the list head.
 *
 * FAILING TO FIND THE SOCKET IS AN ERROR PATH, not a no-op: it reports through
 * the diagnostic printer at 0x007FE780 and returns -1 without closing
 * anything.  The pushed operand for the printer's first argument is a DIR32
 * that the gate fills from retail, so the name below asserts nothing about it;
 * what can be said is that it lies past the last section's raw data, i.e. in
 * zero-initialised storage rather than among the string literals.
 *
 * A REAL BUG IN RETAIL IS PRESERVED HERE.  The handle guard is written
 * `>= 0` against an UNSIGNED field -- the compare is `jb`, which no unsigned
 * value satisfies -- so the branch is always taken and the close always runs.
 * The intent was plainly to skip an already-closed handle, whose sentinel is
 * the -1 this function itself writes back a few instructions later.  Making
 * the field signed would fix the bug and break the bytes; the bytes win.
 */
int __stdcall closesocket( unsigned int socket );

extern char g_Rva012C3C88Format[];

int Rva007FD3F0( struct Rva007FD4E0Socket *socket )
{
	struct Rva007FD4E0Socket **ppLink;
	unsigned char bFound;

	bFound = 0;
	Rva007FEBD0( 0 );
	for ( ppLink = (struct Rva007FD4E0Socket **)&g_Rva0130AB58Head;
		*ppLink != 0;
		ppLink = &( *ppLink )->m_next )
	{
		if ( *ppLink == socket )
		{
			*ppLink = socket->m_next;
			bFound = 1;
			break;
		}
	}
	Rva007FECB0( 0 );

	if ( !bFound )
	{
		Rva007FE780( g_Rva012C3C88Format, socket );
		return -1;
	}

	Rva007FEE10();

	if ( socket->m_socket >= 0 )
	{
		shutdown( socket->m_socket, 2 );
		closesocket( socket->m_socket );
	}
	socket->m_socket = 0xFFFFFFFF;
	socket->m_opened = 0;

	Rva007FEBD0( 0 );
	socket->m_killNext = g_Rva0130AB5CKillList;
	g_Rva0130AB5CKillList = socket;
	Rva007FECB0( 0 );
	return 0;
}

/* 0x007FE310 is the ADDRESS REMAP the file's own string names -- "dirtynetwin:
 * addr remap %s".  Its job is to answer "what local address would I use to
 * reach this peer", and it does so with a fallback ladder rather than one
 * query.  TWO IMMEDIATES CARRY THE IDENTIFICATION and neither is shape:
 * 0xC8000014 is SIO_ROUTING_INTERFACE_QUERY, and 0x7F000001 is 127.0.0.1.
 *
 * The ladder, in the order the bytes run it:
 *   - copy the peer address over, then ZERO the four address bytes, so every
 *     step below is testing "did anything fill this in yet";
 *   - if the capability word at 0x0130AB54 is at least 0x200, ask the routing
 *     table.  Its answer is taken, and then THROWN AWAY AGAIN if it comes back
 *     as loopback -- 127.0.0.1 is a true answer to the wrong question, and the
 *     original peer address is restored instead;
 *   - if the address is still zero, connect a scratch UDP socket to the peer
 *     and ask getsockname what local address the stack picked.  A connect on a
 *     datagram socket sends nothing, so this is a routing query too.
 *
 * THE RETURN CODES ARE NOT AN ERROR LADDER.  Length mismatch is -1 and a
 * non-AF_INET family is -3 with the destination zeroed, but FAILING TO RESOLVE
 * ANYTHING returns 0 -- as does failing to create the socket at all.  Success
 * here means "the output is well-formed", not "an address was found"; the
 * caller is expected to look at the address.  The self test at 0x007FDEE0 does
 * exactly that.
 *
 * The WSAIoctl bytes-returned pointer is `&destLength` -- retail reuses its own
 * PARAMETER SLOT as scratch, and getsockname reuses it again.  That is why the
 * length is not const here.
 *
 * The result of WSAGetLastError is stored and never read; it is retail's, and
 * removing the call would change the bytes.
 */
extern int g_Rva0130AB54Version;

void *__cdecl memcpy( void *destination, const void *source,
	unsigned int count );

unsigned int __stdcall socket( int family, int type, int protocol );
int __stdcall getsockname( unsigned int socket, void *name, int *nameLength );
int __stdcall WSAIoctl( unsigned int socket, unsigned int code,
	const void *inBuffer, int inLength, void *outBuffer, int outLength,
	int *bytesReturned, void *overlapped, void *completion );

/* The four address bytes at +4..+7, in the big-endian order the self test at
 * 0x007FDEE0 writes them; both bodies read them back with movzx. */
#define RVA007FE310_ADDRESS( p ) \
	( ( ( ( ( (const unsigned char *)( p ) )[ 4 ] << 8 ) \
	| ( (const unsigned char *)( p ) )[ 5 ] ) << 8 \
	| ( (const unsigned char *)( p ) )[ 6 ] ) << 8 \
	| ( (const unsigned char *)( p ) )[ 7 ] )

int Rva007FE310( void *dest, int destLength, const void *src, int srcLength )
{
	unsigned int uSocket;
	char addr[ 0x10 ];
	int iError;

	if ( destLength != srcLength )
		return -1;

	/* THE FAMILY TEST IS WRITTEN POSITIVELY, WITH THE FAILURE AS A TRAILING
	 * ELSE.  Retail's `jne` is a FAR jump to a block sitting after the whole
	 * body, which is how MSVC lays out if/else at /Od; writing it as an early
	 * `if ( family != 2 ) { ... return -3; }` puts a short jump over an inline
	 * block instead.  That difference also shifts the register rotation
	 * through every expression that follows, so it is not cosmetic. */
	if ( *(const unsigned short *)src == 2 )
	{
		memcpy( dest, src, destLength );
		( (unsigned char *)dest )[ 7 ] = 0;
		( (unsigned char *)dest )[ 6 ] = 0;
		( (unsigned char *)dest )[ 5 ] = 0;
		( (unsigned char *)dest )[ 4 ] = 0;

		uSocket = socket( 2, 2, 0 );
		if ( uSocket != 0xFFFFFFFF )
		{
			if ( g_Rva0130AB54Version >= 0x200 )
			{
				if ( WSAIoctl( uSocket, 0xC8000014, src, srcLength, addr,
					0x10, &destLength, 0, 0 ) < 0 )
				{
					iError = WSAGetLastError();
				}
				memcpy( (char *)dest + 4, addr + 4, 4 );

				if ( RVA007FE310_ADDRESS( dest ) == 0x7F000001 )
					memcpy( (char *)dest + 4, (const char *)src + 4, 4 );
			}

			if ( RVA007FE310_ADDRESS( dest ) == 0
				&& connect( uSocket, src, srcLength ) == 0
				&& getsockname( uSocket, addr, &destLength ) == 0 )
			{
				memcpy( (char *)dest + 4, addr + 4, 4 );
			}

			closesocket( uSocket );
		}
		return 0;
	}

	memset( dest, 0, destLength );
	return -3;
}

/* 0x007FD660 is the 'xmap' REMAP LOOKUP -- the consumer of the table that
 * SocketControl installs at 0x0130AB60 when handed the 'xmap' selector, which
 * the body at 0x007FDEB0 in this file already showed being stored.  This is
 * what the table is FOR, and the pair together is the whole feature: a
 * caller-supplied list that rewrites destination addresses before connect.
 *
 * THE TABLE'S LAYOUT IS READ FROM THE WALK, not assumed.  The stride is 0x0C,
 * and each entry is tested as `match == (address & mask)` with the replacement
 * at +0x08 doubling as the terminator -- a zero replacement ends the list, so
 * an entry that maps something to 0.0.0.0 cannot be expressed.  That is a real
 * limitation of the format and it is visible here.
 *
 * On a hit the original and the replacement are both printed, the whole
 * address is copied into the caller's scratch buffer, the four address bytes
 * are overwritten from the replacement low-byte-first into descending offsets
 * -- the same big-endian placement the self test at 0x007FDEE0 uses -- and the
 * SCRATCH is returned instead of the original.  On a miss the original pointer
 * comes back untouched, which is why the connect wrapper can pass the result
 * straight through without checking.
 *
 * The parameter is REASSIGNED to the scratch buffer and then returned, so it
 * cannot be const; that is retail's spelling, not a convenience.
 */
struct Rva0130AB60Map
{
	unsigned int m_match;           /* +0x00 */
	unsigned int m_mask;            /* +0x04 */
	unsigned int m_replace;         /* +0x08, and zero terminates the list */
};

char *Rva007FFB50AddrText( unsigned int address );

extern char g_Rva012C3C60Message[];
extern char g_Rva012C3C7CMessage[];

void *Rva007FD660( char *temp, void *address )
{
	unsigned int uAddress;
	struct Rva0130AB60Map *pMap;
	unsigned int uReplace;

	pMap = g_Rva0130AB60;
	if ( pMap != 0 )
	{
		uAddress = RVA007FE310_ADDRESS( address );

		for ( ; pMap->m_replace != 0; pMap++ )
		{
			if ( pMap->m_match == ( uAddress & pMap->m_mask ) )
			{
				Rva007FE780( g_Rva012C3C60Message,
					Rva007FFB50AddrText( uAddress ) );
				Rva007FE780( g_Rva012C3C7CMessage,
					Rva007FFB50AddrText( pMap->m_replace ) );

				memcpy( temp, address, 0x10 );

				uReplace = pMap->m_replace;
				temp[ 7 ] = (char)uReplace;  uReplace >>= 8;
				temp[ 6 ] = (char)uReplace;  uReplace >>= 8;
				temp[ 5 ] = (char)uReplace;  uReplace >>= 8;
				temp[ 4 ] = (char)uReplace;

				address = temp;
				break;
			}
		}
	}
	return address;
}

/* 0x007FD920 is SEND, and its interesting half is the RAW-SOCKET path.  When
 * the socket's type word at +0x0C is 3 -- SOCK_RAW -- the caller has handed in
 * a whole IP datagram including its header, and Windows will not let that
 * header through as data.  So the library takes the two fields it can honour
 * and drops the rest: byte 8 of an IP header is the TTL, and it is pushed
 * through setsockopt with level 0 and option 4, i.e. IPPROTO_IP / IP_TTL; the
 * low nibble of byte 0 is the IHL in 32-bit words, so multiplying it by four
 * gives the header length, which is then skipped over.  EVERY ONE OF THOSE
 * CONSTANTS IS IN THE BYTES -- the 3, the 0 and 4 of the setsockopt, the 0xF
 * mask and the shift by two -- so this identification does not rest on shape.
 *
 * The clamp afterwards is defensive and is retail's: a header longer than the
 * buffer would otherwise make the length negative.
 *
 * THE FLAGS PARAMETER IS IGNORED.  Both calls pass a literal zero, not the
 * caller's flags.  That is retail's behaviour and it is preserved.
 *
 * Which call is used depends only on whether a destination was supplied, and
 * the destination goes through the 'xmap' remap first -- the same interleaved
 * argument evaluation as the connect wrapper, with the remap's own two
 * arguments cleaned in the middle of sendto's list.
 */
struct Rva007FD920IpHeader
{
	unsigned char m_versionAndLength;   /* +0x00, low nibble is IHL */
	unsigned char m_skip[ 7 ];
	unsigned char m_timeToLive;         /* +0x08 */
};

int __stdcall setsockopt( unsigned int socket, int level, int option,
	const void *value, int valueLength );
int __stdcall send( unsigned int socket, const char *buffer, int length,
	int flags );
int __stdcall sendto( unsigned int socket, const char *buffer, int length,
	int flags, const void *to, int toLength );

int Rva007FD920( struct Rva007FD4E0Socket *socket, const char *buffer,
	int length, int flags, void *to, int toLength )
{
	int iResult;
	char scratch[ 0x10 ];
	const struct Rva007FD920IpHeader *pHeader;
	int iTimeToLive;

	if ( socket->m_type == 3 )
	{
		pHeader = (const struct Rva007FD920IpHeader *)buffer;
		iTimeToLive = pHeader->m_timeToLive;
		setsockopt( socket->m_socket, 0, 4, &iTimeToLive, 4 );

		length -= ( pHeader->m_versionAndLength & 0x0F ) * 4;
		buffer = buffer + ( pHeader->m_versionAndLength & 0x0F ) * 4;
		if ( length < 0 )
			length = 0;
	}

	if ( to == 0 )
		iResult = send( socket->m_socket, buffer, length, 0 );
	else
		iResult = sendto( socket->m_socket, buffer, length, 0,
			Rva007FD660( scratch, to ), toLength );

	return Rva007FD540( iResult );
}

/* 0x007FDA50 is RECEIVE, and it carries the neatest trick in this file: on a
 * successful recvfrom it STAMPS A TICK COUNT INTO BYTES 8..11 OF THE SOURCE
 * ADDRESS.  Those are the tail of sockaddr's 14-byte data area, which
 * sockaddr_in leaves as zero padding, so the library gets a per-datagram
 * arrival timestamp delivered to the caller through a structure that already
 * had room for it and no field to name it.  The bytes go in low-first at
 * descending offsets -- the same big-endian placement used for addresses
 * everywhere else in this file.
 *
 * TWO SEPARATE RESULT CONVENTIONS MEET HERE AND THE ORDER MATTERS.  First a
 * zero-length read -- an orderly shutdown -- is turned into -1, while anything
 * else goes through the Winsock error translator.  Then, and only if bit 5 of
 * the flags is set, 0 and -1 are SWAPPED.  The two are applied in sequence
 * rather than folded together, so a caller passing that bit gets 0 for a
 * closed connection: the flag selects which of the two spellings of "nothing
 * arrived" the caller wants.
 */
int __stdcall recv( unsigned int socket, char *buffer, int length, int flags );
int __stdcall recvfrom( unsigned int socket, char *buffer, int length,
	int flags, char *from, int *fromLength );

int Rva007FDA50( struct Rva007FD4E0Socket *socket, char *buffer, int length,
	int flags, char *from, int *fromLength )
{
	int iResult;
	unsigned int uTick;
	int iTranslated;

	if ( from == 0 )
	{
		iResult = recv( socket->m_socket, buffer, length, 0 );
	}
	else
	{
		iResult = recvfrom( socket->m_socket, buffer, length, 0, from,
			fromLength );
		if ( iResult > 0 )
		{
			uTick = Rva007FEA00();
			from[ 11 ] = (char)uTick;  uTick >>= 8;
			from[ 10 ] = (char)uTick;  uTick >>= 8;
			from[ 9 ] = (char)uTick;   uTick >>= 8;
			from[ 8 ] = (char)uTick;
		}
	}

	if ( iResult == 0 )
		iTranslated = -1;
	else
		iTranslated = Rva007FD540( iResult );
	iResult = iTranslated;

	if ( flags & 0x20 )
	{
		if ( iResult == -1 )
			iResult = 0;
		else if ( iResult == 0 )
			iResult = -1;
	}
	return iResult;
}

/* 0x007FD080 IS THE MODULE CREATE, and a 0x190-byte local is what proves it.
 * /GZ's frame descriptor names that local `data`, 0x190 is exactly
 * sizeof(WSADATA), it is zeroed and then handed to the import at 0x0081BDF6 --
 * whose IAT slot the import-name table calls WSAStartup -- and the version word
 * that comes back is byte-swapped into the global at 0x0130AB54.
 *
 * THAT LAST STEP CORRECTS THE GLOBAL'S MEANING.  0x0130AB54 was read as a
 * "capability" word, because its only other use is the remap at 0x007FE310
 * gating a routing query on `>= 0x200`, and a threshold on an unknown word
 * looks like a feature level.  It is a VERSION: 0x200 is Winsock 2.0 with the
 * major and minor bytes already in the order this swap puts them.  The name is
 * corrected here rather than left to read as a bitfield.
 *
 * TWO DETAILS OF THE SWAP ARE READ OUT OF THE BYTES rather than chosen.  The
 * high half shifts with SHR, not SAR, so the shift runs on an UNSIGNED value;
 * letting the WORD promote to int and shifting there compiles to sar and is
 * refuted.  And that half carries no mask at all -- retail masks the low half
 * and only narrows the high one -- so the asymmetry is retail's spelling, not
 * something to tidy up.
 *
 * THE LOCAL ORDER IS FIXED BY /GZ's ARRAY GUARDS, and it is the one thing here
 * that had to be measured instead of reasoned.  /GZ brackets every local array
 * with four guard bytes, so the frame runs cookie, guard, data, guard, iResult
 * -- 4 + 4 + 0x190 + 4 + 4 = 0x1A0, exactly retail's `sub esp`.  That lands only
 * with `data` declared BEFORE `iResult`; the other order puts iResult against
 * the cookie and shifts every frame offset in the body by four.
 *
 * ORDER IS EVIDENCE HERE, not preference.  The thread creation at 0x007FE520
 * runs FIRST, with this function's only argument as its priority, and Winsock
 * is initialised LAST -- so the worker is already running before there is a
 * stack for it to talk to.  The two 'xmap'/'xdns' words cleared in between are
 * the same pair the control entry at 0x007FDEB0 sets, which is what makes this
 * the create half of that pair rather than an unrelated initialiser.
 *
 * WSAStartup's result is stored into a local and never read.  It is retail's;
 * dropping it drops the store.
 */
struct Rva007FD080WsaData
{
	unsigned short wVersion;
	unsigned short wHighVersion;
	char szDescription[ 257 ];
	char szSystemStatus[ 129 ];
	unsigned short iMaxSockets;
	unsigned short iMaxUdpDg;
	char *lpVendorInfo;
};

int __stdcall WSAStartup( unsigned short versionRequested,
	struct Rva007FD080WsaData *data );

void *__cdecl memset( void *destination, int value, unsigned int count );

void Rva007FD080( int priority )
{
	struct Rva007FD080WsaData data;
	int iResult;

	Rva007FE520( priority );
	Rva007FED40( (void *)Rva007FD170, &g_Rva0130AB58Head );

	g_Rva0130AB60 = 0;
	g_Rva0130AB64 = 0;

	memset( &data, 0, sizeof( data ) );
	iResult = WSAStartup( 2, &data );

	g_Rva0130AB54Version = ( (unsigned char)( data.wVersion & 0xFF ) << 8 )
		| (unsigned char)( (unsigned int)data.wVersion >> 8 );
}

/* 0x007FD7D0 IS ACCEPT, and the FIONBIO immediate is what proves it rather
 * than the shape.  0x8004667E is FIONBIO, it is handed to the import at
 * 0x0081BE4A whose IAT slot the import-name table calls ioctlsocket, and the
 * value it enables is the local /GZ names `nonblock` -- retail's own name.  The
 * handle it makes non-blocking came from the import at 0x0081BE6E, `accept`,
 * called with this socket's handle and the caller's address and length.
 *
 * THE GUARDS ARE PART OF THE FRAME.  /GZ brackets `nonblock` with four bytes on
 * each side, so the 0x14 retail subtracts is 4 + 4 + 4 + 4 + 4: two scalars, a
 * guard, the flag, a guard.  Declaring the flag anywhere but last in the list
 * moves the guarded pair and every offset after it.
 *
 * THREE THINGS ABOUT THE ARGUMENTS ARE READ, NOT ASSUMED.  The length is
 * compared with `jae`, so it is UNSIGNED -- a signed minimum would have been
 * jge; 0x10 is sizeof(sockaddr_in), and the check is skipped entirely when no
 * address was asked for.  And the family word is tested for 2, i.e. AF_INET,
 * with the failure falling into the ordinary return rather than an early one:
 * a wrong family returns the null this function started with, not an error.
 *
 * The child socket is 0x50 bytes from the same one-argument allocator at
 * 0x007F0000 that the mangle module uses, zeroed, and then given the parent's
 * family, type and protocol -- three adjacent dwords, which is what let the
 * struct above stop calling +0x08 and +0x10 head bytes.  Its open flag goes to
 * 1 because accept hands back a connection that is already up.
 *
 * The link onto the module list is done under the same acquire/release pair
 * every other mutation of that list uses, and both are passed null so they fall
 * back to the module's own list.
 */
unsigned int __stdcall accept( unsigned int socket, void *address,
	unsigned int *addressLength );
int __stdcall ioctlsocket( unsigned int socket, long command,
	unsigned long *argument );

void *Rva007F0000( int size );

struct Rva007FD4E0Socket *Rva007FD7D0( struct Rva007FD4E0Socket *socket,
	void *address, unsigned int *addressLength )
{
	struct Rva007FD4E0Socket *pOpen;
	unsigned int uSocket;
	unsigned long nonblock;

	pOpen = 0;
	nonblock = 1;

	if ( socket->m_socket == 0xFFFFFFFF )
		return 0;

	if ( address != 0 && *addressLength < 0x10 )
		return 0;

	if ( socket->m_family == 2 )
	{
		uSocket = accept( socket->m_socket, address, addressLength );
		if ( uSocket != 0xFFFFFFFF )
		{
			ioctlsocket( uSocket, 0x8004667E, &nonblock );

			pOpen = (struct Rva007FD4E0Socket *)Rva007F0000( 0x50 );
			memset( pOpen, 0, 0x50 );
			pOpen->m_socket = uSocket;
			pOpen->m_family = socket->m_family;
			pOpen->m_type = socket->m_type;
			pOpen->m_protocol = socket->m_protocol;
			pOpen->m_opened = 1;

			Rva007FEBD0( 0 );
			pOpen->m_next = (struct Rva007FD4E0Socket *)g_Rva0130AB58Head;
			g_Rva0130AB58Head = pOpen;
			Rva007FECB0( 0 );
		}
	}

	return pOpen;
}

/* 0x007FD2D0 IS THE OPEN, and it is the accept above with the handle made
 * instead of taken.  Same allocator, same 0x50, same memset, same three-dword
 * family/type/protocol copy, same acquire/link/release onto the module list --
 * so the two bodies pin each other's reading of those fields rather than each
 * standing on its own.
 *
 * FOUR IMMEDIATES CARRY THE IDENTIFICATION.  0x8004667E is FIONBIO again;
 * 0xFFFF is SOL_SOCKET, 0x20 is SO_BROADCAST, and the option is set only when
 * the requested type is 2, i.e. SOCK_DGRAM.  A socket layer that turns
 * broadcast on for datagram sockets and nothing else is not a shape argument.
 *
 * RETAIL REUSES ONE LOCAL FOR BOTH CALLS.  `nonblock` holds the 1 that FIONBIO
 * enables and is handed straight to setsockopt as the broadcast value, with a
 * length of 4; that is why it is set before the socket is even created and why
 * there is no second flag variable.  /GZ guards it on both sides, which is what
 * makes the frame 0x14 rather than 0x0C.
 *
 * The open flag at +0x14 is NOT set here -- an opened socket is not a connected
 * one, and only accept and the connect wrapper touch it.
 */
struct Rva007FD4E0Socket *Rva007FD2D0( int family, int type, int protocol )
{
	unsigned int uSocket;
	struct Rva007FD4E0Socket *pSocket;
	unsigned long nonblock = 1;

	uSocket = socket( family, type, protocol );
	if ( uSocket == 0xFFFFFFFF )
		return 0;

	pSocket = (struct Rva007FD4E0Socket *)Rva007F0000( 0x50 );
	memset( pSocket, 0, 0x50 );
	pSocket->m_socket = uSocket;

	ioctlsocket( uSocket, 0x8004667E, &nonblock );
	if ( type == 2 )
		setsockopt( uSocket, 0xFFFF, 0x20, &nonblock, 4 );

	pSocket->m_family = family;
	pSocket->m_type = type;
	pSocket->m_protocol = protocol;

	Rva007FEBD0( 0 );
	pSocket->m_next = (struct Rva007FD4E0Socket *)g_Rva0130AB58Head;
	g_Rva0130AB58Head = pSocket;
	Rva007FECB0( 0 );

	return pSocket;
}

/* 0x007FEE40 is the idle-callback dispatcher, and it is the READER of the
 * table the two bodies above maintain.  The remove above does not shrink the
 * table -- it only zeroes both halves of an entry -- so something has to reap
 * the holes, and this is it.
 *
 * IT COMPACTS WHILE WALKING.  An entry with either half cleared is dead; the
 * LAST live entry is moved down into the hole, the tail is zeroed, the count
 * drops, and the index steps BACK ONE so the entry just moved in is examined
 * on the next pass.  That is swap-with-last removal, and it is why callbacks
 * have no guaranteed order -- a removal reshuffles the tail.
 *
 * THE GUARD WRAPS THE BODY rather than returning early.  Retail's is a single
 * far `je` past everything; an early return compiles to a short `jne` over a
 * `jmp`, two instructions where retail has one.  And the lock is TRIED, not
 * taken: when the acquire returns zero the whole pass is skipped rather than
 * retried, so missing an idle tick is cheaper than contending for one.
 *
 * The dispatch is an indirect call through a table slot, which is why the /GZ
 * stack check surrounds it and nothing else here.
 */
int Rva007FEB00( void *list );

void Rva007FEE40( void )
{
	int i;
	void ( __cdecl *pFunction )( void *ref );
	void *pRef;

	if ( Rva007FEB00( &g_Rva0130AC90 ) != 0 )
	{
		for ( i = 0; i < g_Rva0130ACB4; i++ )
		{
			pFunction = ( void ( __cdecl * )( void * ) )
				g_Rva0130AB90[ i ].m_function;
			pRef = g_Rva0130AB90[ i ].m_ref;

			if ( pFunction == 0 || pRef == 0 )
			{
				g_Rva0130AB90[ i ].m_function =
					g_Rva0130AB90[ g_Rva0130ACB4 - 1 ].m_function;
				g_Rva0130AB90[ i ].m_ref =
					g_Rva0130AB90[ g_Rva0130ACB4 - 1 ].m_ref;
				g_Rva0130AB90[ g_Rva0130ACB4 - 1 ].m_function = 0;
				g_Rva0130AB90[ g_Rva0130ACB4 - 1 ].m_ref = 0;
				g_Rva0130ACB4 = g_Rva0130ACB4 - 1;
				i = i - 1;
				continue;
			}

			pFunction( pRef );
		}

		Rva007FECB0( &g_Rva0130AC90 );
	}
}

/* 0x007FE880 IS A HEX DUMP, and the four strings it uses say so outright.  Read
 * out of retail's .rdata they are "%04x" at 0x012C3D04, "%02x" at 0x012C3D0C,
 * and "%s: %s\n" at BOTH 0x012C3D14 and 0x012C3D1C.  The last two are the same
 * text at two addresses, so retail wrote that literal twice and the build did
 * not pool it; that is why there are two externs below and not one, and
 * collapsing them into a single name would be a claim about string pooling that
 * the two distinct relocation targets refute.
 *
 * THE LINE IS 32 BYTES WITH A GAP IN THE MIDDLE, and both halves of that come
 * out of the same modulo idiom rather than from a layout guess.  MSVC's signed
 * `% 32` is `and 0x8000001F` followed by the jns/dec/or/inc fixup, and it
 * appears twice: on `i + 17`, which fires at the sixteenth byte of a line and
 * inserts one space, and on `i + 1`, which fires at the thirty-second and
 * flushes.  Each byte costs two characters -- the pointer advances by 2 after a
 * "%02x" -- so nothing separates the pairs but that one mid-line space.
 *
 * The offset label is formatted into `addr` and the bytes into `line`, both
 * names retail's own via /GZ, and the two are printed as "%s: %s\n" through the
 * hookable printer at 0x007FE780.  `addr` is written only when a line starts,
 * which is what the null pointer doubles as: `line` empty is also "no line in
 * progress", so one variable carries both.
 *
 * THE OUTPUT IS GATED ON A MASK, NOT A LEVEL.  The caller's first argument is
 * ANDed with the word at 0x0130ACBC and the print is skipped when the result is
 * zero -- a bitwise test, so that argument selects a debug GROUP.  The dump is
 * still built either way; only the printing is conditional.
 *
 * The trailing flush repeats the guard because a partial line has to be emitted
 * after the loop ends, and the frame is 0xAC because /GZ brackets each of the
 * two arrays with four bytes on both sides: 4 + 0x80 + 4 + 4 + 0x10 + 4 + 4 +
 * 4 + 4.
 */
int __cdecl sprintf( char *buffer, const char *format, ... );

/* The debug-group mask the printing is gated on. */
extern int g_Rva0130ACBCGroupMask;

extern char g_Rva012C3D04Format[];
extern char g_Rva012C3D0CFormat[];
extern char g_Rva012C3D14Format[];
extern char g_Rva012C3D1CFormat[];

void Rva007FE880( int group, const unsigned char *buffer, int length )
{
	int i;
	char *pOut;
	char addr[ 0x10 ];
	char line[ 0x80 ];

	pOut = 0;

	for ( i = 0; i < length; i++ )
	{
		if ( pOut == 0 )
		{
			sprintf( addr, g_Rva012C3D04Format, i );
			pOut = line;
		}

		sprintf( pOut, g_Rva012C3D0CFormat, buffer[ i ] );
		pOut += 2;

		if ( ( i + 0x11 ) % 32 == 0 )
		{
			*pOut = ' ';
			pOut += 1;
		}

		if ( ( i + 1 ) % 32 == 0 )
		{
			if ( group & g_Rva0130ACBCGroupMask )
				Rva007FE780( g_Rva012C3D14Format, addr, line );
			pOut = 0;
		}
	}

	if ( pOut != 0 )
	{
		if ( group & g_Rva0130ACBCGroupMask )
			Rva007FE780( g_Rva012C3D1CFormat, addr, line );
	}
}

/* 0x007FEF80 IS THE CACHED LOCAL-VERSUS-UTC OFFSET IN SECONDS, and the three
 * multipliers are the whole identification: 0x15180 is 86400, 0xE10 is 3600 and
 * 0x3C is 60, applied to fields at +0x0C, +0x08 and +0x04 with +0x00 added
 * plain.  That is `struct tm`'s tm_mday, tm_hour, tm_min and tm_sec folded to
 * seconds, done once over gmtime's answer and once over localtime's, and the
 * difference cached in the word at 0x012C3D24.  The imports are named by the
 * import-name table: 0x009F6F52 time, 0x009F7B94 gmtime, 0x009F700C localtime.
 *
 * THE FRAME'S TWO "GAPS" ARE /GZ GUARDS, NOT COMPILER TEMPORARIES.  Six slots
 * with only four values in them looks like MSVC spilling, and an earlier
 * attempt recorded it that way; it is not.  `uTime` has its address taken, so
 * /GZ brackets it with four bytes on each side exactly as it brackets an array
 * -- which is also why the frame descriptor names it at all.  0x18 is
 * pTm + guard + uTime + guard + iLocal + iGmt, and nothing here is the
 * compiler's.
 *
 * THE POINTER IS RELOADED PER FIELD AND THE SUM STAYS IN REGISTERS.  Retail
 * reads the local pTm before each of the four accesses but never spills the
 * running total, so the four terms are ONE expression; splitting them into
 * `iGmt = ...; iGmt += ...;` stores and reloads iGmt three extra times and does
 * not reproduce these bytes.  That is where the earlier attempt's 26 surplus
 * bytes were.
 *
 * The whole computation is skipped once the cache is set: the guard tests the
 * global against -1 and the return reads it back from memory either way, so
 * there is no separate result local.
 */
struct Rva007FEF80Tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

struct Rva007FEF80Tm *__cdecl gmtime( const long *timer );
struct Rva007FEF80Tm *__cdecl localtime( const long *timer );

/* -1 until the first call fills it in. */
extern int g_Rva012C3D24Offset;

int Rva007FEF80( void )
{
	int iGmt;
	int iLocal;
	long uTime;
	struct Rva007FEF80Tm *pTm;

	if ( g_Rva012C3D24Offset == -1 )
	{
		uTime = time( 0 );

		pTm = gmtime( &uTime );
		iGmt = pTm->tm_mday * 86400 + pTm->tm_hour * 3600
			+ pTm->tm_min * 60 + pTm->tm_sec;

		pTm = localtime( &uTime );
		iLocal = pTm->tm_mday * 86400 + pTm->tm_hour * 3600
			+ pTm->tm_min * 60 + pTm->tm_sec;

		g_Rva012C3D24Offset = iLocal - iGmt;
	}

	return g_Rva012C3D24Offset;
}

/* 0x007FDB60 is SocketInfo -- the query counterpart of the SocketControl at
 * 0x007FDEB0 -- and like that one it dispatches on a four-character selector
 * held as a bare imm32: 'conn', 'bind', 'peer' and 'stat' all read out of the
 * comparisons directly.  Three of the four are thin: 'bind' is getsockname,
 * while 'conn' and 'peer' are both getpeername, and it is the SELECTOR NAMES
 * that identify which sibling import is which -- 'bind' uses the one the
 * ledger already pins as getsockname, so the one the other two use is
 * getpeername.
 *
 * 'stat' is the real body, and it is a NON-BLOCKING CONNECT COMPLETION CHECK.
 * The frame descriptor gives retail's own names for all four locals --
 * fdwrite, fdexcept, tv and peeraddr -- and the first two are 0x104 bytes,
 * which is exactly fd_count plus 64 handles.  That fixes them as fd_set, and
 * the two long inline blocks that follow are then unmistakable: they are the
 * Winsock FD_SET macro expanded at /Od, scan-for-duplicate and all, each with
 * its own __i and each wrapped in the `do { } while ( 0 )` that leaves a
 * trailing `xor`/`jne` in the bytes.  The macro is reproduced here rather than
 * hand-inlined because only the macro form emits that.
 *
 * HOW THE STATE IS DECIDED, and the order matters: a zero timeout select is
 * run over both sets; an exception means failed, writable means connected, and
 * WRITABLE IS TESTED SECOND SO IT WINS.  Then, if the socket now looks
 * connected, getpeername is called as a confirmation -- and a -2 back from the
 * error translator, this library's "not connected", downgrades it to failed
 * again.  So a socket is only reported connected once the stack agrees twice.
 *
 * The flag is a SIGNED char: every read is movsx and the failure value is
 * written as 0xFF, so its three states are 1 connected, 0 still trying, -1
 * failed.  The function returns 1 or 0, never -1, so a caller using only the
 * return value cannot distinguish "failed" from "still connecting".
 *
 * Retail reuses the caller's length PARAMETER as scratch for getpeername --
 * the same habit as the address remap at 0x007FE310.
 */
struct Rva007FDB60FdSet
{
	unsigned int fd_count;
	unsigned int fd_array[ 64 ];
};

struct Rva007FDB60TimeVal
{
	long tv_sec;
	long tv_usec;
};

/* Winsock's FD_SET, which is what retail compiled.  It scans for the handle
 * before adding it and silently drops the add when the set is full. */
#define RVA007FDB60_FD_SET( fd, set )                                      \
	do {                                                                   \
		unsigned int __i;                                                  \
		for ( __i = 0; __i < ( set )->fd_count; __i++ )                    \
		{                                                                  \
			if ( ( set )->fd_array[ __i ] == ( fd ) )                      \
				break;                                                     \
		}                                                                  \
		if ( __i == ( set )->fd_count )                                    \
		{                                                                  \
			if ( ( set )->fd_count < 64 )                                  \
			{                                                              \
				( set )->fd_array[ __i ] = ( fd );                         \
				( set )->fd_count++;                                       \
			}                                                              \
		}                                                                  \
	} while ( 0 )

int __stdcall select( int nfds, struct Rva007FDB60FdSet *readfds,
	struct Rva007FDB60FdSet *writefds, struct Rva007FDB60FdSet *exceptfds,
	const struct Rva007FDB60TimeVal *timeout );
int __stdcall getpeername( unsigned int socket, void *name, int *nameLength );

int Rva007FDB60( struct Rva007FD4E0Socket *socket, int selector, void *buffer,
	int bufferLength )
{
	int iResult;
	struct Rva007FDB60FdSet fdwrite;
	struct Rva007FDB60FdSet fdexcept;
	struct Rva007FDB60TimeVal tv;
	char peeraddr[ 0x10 ];

	if ( buffer != 0 )
		memset( buffer, 0, bufferLength );

	if ( socket->m_socket == 0xFFFFFFFF )
		return -7;

	if ( selector == 'conn' )
	{
		getpeername( socket->m_socket, buffer, &bufferLength );
		return 0;
	}

	if ( selector == 'bind' )
	{
		getsockname( socket->m_socket, buffer, &bufferLength );
		return 0;
	}

	if ( selector == 'peer' )
	{
		getpeername( socket->m_socket, buffer, &bufferLength );
		return 0;
	}

	if ( selector == 'stat' )
	{
		if ( socket->m_opened == 0 )
		{
			fdwrite.fd_count = 0;
			fdexcept.fd_count = 0;
			RVA007FDB60_FD_SET( socket->m_socket, &fdwrite );
			RVA007FDB60_FD_SET( socket->m_socket, &fdexcept );

			tv.tv_sec = tv.tv_usec = 0;

			if ( select( 1, 0, &fdwrite, &fdexcept, &tv ) != 0 )
			{
				if ( fdexcept.fd_count > 0 )
					socket->m_opened = -1;
				if ( fdwrite.fd_count > 0 )
					socket->m_opened = 1;
			}
		}

		if ( socket->m_opened > 0 )
		{
			bufferLength = 0x10;
			iResult = Rva007FD540( getpeername( socket->m_socket, peeraddr,
				&bufferLength ) );
			if ( iResult == -2 )
				socket->m_opened = -1;
		}

		return socket->m_opened > 0;
	}

	return -1;
}
