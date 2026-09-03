// cl: /DNDEBUG /MD /GX /Od /GZ /GS
// Another module in the 0x00806480..0x00806B10 span, carrying the same /Od /GZ
// signature as the rest of this directory -- a frame pointer for code with no
// register pressure and `cmp ebp,esp` into the stack-check helper at 0x009F7502.
// Nothing in these four bodies names it: there is no string and no selector, so
// the file name and every function name are derived from addresses and assert
// nothing.  What the bodies DO show is that they share one record layout, which
// is why they share a file.

// 0x0080B070, the teardown all three destructors here hand the record's first
// pointer to; address-derived and pinned.
void Rva0080B070Destroy( void *object );

// 0x007F0030, the one-argument release the rest of this directory uses.
void Rva007F0030Free( void *block );

// An import thunk the ledger already names; the C spelling is what this call
// site needs.
extern "C" void Rva0081BDE4( void );

__declspec(dllimport) void __stdcall Rva01358F30Sleep( unsigned int ms );

// The two byte swaps in Y4DirtySock's range and the reset at 0x0080DFC0.
unsigned short Rva007FFA60Swap16( unsigned short value );   // 0x007FFA60
unsigned int   Rva007FFAD0( unsigned int value );           // 0x007FFAD0
// The second argument is a KEY POINTER, not a flag: 0x00806710 passes the
// 0x20-byte Secret it just derived, and 0x00806A90 passes null.
void Rva0080DFC0( void *object, const void *secret );        // 0x0080DFC0
int  Rva0080DF70( const char *key, char *secret, char *ticket ); // 0x0080DF70
extern "C" char *strncpy( char *dest, const char *src, unsigned int count );
extern "C" void *memcpy( void *dest, const void *src, unsigned int count );
extern "C" void *memset( void *dest, int value, unsigned int count );
void *Rva007F0000Alloc( int size );                         // 0x007F0000
unsigned short Rva007FF990Swap16( unsigned short value );   // 0x007FF990
unsigned int   Rva007FF9F0Swap32( unsigned int value );     // 0x007FF9F0
void *Rva0080B000Create( void );                            // 0x0080B000
int   Rva0080B150( void *object, void *addr, int addrLen );  // 0x0080B150
int   Rva0080B460( void *object, int mode );                // 0x0080B460
struct Rva00806580Record;
int   Rva00807370( Rva00806580Record *record, int selector, int flag,
		char *buffer, int bufferSize );                     // 0x00807370
int   Rva008076E0( Rva00806580Record *record, unsigned int *outA,
		unsigned int *outB, char **outText );               // 0x008076E0
void  Rva00806B10( Rva00806580Record *record );             // 0x00806B10
int   Rva0080E330( void *crypto, int length );              // 0x0080E330
// Accept at 0x0080B0A0, connect at 0x0080B1B0, the comm pump at 0x0080B4B0,
// send/recv/info through the comm object, and the three crypto helpers the
// packet path uses after a complete header has arrived.
extern "C" void *Rva0080B0A0( void *comm, int unsupported, void *address,
		int *addressLength );
extern "C" int   Rva0080B1B0( void *comm, int secu, char *name,
		unsigned int addr, unsigned int port );
extern "C" void  Rva0080B4B0( void *comm );
extern "C" int   Rva0080D980( void *comm, const char *data, int length );
extern "C" int   Rva0080DA50( void *comm, char *output, int length );
extern "C" int   Rva0080DBF0( void *comm, int selector, void *buffer,
		int bufferSize );
extern "C" void  Rva0080E1C0( void *crypto, unsigned char *data, int length );
extern "C" int   Rva0080E200( void *crypto, const unsigned char *data,
		int length );
extern "C" int   Rva0080E300( void *crypto, int length );
int   Rva00807520( Rva00806580Record *record, int length, int limit ); // 0x00807520
void  Rva0080E350( void *crypto, char *packet, int length );  // 0x0080E350
void  Rva0080E410( void *crypto, char *packet, int length );  // 0x0080E410
extern "C" unsigned int strlen( const char *text );

// The empty string this module hands back for a block with no payload.
extern char g_Rva0130ACE0Empty[];
unsigned int Rva007FEA00Tick( void );                       // 0x007FEA00

// The tick this module first ran at, filled in once and never again.
extern unsigned int g_Rva0130ACDCEpoch;

// Declared here rather than included: retail reaches WSAStartup by a direct
// rel32 to the stub at 0x0081BDF6, which a <winsock2.h> declaration's dllimport
// would not produce.  Only the first field is ever read, but the SIZE is
// load-bearing -- 0x190 is what the frame is built around.
struct Rva008064A0WsaData
{
	unsigned short wVersion;
	unsigned short wHighVersion;
	char szDescription[ 257 ];
	char szSystemStatus[ 129 ];
	unsigned short iMaxSockets;
	unsigned short iMaxUdpDg;
	char *lpVendorInfo;
};

