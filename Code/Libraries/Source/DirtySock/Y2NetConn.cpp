// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// EA's DirtySock netconn.  THE MODULE NAMES ITSELF AND SO DOES THE FUNCTION:
// the body here logs "netconn: warning - calling NetConnStatus() while module
// is not initialized", which gives both the source file this belongs to and
// what this body is called.  The /Od /GZ signature is the same one the rest of
// this directory carries.
//
// The three module words it reports are address-derived; nothing names them but
// the selectors they answer.
extern int g_Rva0130A590State;   // 'open'
extern int g_Rva0130A594Conn;    // 'conn'
extern int g_Rva0130A598Online;  // 'onln'

int  Rva007FE780Printf( const char *format, ... );    // 0x007FE780
int  Rva007FDEE0( void );                             // 0x007FDEE0
unsigned int Rva007EB520NetConnMAC( void *adapter );   // 0x007EB520
void Rva007FD080( int priority );                     // 0x007FD080
void Rva007FD270( void );                             // 0x007FD270
void Rva007F8D30( void );                             // 0x007F8D30
__declspec(dllimport) void __stdcall Rva01358F30Sleep( unsigned int ms );

// The idle-handler table 0x007F8D30 sweeps: sixteen slots of a function and a
// ref, indexed with an eight-byte stride.  Sixteen is the loop's own bound.
// The handler is CALLED with its own ref and a tick, cdecl, by 0x007F8C90.
typedef void ( __cdecl *IdleHandlerProc )( void *ref, unsigned int tick );

struct IdleHandlerSlot
{
	void *m_function;   // +0x00 -- cast to IdleHandlerProc where it is called
	void *m_ref;        // +0x04
};

extern IdleHandlerSlot g_Rva0130A7B0Idle[ 16 ];

// The tick the pump at 0x007F8C90 will next run at.
extern unsigned int g_Rva0130A850Next;

unsigned int Rva007FEA00Tick( void );                 // 0x007FEA00

// The MAC 0x007F89F0 asks for and the text it caches beside it: 0x0130A830 is
// the 0x10-byte buffer handed to the 'macx' selector, 0x0130A840 the fourteen
// bytes of text written over it.  They are 0x10 apart, so the buffer is exactly
// the size the call declares.
extern unsigned char g_Rva0130A830Mac[ 0x10 ];
extern char g_Rva0130A840Text[ 0x10 ];

// "0123456789abcdef" at 0x0112B918, sixteen bytes with NO terminator -- the
// next literal in .rdata starts immediately after it.  An extern is the only
// honest spelling; a string literal here would be seventeen bytes.
extern const char g_Rva0112B918HexDigits[];

// The default parameter string 0x007EB380 substitutes for a null one.
extern char g_Rva0130A59CDefault[];
extern "C" void *memcpy( void *dest, const void *src, unsigned int count );

// FIVE SELECTORS, and the first one is answered BEFORE the initialisation
// guard: 'open' reports the module's own state word, so a caller can ask
// whether netconn is up without tripping the warning that every other selector
// trips when it is not.  That ordering is the point of the body's shape.
//
// 'conn' and 'onln' are two more module words, 'addr' defers to the address
// self test at 0x007FDEE0, and 'macx' fills the caller's buffer with six bytes
// -- a MAC address -- taken from the 0xF0-byte block /GZ names `Adapter`.
// Anything else is -1.
//
// THE 'macx' SUCCESS TEST CAN NEVER FAIL, and that is retail's.  `test eax,eax`
// clears the carry flag, so the `jb` that follows it is never taken and the
// `return 0` it guards is unreachable.  That is what an unsigned result
// compared `>= 0` compiles to at /Od -- the comparison is vacuous, MSVC emits
// it anyway, and writing the test as a signed one produces a different
// instruction.  So the helper's result is unsigned and the failure arm is dead.
//
// The third parameter is never read.  Callers pass it; this body does not use
// it, and it cannot be dropped without changing every call site's stack.
int Rva007EB410NetConnStatus( int selector, void *buffer, int bufferSize )
{
	char Adapter[ 0xF0 ];

	if( selector == 'open' )
		return g_Rva0130A590State;

	if( g_Rva0130A590State != 1 )
	{
		Rva007FE780Printf( "netconn: warning - calling NetConnStatus() "
				"while module is not initialized\n" );
		return -1;
	}

	if( selector == 'onln' )
		return g_Rva0130A598Online;

	if( selector == 'conn' )
		return g_Rva0130A594Conn;

	if( selector == 'addr' )
		return Rva007FDEE0();

	if( selector == 'macx' )
	{
		if( Rva007EB520NetConnMAC( Adapter ) >= 0 )
		{
			memcpy( buffer, Adapter, 6 );
			return 1;
		}
		return 0;
	}

	return -1;
}