extern "C" int __stdcall WSAStartup( unsigned short versionRequested,
		Rva008064A0WsaData *data );

// Only the five offsets these bodies touch are evidence.  +0x00 is a sub-object
// with its own teardown, +0x70 and +0x7C are plain blocks, +0x5C takes a state
// constant and +0x8C a boolean.  Everything between is padding and names nothing.
struct Rva00806580Record
{
	void *m_field00;             // +0x00
	// +0x04..+0x13 IS A SOCKADDR: 0x00806910 memsets exactly 0x10 bytes from
	// +0x04, writes 2 into the first word, and fills the next two fields from
	// its own address and port arguments through the byte swaps.
	short m_family;              // +0x04
	short m_port;                // +0x06 -- 'port', swapped back on the way out
	int   m_addr;                // +0x08 -- 'addr', likewise
	char  m_pad0C[ 0x08 ];
	int   m_localAddr;           // +0x14 -- 'ladr', returned raw
	int   m_localPort;           // +0x18 -- 'lprt', returned raw
	// A 0x3F-byte name with its own terminator: 0x00806710 strncpy's 0x3F bytes
	// here and then writes a zero at +0x5B, which is exactly +0x1C plus 0x3F.
	char  m_name[ 0x40 ];        // +0x1C
	int   m_field5C;             // +0x5C -- 'stat'
	int   m_field60;             // +0x60
	// THE OUTPUT BUFFER, named by 0x00807520: +0x70 is the block, +0x6C its
	// capacity, +0x64 how much has been written and +0x68 how much has been
	// sent.  'obuf' reporting +0x64 minus +0x68 is what is still queued.
	int   m_outUsed;             // +0x64
	int   m_outSent;             // +0x68
	int   m_outSize;             // +0x6C
	void *m_outBuffer;           // +0x70
	int   m_field74;             // +0x74 -- 'ibuf' is +0x74 minus +0x78
	int   m_field78;             // +0x78
	void *m_field7C;             // +0x7C -- gates 'ibuf'
	// 0x0C-byte header staging: 0x00806B10 receives the packet header here
	// while +0x7C is still null, then copies it into the allocated block.
	char  m_recvHead[ 0x0C ];    // +0x80
	short m_field8C;             // +0x8C -- 'secu', read SIGNED
	short m_field8E;             // +0x8E -- set by 0x00806A90
	char  m_key[ 0x54 ];         // +0x90
	int   m_fieldE4;             // +0xE4 -- 'cryp'; 0x90 + 0x54 lands exactly here
};

// 0x00806580 IS THE FULL TEARDOWN and the sleep in the middle is the whole
// story: it tears the sub-object down, WAITS 50 MILLISECONDS, calls an import,
// and only then frees the two blocks and the record.  A destructor that has to
// pause before releasing memory is waiting for something else to stop touching
// it -- the sub-object almost certainly owns a thread -- and the pause is
// unconditional, taken even when there was no sub-object to tear down.
//
// The record's own pointer is NOT nulled on the way out, unlike in the two
// bodies below; nothing can read it again, because the record is freed.
void Rva00806580( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
		Rva0080B070Destroy( record->m_field00 );

	Rva01358F30Sleep( 50 );
	Rva0081BDE4();

	if( record->m_field7C != 0 )
		Rva007F0030Free( record->m_field7C );

	if( record->m_outBuffer != 0 )
		Rva007F0030Free( record->m_outBuffer );

	Rva007F0030Free( record );
}

// 0x008068B0 and 0x00806A10 ARE BYTE-IDENTICAL apart from the displacements of
// their own two calls, and retail carries both.  That is not identical-code
// folding failing: folding would have left ONE body and two names pointing at
// it, and these are two bodies at two addresses.  So the source really does say
// this twice, and it is written out twice here rather than aliased.
//
// Both are the partial reset the full teardown above is the destructive form of:
// same sub-object, same +0x70 block, but each pointer is NULLED after release
// and the record survives with its state set to 4.
int Rva008068B0( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
	{
		Rva0080B070Destroy( record->m_field00 );
		record->m_field00 = 0;
	}

	if( record->m_outBuffer != 0 )
	{
		Rva007F0030Free( record->m_outBuffer );
		record->m_outBuffer = 0;
	}

	record->m_field5C = 4;
	return 0;
}

int Rva00806A10( Rva00806580Record *record )
{
	if( record->m_field00 != 0 )
	{
		Rva0080B070Destroy( record->m_field00 );
		record->m_field00 = 0;
	}

	if( record->m_outBuffer != 0 )
	{
		Rva007F0030Free( record->m_outBuffer );
		record->m_outBuffer = 0;
	}

	record->m_field5C = 4;
	return 0;
}

// 0x00806A70 stores a comparison, not its argument: the flag at +0x8C is set
// only when the value handed in is exactly 1, and it is stored SIXTEEN BITS
// WIDE.  Any other value -- including 2 -- clears it.
void Rva00806A70( Rva00806580Record *record, int value )
{
	record->m_field8C = (short)( value == 1 );
}

// 0x00806600 IS THE RECORD'S QUERY, and nine multi-character selectors are what
// say so -- 'port', 'addr', 'ladr', 'lprt', 'obuf', 'ibuf', 'stat', 'secu' and
// 'cryp', the same convention 0x007FDEB0's 'xmap'/'xdns' and 0x008053C0's
// 'bind' use.  They also name most of the layout above: two of them come back
// byte-swapped and two do not, which is what separates the wire-order pair at
// +0x06 and +0x08 from the host-order pair at +0x14 and +0x18.
//
// THE TWO BUFFER SELECTORS ARE DIFFERENCES, NOT FIELDS: 'obuf' is +0x64 minus
// +0x68 and 'ibuf' is +0x74 minus +0x78, so each pair is a write cursor and a
// read cursor and the answer is how much is pending.  'ibuf' is additionally
// gated on +0x7C and reports 0 when that is null -- the only arm here that
// needs a local, which is why the frame is four bytes.
//
// IT IS AN IF-CHAIN, NOT A SWITCH.  Each test is followed by its own body and a
// jump to the epilogue before the next test; a switch groups every comparison
// first.  'secu' is read with MOVSX, so that field is a signed short, and an
// unrecognised selector returns 0 rather than an error.
int Rva00806600( Rva00806580Record *record, int selector )
{
	int pending;

	if( selector == 'port' )
		return Rva007FFA60Swap16( record->m_port );
	if( selector == 'addr' )
		return Rva007FFAD0( record->m_addr );
	if( selector == 'ladr' )
		return record->m_localAddr;
	if( selector == 'lprt' )
		return record->m_localPort;
	if( selector == 'obuf' )
		return record->m_outUsed - record->m_outSent;
	if( selector == 'ibuf' )
	{
		if( record->m_field7C != 0 )
			pending = record->m_field74 - record->m_field78;
		else
			pending = 0;
		return pending;
	}
	if( selector == 'stat' )
		return record->m_field5C;
	if( selector == 'secu' )
		return record->m_field8C;
	if( selector == 'cryp' )
		return record->m_fieldE4;

	return 0;
}

// 0x00806A90 INSTALLS A 0x54-BYTE KEY, and 0x54 is not an arbitrary size: the
// body at 0x00806710 in this same span has /GZ locals named Secret[0x20] and
// Ticket[0x34], and 0x20 + 0x34 is exactly 0x54.  So what lands at +0x90 is
// that pair, and the flag at +0x8E records whether it is there.
//
// THE GUARD IS WRITTEN NEGATIVELY and that is what puts the clearing arm first:
// null, or zero length, or any length that is not 0x54, all take it.  A length
// test that both rejects zero AND demands 0x54 is redundant in its first half,
// and the redundancy is retail's.
//
// The key pointer is copied into a local before the guard runs and the copy is
// what the memcpy reads; and the clearing arm resets the sub-object at +0xE4,
// which is the same field 'cryp' reports, so installing no key tears the
// crypto state down rather than leaving it stale.
void Rva00806A90( Rva00806580Record *record, const void *key, int length )
{
	const void *p;

	p = key;

	if( key == 0 || length == 0 || length != 0x54 )
	{
		record->m_field8E = 0;
		Rva0080DFC0( &record->m_fieldE4, 0 );
	}
	else
	{
		record->m_field8E = 1;
		memcpy( record->m_key, p, 0x54 );
	}
}

// 0x008064A0 MAKES THE RECORD, and it is the counterpart of the teardown at
// 0x00806580: 0x2F0 bytes, zeroed, with the same three fields the resets touch
// set explicitly afterwards.  0x2F0 is also what fixes the layout's tail --
// +0xE4 is well inside it.
//
// WINSOCK IS STARTED FIRST AND ITS FAILURE IS FATAL, before anything is
// allocated, so a caller that gets null back has leaked nothing.  The version
// word it comes back with is DISCARDED here, unlike at 0x007FD080 where the
// same call's answer is byte-swapped and kept -- this module only cares that it
// worked.
//
// The epoch at 0x0130ACDC is stamped only if it is still zero, so the first
// record made in the process fixes it for every later one.
//
// THE THREE EXPLICIT ZEROES ARE REDUNDANT AFTER THE memset and they are
// retail's: +0x00, +0x5C and the 16-bit +0x8E are written again with the values
// the memset already left there.  Dropping them drops three stores.
Rva00806580Record *Rva008064A0( void )
{
	Rva00806580Record *record;
	Rva008064A0WsaData wsadata;

	if( WSAStartup( 2, &wsadata ) != 0 )
		return 0;

	if( g_Rva0130ACDCEpoch == 0 )
		g_Rva0130ACDCEpoch = Rva007FEA00Tick();

	record = (Rva00806580Record *)Rva007F0000Alloc( 0x2F0 );
	if( record != 0 )
	{
		memset( record, 0, 0x2F0 );
		record->m_field00 = 0;
		record->m_field5C = 0;
		record->m_field8E = 0;
	}

	return record;
}