// The NCB Win32's netbios API takes.  Its field offsets are not a guess: the
// body below writes the command at +0x00, reads the return code at +0x01, sets
// the buffer at +0x04 and the length at +0x08, copies a name to +0x0A and
// steps the LANA number at +0x30 -- which is the documented layout, and 0x40 is
// the size it memsets.
struct NCB
{
	unsigned char  ncb_command;      // +0x00
	unsigned char  ncb_retcode;      // +0x01
	unsigned char  ncb_lsn;
	unsigned char  ncb_num;
	void          *ncb_buffer;       // +0x04
	unsigned short ncb_length;       // +0x08
	char           ncb_callname[ 16 ];  // +0x0A
	char           ncb_name[ 16 ];   // +0x1A
	unsigned char  ncb_rto;
	unsigned char  ncb_sto;
	void         (*ncb_post)( void );
	unsigned char  ncb_lana_num;     // +0x30
	unsigned char  ncb_cmd_cplt;
	char           ncb_reserve[ 10 ];
	void          *ncb_event;
};

extern "C" unsigned char __stdcall Netbios( NCB *ncb );
extern "C" char *strcpy( char *dest, const char *src );
extern "C" void *memset( void *dest, int value, unsigned int count );

// 0x007EB520 IS NetConnMAC and it says so twice, in "NetConnMAC: The NCBRESET
// return code is: 0x%x" and "NetConnMAC: Could not find any valid network
// addapters!" -- retail's spelling of `adapters` included.  The first of those
// also names the command: 0x32 is NCBRESET and the 0x33 the second half uses is
// NCBASTAT, the adapter-status query that returns a MAC.
//
// IT RESETS LANAS UNTIL ONE WORKS.  The loop runs 0 through 9 and BREAKS on the
// first reset that succeeds, so the LANA the second half queries is whichever
// one that was -- which is why the post-loop test on the same counter is not
// redundant: reaching 10 means every LANA failed.  Return code 0x23 is expected
// and stays quiet; every other failure is logged and the walk continues.
//
// THE CALLNAME COPY OVERRUNS BY ONE.  "*" followed by fifteen spaces is sixteen
// characters, and strcpy writes a seventeenth for the terminator -- into the
// first byte of ncb_name, which the memset has already zeroed.  It is harmless
// and it is retail's.
//
// The buffer is handed over with a length of 0xF0, which is the size of the
// block NetConnStatus declares for it, and only six bytes of the answer are
// ever used.  A failed query returns -1 WITHOUT logging: the "no adapters"
// line belongs to the loop running out, not to the query failing.
unsigned int Rva007EB520NetConnMAC( void *adapter )
{
	NCB ncb;
	int result;
	int lana;

	memset( &ncb, 0, 0x40 );
	ncb.ncb_command = 0x32;

	for( ncb.ncb_lana_num = 0; ncb.ncb_lana_num < 10; ncb.ncb_lana_num++ )
	{
		result = Netbios( &ncb );
		if( result != 0 )
		{
			if( result != 0x23 )
				Rva007FE780Printf(
						"NetConnMAC: The NCBRESET return code is: 0x%x \n",
						ncb.ncb_retcode );
		}
		else
		{
			break;
		}
	}

	if( ncb.ncb_lana_num < 10 )
	{
		lana = ncb.ncb_lana_num;
		memset( &ncb, 0, 0x40 );
		ncb.ncb_command = 0x33;
		ncb.ncb_lana_num = (unsigned char)lana;
		strcpy( ncb.ncb_callname, "*               " );
		ncb.ncb_buffer = adapter;
		ncb.ncb_length = 0xF0;

		if( Netbios( &ncb ) == 0 )
			return 0;
	}
	else
	{
		Rva007FE780Printf(
				"NetConnMAC: Could not find any valid network addapters!\n" );
	}

	return (unsigned int)-1;
}