// 0x00806910 IS THE OPEN, and the pairing is what reads it: it builds the
// sockaddr in the record, makes the sub-object with 0x0080B000 -- the
// constructor matching the 0x0080B070 teardown the three destructors above all
// call -- and then configures it twice before declaring the record ready.
//
// IT REFUSES TO RUN TWICE.  A record that already has a sub-object is rejected
// outright, so this is an open and not a reconnect; the reset at 0x008068B0 is
// what has to run in between.
//
// The address and port arrive in host order and are swapped in, which is the
// mirror of 'addr' and 'port' swapping them back out at 0x00806600 -- the
// record stores them the way the wire wants them.  The port argument is loaded
// SIXTEEN BITS WIDE at the call, so it is a short parameter and not a
// truncated int.
//
// EVERY FAILURE RETURNS -1 AND LEAVES THE SUB-OBJECT IN PLACE.  Neither
// configuration failure tears down what 0x0080B000 just built, so the caller
// must run a reset before trying again -- and the second attempt would then hit
// the refusal at the top if it did not.
int Rva00806910( Rva00806580Record *record, unsigned int addr,
		unsigned short port )
{
	if( record->m_field00 != 0 )
		return -1;

	if( record->m_field7C != 0 )
	{
		Rva007F0030Free( record->m_field7C );
		record->m_field7C = 0;
	}

	memset( &record->m_family, 0, 0x10 );
	record->m_family = 2;
	record->m_addr = Rva007FF9F0Swap32( addr );
	record->m_port = Rva007FF990Swap16( port );

	record->m_field00 = Rva0080B000Create();
	if( record->m_field00 == 0 )
		return -1;

	if( Rva0080B150( record->m_field00, &record->m_family, 0x10 ) < 0 )
		return -1;

	if( Rva0080B460( record->m_field00, 2 ) < 0 )
		return -1;

	record->m_field5C = 1;
	record->m_field60 = 0;
	record->m_field8E = 0;
	return 0;
}

// 0x00806710 IS THE SECURE OPEN, and it is 0x00806910 with a key step bolted
// on: the same refusal when a sub-object already exists, the same +0x7C
// release, the same 0x10-byte sockaddr built from swapped arguments.  What it
// adds is a name and, when a key was installed, a derivation.
//
// THE NAME FIELD SIZES ITSELF: 0x3F bytes are copied to +0x1C and a zero is
// then written at +0x5B, which is exactly +0x1C plus 0x3F.  strncpy does not
// terminate when it fills, so that store is the terminator and the field is
// 0x40 wide.  A null name is skipped entirely, terminator included, which
// leaves whatever was there before.
//
// THE KEY STEP IS GATED ON THE FLAG 0x00806A90 SETS, read with MOVSX from
// +0x8E.  It derives a 0x20-byte Secret and a 0x34-byte Ticket from the stored
// key -- 0x20 plus 0x34 is the 0x54 that key is -- then hands the Ticket to the
// selector 0x3F746963, '?tic', and the Secret to the crypto sub-object at
// +0xE4.  A derivation that does not report a positive result clears the flag,
// so the record falls back to unsecured rather than failing the open.
//
// Unlike 0x00806910 this body never makes a sub-object of its own: it requires
// one to be absent and then leaves it absent, which is what separates the two.
int Rva00806710( Rva00806580Record *record, const char *name, unsigned int addr,
		unsigned short port )
{
	char Secret[ 0x20 ];
	char Ticket[ 0x34 ];

	if( record->m_field00 != 0 )
		return -1;

	if( record->m_field7C != 0 )
	{
		Rva007F0030Free( record->m_field7C );
		record->m_field7C = 0;
	}

	memset( &record->m_family, 0, 0x10 );
	record->m_family = 2;
	record->m_addr = Rva007FF9F0Swap32( addr );
	record->m_port = Rva007FF990Swap16( port );

	if( name != 0 )
	{
		strncpy( record->m_name, name, 0x3F );
		record->m_name[ 0x3F ] = 0;
	}

	record->m_field5C = 2;
	record->m_field60 = 0;
	record->m_field8C = 0;

	if( record->m_field8E != 0 )
	{
		if( Rva0080DF70( record->m_key, Secret, Ticket ) > 0 )
		{
			Rva00807370( record, '?tic', 0, Ticket, 0x34 );
			Rva0080DFC0( &record->m_fieldE4, Secret );
		}
		else
		{
			record->m_field8E = 0;
		}
	}

	return 0;
}