// 0x007EB380 IS THE STARTUP, and what settles that is which word it writes:
// the same 0x0130A590 NetConnStatus answers 'open' with, set to 1 -- the exact
// value NetConnStatus's own guard demands before it will answer anything else.
// It also brings up the DirtySock module underneath, at priority 2.
//
// IT REFUSES TO RUN TWICE and says so by returning -1 on any non-zero state,
// which is checked before anything else happens.
//
// THE PARAMETER IS SUBSTITUTED AND THEN NEVER USED.  A null argument is
// replaced with a default string and the local is not read again -- so whatever
// this was meant to configure, nothing here reads it.  The store is retail's.
int Rva007EB380Startup( char *params )
{
	if( g_Rva0130A590State != 0 )
		return -1;

	if( params == 0 )
		params = g_Rva0130A59CDefault;

	Rva007FD080( 2 );

	g_Rva0130A590State = 1;
	g_Rva0130A594Conn = 0;
	g_Rva0130A598Online = 0;
	return 0;
}

// 0x007EB650 is its counterpart: two teardowns and the state back to zero, so
// the next startup will run.  It checks nothing first -- shutting down twice is
// allowed here where starting twice is not -- and always reports success.
int Rva007EB650Shutdown( void )
{
	Rva007F8D30();
	Rva007FD270();
	g_Rva0130A590State = 0;
	return 0;
}

// A one-line forwarder onto Sleep, with the /GZ stack check around the import
// call and nothing else in it.
void Rva007EB680Sleep( unsigned int ms )
{
	Rva01358F30Sleep( ms );
}

// THREE SEVEN-BYTE BODIES THAT RETURN ZERO, byte-identical and at three
// separate addresses.  Retail carries all three: identical-code folding would
// have left one body with three names, and these are three bodies.  So the
// source really does declare three functions, and they are written out three
// times rather than aliased.  Nothing says what any of them is for.
int Rva007EB3E0( void )
{
	return 0;
}

int Rva007EB3F0( void )
{
	return 0;
}

int Rva007EB400( void )
{
	return 0;
}

// 0x007F8D30 belongs to netconn too, and its own line says so: "netconn:
// removing idle handler at shutdown".  It sweeps all sixteen slots of the
// handler table, complaining about each one still registered and clearing both
// halves of it.
//
// THE WARNING IS PER SLOT AND CARRIES NOTHING.  It names no handler and no
// index, so a caller that leaked several sees the same line several times --
// which is also how the count is visible at all.  The sweep is unconditional:
// there is no way to shut down quietly having unregistered properly, because
// an empty slot simply prints nothing.
void Rva007F8D30( void )
{
	int i;

	for( i = 0; i < 0x10; i++ )
	{
		if( g_Rva0130A7B0Idle[ i ].m_function != 0 )
		{
			Rva007FE780Printf(
					"netconn: removing idle handler at shutdown\n" );
			g_Rva0130A7B0Idle[ i ].m_function = 0;
			g_Rva0130A7B0Idle[ i ].m_ref = 0;
		}
	}
}

// 0x007F8B60 REGISTERS AN IDLE HANDLER, and its two log lines separate the two
// ways that fails: "ignoring add of an idle handler that is already
// registered" for a duplicate and "unable to add new idle handler as table is
// full" for no space, reported as -1 and -2.  A caller can tell them apart
// from the return alone.
//
// BOTH CHECKS RUN IN ONE PASS.  Each slot is tested first for being the same
// pair and then for being free, so the handler lands in the first empty slot
// AT OR AFTER any duplicate -- which means a duplicate earlier in the table is
// always found before an empty slot later, and duplicates are impossible.
// Identity is the PAIR: the same function with a different ref is not a
// duplicate.
int Rva007F8B60( void *function, void *ref )
{
	int i;

	for( i = 0; i < 0x10; i++ )
	{
		if( g_Rva0130A7B0Idle[ i ].m_function == function
				&& g_Rva0130A7B0Idle[ i ].m_ref == ref )
		{
			Rva007FE780Printf(
					"netconn: ignoring add of an idle handler that is "
					"already registered\n" );
			return -1;
		}

		if( g_Rva0130A7B0Idle[ i ].m_function == 0 )
		{
			g_Rva0130A7B0Idle[ i ].m_function = function;
			g_Rva0130A7B0Idle[ i ].m_ref = ref;
			return 0;
		}
	}

	Rva007FE780Printf(
			"netconn: unable to add new idle handler as table is full\n" );
	return -2;
}