// 0x008078B0 IS A CONDITIONAL RELEASE written as four early returns, not as one
// condition.  Each test compiles to `je` over a two-byte `jmp` -- the shape an
// inverted `if( ... ) return;` gives -- where a single && chain would branch
// straight to the end each time.
//
// What the four tests together say is that this only fires on a record in state
// 3 with nothing outstanding: no +0x70 block, no +0x7C block, and a sub-object
// still present.  Anything pending and it does nothing at all -- which is what
// makes this the idle-time collector rather than a destructor.
void Rva008078B0( Rva00806580Record *record )
{
	if( record->m_field5C != 3 )
		return;
	if( record->m_outBuffer != 0 )
		return;
	if( record->m_field7C != 0 )
		return;
	if( record->m_field00 == 0 )
		return;

	Rva0080B070Destroy( record->m_field00 );
	record->m_field00 = 0;
}

// 0x00807820 TAKES DELIVERY OF A BLOCK AND FREES IT.  It asks 0x008076E0 for a
// length, and on anything but a negative answer copies out of +0x7C at an
// offset of 0x0C -- so that block carries a 0x0C-byte header the caller never
// sees -- then releases it and nulls the field.
//
// THE FREE HAPPENS EVEN WHEN THE CALLER PASSED NO BUFFER.  Only the copy is
// conditional on the destination, so a caller reading the length alone still
// consumes the block; there is no way to peek.  The length is clamped DOWN to
// what arrived and never up, and the value returned is the real length rather
// than the clamped one -- so a caller with too small a buffer is told how much
// there was and has already lost the rest.
int Rva00807820( Rva00806580Record *record, unsigned int *outA,
		unsigned int *outB, void *dest, int destSize )
{
	int result;

	result = Rva008076E0( record, outA, outB, 0 );
	if( result >= 0 )
	{
		if( destSize > result )
			destSize = result;

		if( dest != 0 )
			memcpy( dest, (char *)record->m_field7C + 0x0C, destSize );

		Rva007F0030Free( record->m_field7C );
		record->m_field7C = 0;
	}

	return result;
}

// 0x008076E0 HANDS BACK THE ARRIVED BLOCK, and the shape of that block is the
// whole result: two big-endian dwords at +0x00 and +0x04, then text from +0x0C
// on -- which is the 0x0C header 0x00807820 skips when it copies the payload
// out.  The length returned is the total minus that header.
//
// "COMPLETE" IS THE TWO CURSORS BEING EQUAL, not merely non-zero: +0x74 and
// +0x78 are the same pair 'ibuf' subtracts, so nothing pending is what makes a
// block readable.  When they differ the pump at 0x00806B10 is run once and the
// test repeated; it is never run twice.
//
// A CALLER THAT WANTS NOTHING GETS NOTHING PUMPED.  All three out-pointers null
// means -1 without running the pump at all, so this doubles as a poll that has
// no side effect -- and every other combination pumps.
//
// The text is TERMINATED IN PLACE, one past the payload, so the block must have
// room for it; an empty payload takes a shared empty string instead, which is
// also what stops that store writing before the buffer.
int Rva008076E0( Rva00806580Record *record, unsigned int *outA,
		unsigned int *outB, char **outText )
{
	int length;
	unsigned char *p;
	char *text;

	if( record->m_field7C == 0 || record->m_field78 != record->m_field74 )
	{
		if( outA == 0 && outB == 0 && outText == 0 )
			return -1;

		Rva00806B10( record );

		if( record->m_field7C == 0 || record->m_field78 != record->m_field74 )
			return -1;
	}

	p = (unsigned char *)record->m_field7C;
	length = record->m_field74 - 0x0C;
	text = (char *)record->m_field7C + 0x0C;

	if( length < 1 )
		text = g_Rva0130ACE0Empty;
	else
		text[ length ] = 0;

	if( outA != 0 )
		*outA = ( p[ 0 ] << 24 ) | ( p[ 1 ] << 16 ) | ( p[ 2 ] << 8 ) | p[ 3 ];

	if( outB != 0 )
		*outB = ( p[ 4 ] << 24 ) | ( p[ 5 ] << 16 ) | ( p[ 6 ] << 8 ) | p[ 7 ];

	if( outText != 0 )
		*outText = text;

	return length;
}