// 0x007F8C00 is the matching remove -- same pair test, both halves cleared --
// and it complains about a handler that was never there: "ignoring delete of an
// idle handler that is not registered".  Unlike the add it has only one failure
// and reports -1 for it.
int Rva007F8C00( void *function, void *ref )
{
	int i;

	for( i = 0; i < 0x10; i++ )
	{
		if( g_Rva0130A7B0Idle[ i ].m_function == function
				&& g_Rva0130A7B0Idle[ i ].m_ref == ref )
		{
			g_Rva0130A7B0Idle[ i ].m_function = 0;
			g_Rva0130A7B0Idle[ i ].m_ref = 0;
			return 0;
		}
	}

	Rva007FE780Printf(
			"netconn: ignoring delete of an idle handler that is not "
			"registered\n" );
	return -1;
}

// 0x007F8C90 IS THE PUMP, and the throttle it applies is the interesting part:
// five ticks between passes -- and it applies ONLY WHEN NETCONN IS UP.  A zero
// from NetConnStatus('open') jumps straight past the deadline check to the
// walk, so a module that is not started runs its handlers on every call and one
// that is started runs them at most every five ticks.
//
// THE DEADLINE IS SET FROM A SECOND READING OF THE CLOCK, not from the one it
// was compared against, and each handler gets a THIRD.  Three separate reads,
// so the tick a handler sees is later than the one that let the pass through.
//
// The handler takes its own ref and that tick, cdecl, which is what types the
// table's first word.
void Rva007F8C90( void )
{
	int i;

	if( Rva007EB410NetConnStatus( 'open', 0, 0 ) != 0 )
	{
		if( Rva007FEA00Tick() < g_Rva0130A850Next )
			return;

		g_Rva0130A850Next = Rva007FEA00Tick() + 5;
	}

	for( i = 0; i < 0x10; i++ )
	{
		if( g_Rva0130A7B0Idle[ i ].m_function != 0 )
			( (IdleHandlerProc)g_Rva0130A7B0Idle[ i ].m_function )(
					g_Rva0130A7B0Idle[ i ].m_ref, Rva007FEA00Tick() );
	}
}

// 0x007F89F0 CACHES THE MAC AS TEXT, and the cache test is the first byte of
// the result itself: a non-empty string is returned unchanged, so the whole
// body runs at most once per process.  There is no way to invalidate it.
//
// The form is '$' followed by twelve lower-case hex digits and a terminator --
// the same '$'-prefixed shape 0x00807AB0 uses for an address, which is what
// makes these two the text encodings of this library rather than one-offs.
//
// THE TWELVE DIGITS ARE WRITTEN OUT LONGHAND, not looped.  Each of the six
// bytes is loaded twice, shifted or masked, and indexed into the digit table,
// which is twelve straight copies of the same four instructions; a loop would
// need an index and a bound and does not reproduce them.
//
// A FAILED QUERY LEAVES THE CACHE EMPTY AND RETURNS IT ANYWAY.  The caller gets
// a pointer to an empty string rather than null, and the next call will try
// again -- which is the one thing the cache test buys beyond speed.
char *Rva007F89F0( void )
{
	if( g_Rva0130A840Text[ 0 ] == 0 )
	{
		if( Rva007EB410NetConnStatus( 'macx', g_Rva0130A830Mac, 0x10 ) > 0 )
		{
			g_Rva0130A840Text[ 0 ] = '$';
			g_Rva0130A840Text[ 1 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 0 ] >> 4 ];
			g_Rva0130A840Text[ 2 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 0 ] & 0x0F ];
			g_Rva0130A840Text[ 3 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 1 ] >> 4 ];
			g_Rva0130A840Text[ 4 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 1 ] & 0x0F ];
			g_Rva0130A840Text[ 5 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 2 ] >> 4 ];
			g_Rva0130A840Text[ 6 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 2 ] & 0x0F ];
			g_Rva0130A840Text[ 7 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 3 ] >> 4 ];
			g_Rva0130A840Text[ 8 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 3 ] & 0x0F ];
			g_Rva0130A840Text[ 9 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 4 ] >> 4 ];
			g_Rva0130A840Text[ 10 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 4 ] & 0x0F ];
			g_Rva0130A840Text[ 11 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 5 ] >> 4 ];
			g_Rva0130A840Text[ 12 ] = g_Rva0112B918HexDigits[ g_Rva0130A830Mac[ 5 ] & 0x0F ];
			g_Rva0130A840Text[ 13 ] = 0;
		}
	}

	return g_Rva0130A840Text;
}