// 0x00807370 QUEUES ONE PACKET, and the twelve byte stores are its whole
// header: a big-endian kind at +0x00, a big-endian flag at +0x04 and the
// big-endian total at +0x08, with the payload from +0x0C -- which is exactly
// the 0x0C header 0x008076E0 reads back and 0x00807820 skips.  The two ends of
// this module agree byte for byte.
//
// THE SELECTOR IS A VERB PLUS A NOUN.  This body clears the key flag when the
// kind is 0x40746963, '@tic', while 0x00806710 sends 0x3F746963, '?tic' -- same
// three letters, '@' against '?'.  So the leading character is set-versus-query
// and the rest names what is being carried; nothing else in this file would
// have shown that, because each body only ever sees one of the pair.
//
// THE LENGTH IS NEGOTIATED, NOT ASSUMED.  The crypto sub-object is asked what a
// payload of this size becomes, and the output reservation must come back with
// AT LEAST that much or the packet is dropped -- so the header's total is the
// wrapped length and not the caller's.
//
// The header is written AFTER the payload is copied and after the cursor has
// already advanced, through a second pointer holding the same address; both
// locals are retail's.  A negative length means the payload is text and is
// measured with its terminator, and a zero-length payload skips the copy but
// still gets a header.
//
// The pump runs at both ends: once before anything is reserved and once after
// the packet is complete.
int Rva00807370( Rva00806580Record *record, int kind, int flag,
		char *data, int length )
{
	int total;
	char *header;
	char *packet;

	Rva00806B10( record );

	if( length < 0 )
		length = strlen( data ) + 1;

	total = Rva0080E330( &record->m_fieldE4, length + 0x0C );

	if( Rva00807520( record, total, 0x8000 ) < total )
		return -1;

	packet = (char *)record->m_outBuffer + record->m_outUsed;
	header = packet;

	if( length > 0 )
		memcpy( packet + 0x0C, data, length );

	record->m_outUsed = record->m_outUsed + total;

	header[ 8 ] = (char)( total >> 24 );
	header[ 9 ] = (char)( total >> 16 );
	header[ 10 ] = (char)( total >> 8 );
	header[ 11 ] = (char)total;
	header[ 0 ] = (char)( kind >> 24 );
	header[ 1 ] = (char)( kind >> 16 );
	header[ 2 ] = (char)( kind >> 8 );
	header[ 3 ] = (char)kind;
	header[ 4 ] = (char)( flag >> 24 );
	header[ 5 ] = (char)( flag >> 16 );
	header[ 6 ] = (char)( flag >> 8 );
	header[ 7 ] = (char)flag;

	Rva0080E350( &record->m_fieldE4, packet, total );
	Rva0080E410( &record->m_fieldE4, packet, total );

	if( kind == '@tic' )
		record->m_field8E = 0;

	Rva00806B10( record );
	return 0;
}

// 0x00807520 MAKES ROOM IN THE OUTPUT BUFFER, and it does three separate
// things depending on what it finds.  With no buffer at all it simply
// allocates one of exactly the requested size and returns what is free.
//
// Otherwise it COMPACTS FIRST.  It walks the queued packets from the start,
// stepping by each one's own big-endian length at +0x08 -- the header
// 0x00807370 writes -- until it passes what has been sent, backs off by one
// packet if it overshot, and slides the remainder down.  So packets are only
// ever dropped on a packet boundary, which is why the walk needs the length
// field rather than just the sent cursor.
//
// Only then does it grow, and the new size is used + requested + LIMIT rather
// than just what was asked for -- the caller's third argument is headroom, not
// a cap.  A failed allocation returns 0 and leaves the old buffer in place, so
// nothing is lost; every other path returns the free space, which is what
// 0x00807370 compares against its own requirement.
int Rva00807520( Rva00806580Record *record, int length, int limit )
{
	int size;
	int used;
	char *grown;
	unsigned char *p;

	if( record->m_outBuffer == 0 )
	{
		record->m_outUsed = 0;
		record->m_outSent = 0;
		record->m_outSize = length;
		record->m_outBuffer = Rva007F0000Alloc( record->m_outSize );
		return record->m_outSize - record->m_outUsed;
	}

	for( size = 0, used = size; used < record->m_outSent; used += size )
	{
		p = (unsigned char *)record->m_outBuffer + used;
		size = ( p[ 8 ] << 24 ) | ( p[ 9 ] << 16 ) | ( p[ 10 ] << 8 ) | p[ 11 ];
	}

	if( used > record->m_outSent )
		used -= size;

	if( used > 0 )
	{
		memcpy( record->m_outBuffer, (char *)record->m_outBuffer + used,
				record->m_outUsed - used );
		record->m_outUsed = record->m_outUsed - used;
		record->m_outSent = record->m_outSent - used;
	}

	if( length > record->m_outSize - record->m_outUsed )
	{
		grown = (char *)Rva007F0000Alloc( record->m_outUsed + length + limit );
		if( grown == 0 )
			return 0;

		memcpy( grown, record->m_outBuffer, record->m_outUsed );
		Rva007F0030Free( record->m_outBuffer );
		record->m_outBuffer = grown;
		record->m_outSize = record->m_outUsed + length + limit;
	}

	return record->m_outSize - record->m_outUsed;
}

// 0x00806B10 IS THE PUMP.  It is the 2102-byte body the two packet helpers
// above call: 0x008076E0 runs it once when no complete inbound block is
// waiting, and 0x00807370 runs it before reserving space and again after the
// packet is assembled.  The /GZ frame names two arrays -- `len` at ebp-12 and
// `addr` at ebp-40 -- and /GS puts a cookie in front of `addr[0x10]`.
//
// THE STATE WORD AT +0x5C IS A SEQUENCE, not a switch: 1 is accept, 2 is
// connect, 3 is connected, 4 is the listen-idle that 3 falls into when it has
// no sub-object.  Each arm can change the word, so a later arm in the same
// call sees the new value -- 3 with no socket becomes 4, and 4 with queued
// output becomes 2.
//
// A COMPLETE INBOUND PACKET is the two cursors at +0x74/+0x78 being equal.
// Until then the 0x0C-byte header is received into +0x80, decrypted, and used
// to size the +0x7C block; the rest of the payload is received into that block
// and checked by the crypto sub-object at +0xE4.
void Rva00806B10( Rva00806580Record *record )
{
	int len;
	unsigned char *packet;
	char addr[ 0x10 ];
	void *ref;

	if( record->m_field5C == 3 && record->m_field00 == 0 )
	{
		if( record->m_field7C != 0 )
			Rva007F0030Free( record->m_field7C );

		record->m_field74 = 0xC;
		record->m_field78 = 0xC;
		record->m_field7C = Rva007F0000Alloc( record->m_field74 + 1 );
		packet = (unsigned char *)record->m_field7C;
		packet[ 3 ] = 0xFF;
		packet[ 2 ] = 0xFF;
		packet[ 1 ] = 0xFF;
		packet[ 0 ] = 0xFF;
		packet[ 7 ] = 0xFE;
		packet[ 6 ] = 0xFE;
		packet[ 5 ] = 0xFE;
		packet[ 4 ] = 0xFE;
		packet[ 10 ] = 0;
		packet[ 9 ] = 0;
		packet[ 8 ] = 0;
		packet[ 11 ] = 0xC;
		record->m_field5C = 4;
	}

	if( record->m_field5C == 4 && record->m_outBuffer != 0 )
	{
		record->m_field5C = 2;
		record->m_field60 = 0;
	}

	if( record->m_field5C == 1 )
	{
		len = 0x10;
		ref = Rva0080B0A0( record->m_field00, 0, addr, &len );
		if( ref == 0 )
			return;

		Rva0080B070Destroy( record->m_field00 );
		record->m_field00 = ref;
		record->m_field5C = 3;
		record->m_outSent = 0;

		if( record->m_field7C != 0 )
			Rva007F0030Free( record->m_field7C );

		record->m_field74 = 0xC;
		record->m_field78 = 0xC;
		record->m_field7C = Rva007F0000Alloc( record->m_field74 + 1 );
		packet = (unsigned char *)record->m_field7C;
		packet[ 3 ] = 0xFF;
		packet[ 2 ] = 0xFF;
		packet[ 1 ] = 0xFF;
		packet[ 0 ] = 0xFF;
		packet[ 7 ] = 0xFF;
		packet[ 6 ] = 0xFF;
		packet[ 5 ] = 0xFF;
		packet[ 4 ] = 0xFF;
		packet[ 10 ] = 0;
		packet[ 9 ] = 0;
		packet[ 8 ] = 0;
		packet[ 11 ] = 0xC;
	}

	if( record->m_field5C == 2 )
	{
		if( Rva007FEA00Tick() > (unsigned int)record->m_field60 )
		{
			if( record->m_field00 != 0 )
				Rva0080B070Destroy( record->m_field00 );

			record->m_field00 = Rva0080B000Create();
			if( record->m_field00 == 0 )
				return;

			if( Rva0080B1B0( record->m_field00,
					record->m_field8C != 0,
					record->m_name,
					Rva007FFAD0( record->m_addr ),
					Rva007FFA60Swap16( record->m_port ) ) < 0 )
				return;

			record->m_field60 = Rva007FEA00Tick() + 0x7530;
			Rva0080DFC0( &record->m_fieldE4, 0 );
		}

		if( record->m_field00 == 0 )
			return;

		Rva0080B4B0( record->m_field00 );

		if( Rva0080DBF0( record->m_field00, 'stat', 0, 0 ) <= 0 )
			return;

		if( record->m_addr == 0 )
			Rva0080DBF0( record->m_field00, 'peer', &record->m_family, 0x10 );

		if( Rva0080DBF0( record->m_field00, 'bind', addr, 0x10 ) == 0 )
		{
			record->m_localAddr = Rva007FFAD0( *(unsigned int *)( addr + 4 ) );
			record->m_localPort = Rva007FFA60Swap16( *(unsigned short *)( addr + 2 ) );
		}

		record->m_field5C = 3;
		record->m_outSent = 0;

		if( record->m_field7C != 0 )
			Rva007F0030Free( record->m_field7C );

		record->m_field74 = 0xC;
		record->m_field78 = 0xC;
		record->m_field7C = Rva007F0000Alloc( record->m_field74 + 1 );
		packet = (unsigned char *)record->m_field7C;
		packet[ 3 ] = 0xFF;
		packet[ 2 ] = 0xFF;
		packet[ 1 ] = 0xFF;
		packet[ 0 ] = 0xFF;
		packet[ 7 ] = 0xFF;
		packet[ 6 ] = 0xFF;
		packet[ 5 ] = 0xFF;
		packet[ 4 ] = 0xFF;
		packet[ 10 ] = 0;
		packet[ 9 ] = 0;
		packet[ 8 ] = 0;
		packet[ 11 ] = 0xC;
	}

	if( record->m_field00 == 0 )
		return;

	Rva0080B4B0( record->m_field00 );

	if( record->m_outBuffer != 0 && record->m_outSent != record->m_outUsed )
	{
		len = Rva0080D980( record->m_field00,
				(char *)record->m_outBuffer + record->m_outSent,
				record->m_outUsed - record->m_outSent );
		if( len < 0 )
		{
			Rva0080B070Destroy( record->m_field00 );
			record->m_field00 = 0;
			return;
		}

		if( len > 0 )
			record->m_outSent = record->m_outSent + len;

		if( record->m_outSent == record->m_outUsed )
		{
			Rva007F0030Free( record->m_outBuffer );
			record->m_outBuffer = 0;
		}
	}

	if( record->m_field7C == 0 )
	{
		if( record->m_field74 == record->m_field78 )
		{
			record->m_field74 = 0xC;
			record->m_field78 = 0;
		}

		len = Rva0080DA50( record->m_field00,
				(char *)record + 0x80 + record->m_field78,
				record->m_field74 - record->m_field78 );
		if( len < 0 )
		{
			Rva0080B070Destroy( record->m_field00 );
			record->m_field00 = 0;
			return;
		}

		if( len > 0 )
			record->m_field78 = record->m_field78 + len;

		if( record->m_field78 == record->m_field74 )
		{
			packet = (unsigned char *)record + 0x80;
			Rva0080E1C0( &record->m_fieldE4, packet, 0xC );
			record->m_field74 = ( packet[ 8 ] << 24 ) | ( packet[ 9 ] << 16 )
					| ( packet[ 10 ] << 8 ) | packet[ 11 ];

			if( record->m_field74 < 0xC || record->m_field74 > 0x8000 )
			{
				Rva0080B070Destroy( record->m_field00 );
				record->m_field00 = 0;
				return;
			}

			record->m_field7C = Rva007F0000Alloc( record->m_field74 + 1 );
			if( record->m_field7C == 0 )
			{
				Rva0080B070Destroy( record->m_field00 );
				record->m_field00 = 0;
				return;
			}

			memcpy( record->m_field7C, (char *)record + 0x80, record->m_field78 );

			if( record->m_field78 == record->m_field74
					&& record->m_outBuffer != 0
					&& record->m_outSent == record->m_outUsed )
			{
				Rva007F0030Free( record->m_outBuffer );
				record->m_outBuffer = 0;
			}
		}
	}

	if( record->m_field7C != 0 )
	{
		if( record->m_field78 < record->m_field74 )
		{
			len = Rva0080DA50( record->m_field00,
					(char *)record->m_field7C + record->m_field78,
					record->m_field74 - record->m_field78 );
			if( len < 0 )
			{
				Rva0080B070Destroy( record->m_field00 );
				record->m_field00 = 0;
				return;
			}

			if( len > 0 )
				record->m_field78 = record->m_field78 + len;

			if( record->m_field78 == record->m_field74 )
			{
				Rva0080E1C0( &record->m_fieldE4,
						(unsigned char *)record->m_field7C + 0xC,
						record->m_field78 - 0xC );
				if( Rva0080E200( &record->m_fieldE4,
						(unsigned char *)record->m_field7C,
						record->m_field74 ) < 0 )
				{
					Rva0080B070Destroy( record->m_field00 );
					record->m_field00 = 0;
					return;
				}

				record->m_field78 = Rva0080E300( &record->m_fieldE4,
						record->m_field74 );
				record->m_field74 = record->m_field78;
			}

			if( record->m_field78 == record->m_field74
					&& record->m_outBuffer != 0
					&& record->m_outSent == record->m_outUsed )
			{
				Rva007F0030Free( record->m_outBuffer );
				record->m_outBuffer = 0;
			}
		}
	}
}
