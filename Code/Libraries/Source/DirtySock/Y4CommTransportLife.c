// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- the construct/destroy pair for a THIRD comm transport,
 * distinct again from the two in Y4CommRingIdle.c and Y4CommTickIdle.c.  Its
 * lock sits at +0x1F4 where theirs are at +0x1EC and +0x1E8, and its object is
 * 0x224 bytes where theirs are smaller; the constructor's own allocation size
 * settles that.
 *
 * WHAT THE OBJECT IS.  Its first fourteen words are a table of FUNCTION
 * POINTERS, filled in one by one, and the first two entries are this file's
 * own two bodies -- construct at +0x00 and destroy at +0x04.  That is
 * DirtySock's usual shape for a transport: a plain C struct whose leading
 * fields are the operations, so a caller holds one pointer and reaches
 * everything through it.  The other twelve land in the address range
 * commudp.cpp already occupies, which is what places this pair.
 *
 * The remaining pointer operands are declared address-derived and asserted to
 * be nothing more: they are DIR32 sites, so the gate fills them from retail
 * and the names below never reach the bytes.
 */

void *Rva007F0000Alloc( int size );
void Rva007F0030( void *object );
int Rva007FE780( const char *format, ... );
unsigned int Rva007FEA00( void );
void *__cdecl memset( void *destination, int value, unsigned int count );
void *__cdecl memcpy( void *destination, const void *source,
	unsigned int count );
char *__cdecl strcpy( char *destination, const char *source );

extern unsigned int g_Rva012C4DF4;

/* Lock construct and destruct; the acquire and release live in the socket
 * unit and are already named there. */
void Rva007FEA20( void *lock );
void Rva007FEAA0( void *lock );

void Rva00817210Op( void );
void Rva00817230Op( void );
void Rva00818D90Op( void );
void Rva00817240Op( void );
void Rva00819300Op( void );
void Rva008172C0Op( void );
void Rva008171C0Op( void );
void Rva00817340Op( void );
void Rva008173A0Op( void );
void Rva008173C0Op( void );
void Rva00818BF0Op( void );
void Rva00818D20Op( void );

struct Rva00816BF0Comm
{
	/* +0x00..+0x34, and the first two are this file's own bodies. */
	void *m_op[ 14 ];
	void ( __cdecl *m_sendProc )( struct Rva00816BF0Comm *comm,
		const void *payload, int length, unsigned int tick ); /* +0x38 */
	/* THE RECEIVE CALLBACK, called by 0x008187E0 with the transport, the
	 * payload, its length and its arrival tick.  Null means nobody is
	 * listening and the record is still queued. */
	void ( __cdecl *m_receiveProc )( struct Rva00816BF0Comm *comm,
		const void *payload, int length, unsigned int tick );  /* +0x3C */
	char m_gap0b[ 0x08 ];
	/* A SECOND COPY of the socket pointer.  0x00816DF0 writes the same value
	 * to this and to +0x7C in consecutive statements; nothing converted so far
	 * reads this one, so what it is for is not yet established -- only that it
	 * is kept in step. */
	struct Rva007FD4E0Socket *m_socketAlias;        /* +0x48 */
	/* THE NAME BUFFER IS 0x20, NOT the 0x2C the next field's offset alone
	 * suggested: 0x00818500 writes endpoint fields starting at +0x6C, which
	 * is where the buffer has to stop. */
	char m_name[ 0x20 ];            /* +0x4C */
	/* The four endpoint fields, at the same offsets the ring transport uses
	 * for them -- local address, peer address, local port, peer port, with
	 * the ports as shorts.  Two different objects agreeing on this run and on
	 * +0x7C suggests a shared header, though nothing converted so far proves
	 * one. */
	unsigned int m_localAddress;    /* +0x6C */
	unsigned int m_peerAddress;     /* +0x70 */
	unsigned short m_localPort;     /* +0x74 */
	unsigned short m_peerPort;      /* +0x76 */
	struct Rva00816BF0Comm *m_next; /* +0x78 */
	/* The socket OBJECT, not a handle: the destructor hands it straight to the
	 * socket destroy at 0x007FD3F0. */
	struct Rva007FD4E0Socket *m_socket;     /* +0x7C */
	char m_peer[ 0x10 ];            /* +0x80 */
	int m_state;                    /* +0x90 */
	/* A HASH OF THE CONNECTION STRING'S TAIL.  0x00818FF0 finds the '#' in
	 * the text it is given and hashes from there to the end, storing the
	 * result here; the connect and close messages then carry it out as their
	 * third word.  So it identifies which session on a host is meant, not the
	 * host. */
	int m_sessionHash;              /* +0x94 */
	int m_recvRecordSize;           /* +0x98 */
	int m_recvBufferSize;           /* +0x9C */
	/* The two receive cursors.  0x00818BF0 compares them for emptiness and
	 * reads the record at +0xA8 plus +0xA4, and 0x00818D20 advances +0xA4
	 * after a successful read -- so +0xA0 is where records arrive and +0xA4 is
	 * where they are taken from. */
	int m_recvWriteOffset;          /* +0xA0 */
	int m_recvReadOffset;           /* +0xA4 */
	unsigned char *m_recvBuffer;    /* +0xA8 */
	/* Both rings get a sequence set to 0x65 by the reset at 0x00819260 -- one
	 * here and one at +0xD0 -- alongside their cursors being zeroed.  101 as a
	 * starting sequence rather than 0 is what makes "never sent" and "sequence
	 * zero" distinguishable on the wire. */
	int m_recvSequence;             /* +0xAC */
	/* A COPY of the receive sequence, taken by 0x00818AD0 immediately before
	 * it reports one and used only to build that report.  Keeping the copy
	 * rather than reading the live field twice is what makes the number sent
	 * and the number remembered the same one. */
	int m_reportedSequence;         /* +0xB0 */
	int m_recvCounter;              /* +0xB4 */
	int m_sendRecordSize;           /* +0xB8 */
	int m_sendBufferSize;           /* +0xBC */
	/* The two send cursors, proven by the depth calculation at 0x00817100:
	 * the distance from +0xC4 to +0xC0 taken modulo the buffer size and
	 * divided by the record size, which only reads as a count of records if
	 * these are the write and read positions. */
	int m_sendWriteOffset;          /* +0xC0 */
	int m_sendReadOffset;           /* +0xC4 */
	/* A THIRD SEND CURSOR, between the read and write ones.  The ack handler
	 * at 0x008186C0 drags it along with the read cursor while retiring, and
	 * snaps it back to the read cursor when a code-4 message arrives -- so it
	 * marks how far transmission has got, distinctly from how far
	 * acknowledgement has. */
	int m_sendAckOffset;            /* +0xC8 */
	unsigned char *m_sendBuffer;    /* +0xCC */
	int m_sendSequence;             /* +0xD0 */
	char m_gap4[ 0x04 ];
	/* Two timestamps, both BACKDATED five seconds by the reset. */
	unsigned int m_tickA;           /* +0xD8 */
	unsigned int m_tickB;           /* +0xDC */
	char m_gap5[ 0x114 ];
	char m_lock[ 4 ];               /* +0x1F4 */
	char m_tail[ 0x20 ];
	/* A RE-ENTRANCY DEPTH, raised across the whole of 0x008187E0 and lowered
	 * again at its end -- including across the user callback, which is the
	 * only place that could re-enter. */
	int m_depth;                    /* +0x218 */
	/* A FLAG WORD AND ITS VALUE, written together under the lock by
	 * 0x008171C0: the value goes into +0x220 and bit 1 is set in +0x21C.  A
	 * bit per installed thing beside the thing itself is how a caller can ask
	 * "was this ever set" without a sentinel. */
	int m_flags;                    /* +0x21C */
	void *m_value;                  /* +0x220 */
};

struct Rva007FD4E0Socket;
int Rva007FD3F0( struct Rva007FD4E0Socket *socket );

extern char g_Rva012C4F88Name[];
extern struct Rva00816BF0Comm *g_Rva0130B188List;

struct Rva00816BF0Comm *Rva00816BF0( int maxPacket, int recvCount,
	int sendCount );
void Rva00816E70( struct Rva00816BF0Comm *comm );
void Rva00816DF0( struct Rva00816BF0Comm *comm,
	struct Rva007FD4E0Socket *socket );
void Rva00816E10( struct Rva00816BF0Comm *comm );
int Rva00816F60( struct Rva00816BF0Comm *comm );
int Rva00817100( struct Rva00816BF0Comm *comm, int unused );
void Rva00817140( struct Rva00816BF0Comm *comm );

/* THE TWO QUEUE SIZINGS ARE THE INTERESTING PART, and they are identical:
 * a record is the caller's maximum packet plus 0x10 of per-record header --
 * which is where the timestamp at +0x00, the length at +0x04 and the leading
 * data byte come from -- then rounded UP to a multiple of four.
 *
 * The rounding is `(n + 3) & 0x7FFC`, an AND rather than a modulo, and the
 * mask does two jobs: it clears the low two bits for the alignment and it also
 * clears everything above 0x7FFC.  So a maximum packet larger than about 32KB
 * does not fail, it WRAPS to a small record size.  That is a real limit of
 * this constructor and nothing here checks for it.
 *
 * Neither buffer allocation is checked either, though the object's own is.
 */
struct Rva00816BF0Comm *Rva00816BF0( int maxPacket, int recvCount,
	int sendCount )
{
	struct Rva00816BF0Comm *comm;

	comm = (struct Rva00816BF0Comm *)Rva007F0000Alloc( 0x224 );
	if ( comm == 0 )
		return 0;

	memset( comm, 0, 0x224 );

	comm->m_op[  0 ] = (void *)Rva00816BF0;
	comm->m_op[  1 ] = (void *)Rva00816E70;
	comm->m_op[  2 ] = (void *)Rva00817210Op;
	comm->m_op[  3 ] = (void *)Rva00817230Op;
	comm->m_op[  4 ] = (void *)Rva00818D90Op;
	comm->m_op[  5 ] = (void *)Rva00817240Op;
	comm->m_op[  6 ] = (void *)Rva00819300Op;
	comm->m_op[  7 ] = (void *)Rva008172C0Op;
	comm->m_op[  8 ] = (void *)Rva008171C0Op;
	comm->m_op[  9 ] = (void *)Rva00817340Op;
	comm->m_op[ 10 ] = (void *)Rva008173A0Op;
	comm->m_op[ 11 ] = (void *)Rva008173C0Op;
	comm->m_op[ 12 ] = (void *)Rva00818BF0Op;
	comm->m_op[ 13 ] = (void *)Rva00818D20Op;

	strcpy( comm->m_name, g_Rva012C4F88Name );
	Rva007FEA20( comm->m_lock );

	comm->m_recvRecordSize = maxPacket + 0x10;
	comm->m_recvRecordSize = ( comm->m_recvRecordSize + 3 ) & 0x7FFC;
	comm->m_recvBufferSize = comm->m_recvRecordSize * recvCount;
	comm->m_recvBuffer = (unsigned char *)
		Rva007F0000Alloc( comm->m_recvBufferSize );

	comm->m_sendRecordSize = maxPacket + 0x10;
	comm->m_sendRecordSize = ( comm->m_sendRecordSize + 3 ) & 0x7FFC;
	comm->m_sendBufferSize = comm->m_sendRecordSize * sendCount;
	comm->m_sendBuffer = (unsigned char *)
		Rva007F0000Alloc( comm->m_sendBufferSize );

	Rva00816DF0( comm, 0 );

	memset( comm->m_peer, 0, 0x10 );
	comm->m_state = 1;
	comm->m_sessionHash = 0;

	Rva00816E10( comm );
	return comm;
}

/* THE SOCKET IS SHARED, AND THIS IS WHERE THAT SHOWS.  Before destroying it
 * the body walks the global list of transports looking for ANOTHER one using
 * the same socket, and destroys it only if none is found.  That is a
 * reference count done by search rather than by counter -- cheap when the list
 * is short, and it means the socket outlives whichever transport happens to be
 * torn down first.
 *
 * The scan relies on this object already being unlinked from that list; the
 * unlink is one of the two calls made before it.
 *
 * The three frees at the end are in allocation order -- receive buffer, send
 * buffer, then the object -- and none of them is null-checked, which is
 * consistent with the constructor never checking the two buffer allocations
 * either.
 */
void Rva00816E70( struct Rva00816BF0Comm *comm )
{
	struct Rva00816BF0Comm *p;

	Rva00817100( comm, 0xC8 );
	Rva00817140( comm );

	if ( comm->m_state == 4 )
		Rva00816F60( comm );

	if ( comm->m_socket != 0 )
	{
		for ( p = g_Rva0130B188List; p != 0; p = p->m_next )
		{
			if ( p->m_socket == comm->m_socket )
				break;
		}

		if ( p == 0 )
		{
			Rva007FD3F0( comm->m_socket );
			Rva00816DF0( comm, 0 );
		}
	}

	Rva007FEAA0( comm->m_lock );
	Rva007F0030( comm->m_recvBuffer );
	Rva007F0030( comm->m_sendBuffer );
	Rva007F0030( comm );
}

/* The registry the transports keep themselves in, and the lock guarding it.
 * Both are constructed and destroyed BY the register and unregister bodies
 * below rather than by any module init. */
extern struct Rva00816BF0Comm *g_Rva0130B188List;
extern char g_Rva0130AF38Lock[ 4 ];
extern int g_Rva0130AD08Count;

void Rva007FEBD0( void *lock );
void Rva007FECB0( void *lock );

/* 0x00816DF0 attaches or detaches the socket, and writes it to TWO fields --
 * +0x7C and +0x48 -- one after the other.  The constructor and the destructor
 * both call it with a null socket, so it is also the detach.
 */
void Rva00816DF0( struct Rva00816BF0Comm *comm,
	struct Rva007FD4E0Socket *socket )
{
	comm->m_socket = socket;
	comm->m_socketAlias = socket;
}

/* 0x00816E10 REGISTERS the transport, and the interesting part is that it
 * builds its own lock on the way.
 *
 * The list head being null is taken to mean "nothing has registered yet", and
 * on that path the lock is CONSTRUCTED and a counter zeroed before anything
 * else.  So there is no module initialiser for this registry: the first
 * registration creates it and, in the unregister below, the last one destroys
 * it.  THAT LAZY CONSTRUCTION IS ITSELF UNGUARDED -- the lock cannot protect
 * its own creation -- so two threads registering the first two transports at
 * once would race.  Retail's, and stated rather than quietly fixed.
 *
 * The insertion itself is an ordinary push at the head, under the lock.
 */
void Rva00816E10( struct Rva00816BF0Comm *comm )
{
	if ( g_Rva0130B188List == 0 )
	{
		Rva007FEA20( g_Rva0130AF38Lock );
		g_Rva0130AD08Count = 0;
	}

	Rva007FEBD0( g_Rva0130AF38Lock );

	comm->m_next = g_Rva0130B188List;
	g_Rva0130B188List = comm;

	Rva007FECB0( g_Rva0130AF38Lock );
}

/* 0x00817140 UNREGISTERS it, and mirrors the lazy construction: when the list
 * empties, the lock is destroyed again.
 *
 * The unlink walks a POINTER TO the link rather than the node, so the head and
 * every interior link are one case -- the same technique the socket destroy in
 * the socket unit uses.
 *
 * THE SEARCH HAS NO TERMINATION GUARD.  Its only exit is finding the node; a
 * transport that is not on the list walks off the end of the chain.  Nothing
 * here checks for null, and the constructor is what makes that safe, since a
 * transport is registered before it can be handed out.  It is still a real
 * hazard and is not something to add a check for -- the check would change the
 * bytes.
 *
 * The lock is released BEFORE the emptiness test, so the destroy happens
 * outside it, which is the only order that can work: destroying a lock you
 * still hold would not.
 */
void Rva00817140( struct Rva00816BF0Comm *comm )
{
	struct Rva00816BF0Comm **ppLink;

	Rva007FEBD0( g_Rva0130AF38Lock );

	for ( ppLink = &g_Rva0130B188List; *ppLink != comm;
		ppLink = &( *ppLink )->m_next )
	{
		/* the search is the whole loop */
	}

	*ppLink = comm->m_next;

	Rva007FECB0( g_Rva0130AF38Lock );

	if ( g_Rva0130B188List == 0 )
		Rva007FEAA0( g_Rva0130AF38Lock );
}

/* 0x00817100 REPORTS THE SEND QUEUE DEPTH -- and it is not what its call site
 * suggested.  The destructor invokes it with a second argument of 0xC8, which
 * reads like a timeout, and discards the result; this body IGNORES that
 * argument entirely and returns a count of outstanding records.
 *
 * Both facts are stated rather than smoothed over.  The parameter is declared
 * because the call site pushes it -- two arguments and an eight-byte cleanup
 * -- but nothing here reads it, so a one-parameter definition would compile to
 * the same bytes and misdescribe the interface.  Whether retail meant this to
 * drain for 0xC8 milliseconds and never finished it is not something the bytes
 * can say.
 */
int Rva00817100( struct Rva00816BF0Comm *comm, int unused )
{
	return ( ( comm->m_sendWriteOffset + comm->m_sendBufferSize
		- comm->m_sendReadOffset ) % comm->m_sendBufferSize )
		/ comm->m_sendRecordSize;
}

/* 0x00816F60 is the CLOSE, and it only runs from state 4 -- the state the
 * handshake's 0x13 packet drives the connection into.  Anything else returns
 * immediately, which is why the destructor guards its call the same way.
 *
 * It builds a message on the stack the size of the transport object itself,
 * fills in exactly three words of it, and hands it to 0x00817030.  The third
 * of those carries +0x94 out of the object, and the field is cleared straight
 * afterwards -- so whatever it holds is being handed OVER rather than copied,
 * and the object must not keep it.
 *
 * THE MESSAGE IS OTHERWISE UNINITIALISED.  Only +0x00, +0x08 and +0x0C are
 * written; the rest is whatever the /GZ fill left.  The recipient therefore
 * reads at most those three, and the size is a buffer allowance rather than a
 * payload.
 *
 * State goes to 5 last, so 4 means "peer asked to close" and 5 means "close
 * has been sent".
 */
struct Rva00816F60Message
{
	/* THE PAYLOAD LENGTH, not a kind.  The control senders set it to zero and
	 * that reads either way; 0x008187E0 settles it by testing this field for
	 * zero to reject an empty data record, and the submit at 0x00817030 uses
	 * it as the length it puts on the wire. */
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04, the arrival stamp once queued */
	/* EITHER A CONTROL CODE OR THE MESSAGE'S OWN SEQUENCE, and the two share
	 * the field without ambiguity because sequences start at 0x65: 1 is
	 * connect, 3 is close, 4 is a retransmit request, and anything from 101
	 * upwards is a data sequence.  That is what the reset's odd-looking choice
	 * of 0x65 buys -- it reserves a hundred values for control. */
	int m_code;                     /* +0x08 */
	/* A session hash for the control codes, an acknowledged sequence for the
	 * data ones. */
	int m_value;                    /* +0x0C */
	/* 0x228 in total, four bytes MORE than the transport object -- close, but
	 * not the same type, so the size is taken from the frame rather than
	 * assumed to be a copy of the object. */
	char m_body[ 0x218 ];
};

/* Returns the submit result; the close discards it, 0x00818620 returns it. */
int Rva00817030( struct Rva00816BF0Comm *comm,
	struct Rva00816F60Message *message );

int Rva00816F60( struct Rva00816BF0Comm *comm )
{
	struct Rva00816F60Message message;

	if ( comm->m_state != 4 )
		return 0;

	message.m_length = 0;
	message.m_code = 3;
	message.m_value = comm->m_sessionHash;

	Rva00817030( comm, &message );

	comm->m_sessionHash = 0;
	comm->m_state = 5;
	return 0;
}

/* 0x008171C0 installs a value and RECORDS THAT IT WAS INSTALLED, both under
 * the lock.  The value lands at +0x220 and bit 1 is set in the flag word at
 * +0x21C.  Setting a bit beside the value rather than relying on the value
 * being non-null is what lets a caller install a null one and still have it
 * count -- and it is why the two writes have to be atomic with respect to each
 * other, which is what the lock is doing here.
 */
void Rva008171C0( struct Rva00816BF0Comm *comm, void *value )
{
	Rva007FEBD0( comm->m_lock );

	comm->m_value = value;
	comm->m_flags = comm->m_flags | 2;

	Rva007FECB0( comm->m_lock );
}

/* 0x00817240 DISCONNECTS, returning the transport to the state the constructor
 * left it in, and the interesting part is what happens to the socket.
 *
 * If the connection is established, the socket pointer is CLEARED FIRST.  That
 * makes the block below it unreachable, so an established transport gives up
 * its socket WITHOUT closing it -- consistent with the destructor's scan,
 * which exists precisely because a socket can be shared.  From any other state
 * the socket is closed and destroyed.  The two paths are written as separate
 * ifs and only their order makes them exclusive; reading them as an if/else
 * would describe the same behaviour but not these bytes.
 *
 * It also opens by calling the queue-depth body with 0xC8 and discarding the
 * result, exactly as the destructor does -- the same call, the same unused
 * argument, the same ignored answer, in both of the places that would want a
 * drain.
 */
int Rva00817240( struct Rva00816BF0Comm *comm )
{
	Rva00817100( comm, 0xC8 );

	if ( comm->m_state == 3 )
		Rva00816DF0( comm, 0 );

	if ( comm->m_socket != 0 )
	{
		Rva00816F60( comm );
		Rva007FD3F0( comm->m_socket );
		Rva00816DF0( comm, 0 );
	}

	comm->m_state = 1;
	return 0;
}

/* 0x008172C0 IS A SECOND COPY OF THE DISCONNECT ABOVE.  The two bodies are
 * identical byte for byte except for their call displacements, which differ
 * only because the functions sit at different addresses -- so this is real
 * duplicated code that the linker did NOT fold, not one function reached two
 * ways.
 *
 * Which of the two the operation table points at is settled elsewhere: the
 * constructor stores 0xC172C0 into the table, so THIS is the entry point a
 * caller reaches through the object, and 0x00817240 is the copy reached some
 * other way.  Nothing here says why there are two; both are converted because
 * both addresses are real code and the ledger needs each claimed.
 */
int Rva008172C0( struct Rva00816BF0Comm *comm )
{
	Rva00817100( comm, 0xC8 );

	if ( comm->m_state == 3 )
		Rva00816DF0( comm, 0 );

	if ( comm->m_socket != 0 )
	{
		Rva00816F60( comm );
		Rva007FD3F0( comm->m_socket );
		Rva00816DF0( comm, 0 );
	}

	comm->m_state = 1;
	return 0;
}

/* 0x00817340 MAPS THE INTERNAL STATE ONTO A SMALLER PUBLIC ONE, and the
 * grouping is the interesting part because it LOSES information deliberately.
 *
 *   internal 2 or 3  ->  2      connecting and established report the same
 *   internal 1 or 5  ->  1      never opened and closed report the same
 *   internal 4       ->  3      peer asked to close
 *   anything else    ->  4
 *
 * So a caller polling this CANNOT TELL "still connecting" FROM "connected",
 * nor "fresh" from "finished".  Anything wanting that has to read +0x90
 * directly.  The pairs are written as separate comparisons joined by ||, not
 * as a switch, which is what keeps this a chain of tests rather than a table.
 */
int Rva00817340( struct Rva00816BF0Comm *comm )
{
	if ( comm->m_state == 2 || comm->m_state == 3 )
		return 2;

	if ( comm->m_state == 1 || comm->m_state == 5 )
		return 1;

	if ( comm->m_state == 4 )
		return 3;

	return 4;
}

int Rva007FEB00( void *lock );

/* 0x00818D20 forwards four arguments and advances the receive cursor only when
 * the inner call reports success, so a failure leaves the slot to be retried.
 * Nothing here inspects the four, so their types are not recoverable and they
 * are declared as plain words rather than guessed at -- converting 0x00818BF0
 * is what would settle them.
 */
/* Settled by converting it: a buffer, a size and an optional out-pointer,
 * not the plain words this was declared as while nothing had inspected it. */
int Rva00818BF0( struct Rva00816BF0Comm *comm, void *buffer, int size,
	unsigned int *when );

int Rva00818D20( struct Rva00816BF0Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	int iResult;

	iResult = Rva00818BF0( comm, buffer, size, when );

	if ( iResult >= 0 )
	{
		comm->m_recvReadOffset = ( comm->m_recvReadOffset + comm->m_recvRecordSize )
			% comm->m_recvBufferSize;
	}

	return iResult;
}

/* 0x00818CB0 is the GLOBAL PUMP, and it finally explains the counter the
 * registry zeroes when it builds the lock.
 *
 * The lock is TRIED.  On success the tick is read ONCE and the worker is
 * driven with that same timestamp until it reports nothing left to do -- so a
 * whole pass shares one consistent time rather than sampling per iteration,
 * the same discipline the other transport's callback uses.  The counter is
 * then cleared.
 *
 * ON FAILURE THE COUNTER IS INCREMENTED INSTEAD.  So +0x0130AD08 counts
 * CONSECUTIVE MISSED PUMPS -- how many times the pump was called while another
 * thread held the lock -- and any successful pass resets it to zero.  That is
 * a contention measure, not a total, and neither body alone shows it: the
 * registry only zeroes it at construction, and this one only makes sense once
 * both branches are read together.
 *
 * The driving loop has an EMPTY BODY; all the work is in the condition.
 *
 * ITS THREE PARAMETERS ARE THE SOCKET-CALLBACK SIGNATURE and none of them is
 * read.  0x00818BF0 calls it as (0, 0, comm) -- handle, flags, ref -- which is
 * exactly how this library installs socket callbacks everywhere else, so the
 * pump is both installed as one and called directly.  A no-argument definition
 * compiles to identical bytes, since the body only touches globals, but it
 * would misdescribe the interface and no caller could then pass anything.
 */
int Rva00817B30( unsigned int tick );

int Rva00818CB0( unsigned int socket, int flags,
	struct Rva00816BF0Comm *ref )
{
	unsigned int uTick;

	if ( Rva007FEB00( g_Rva0130AF38Lock ) != 0 )
	{
		uTick = Rva007FEA00();

		while ( Rva00817B30( uTick ) > 0 )
		{
			/* the work is the condition */
		}

		g_Rva0130AD08Count = 0;
		Rva007FECB0( g_Rva0130AF38Lock );
	}
	else
	{
		g_Rva0130AD08Count = g_Rva0130AD08Count + 1;
	}

	return 0;
}

/* A RECEIVED RECORD in this transport, and its header is 0x10 bytes -- exactly
 * the per-record overhead the constructor adds to the caller's maximum packet
 * size, which is what fixes the payload offset.
 *
 * NOTE THIS IS NOT THE OTHER TRANSPORT'S RECORD.  There the length sits at
 * +0x04 and the payload at +0x08 behind a one-byte header; here the length is
 * at +0x00, the timestamp at +0x04, and the payload starts at +0x10 with no
 * header byte.  Two transports, two wire formats.
 */
struct Rva00818BF0Record
{
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04 */
	char m_reserved[ 0x08 ];
	unsigned char m_data[ 4 ];      /* +0x10 */
};

/* 0x00818BF0 DEQUEUES ONE RECEIVED RECORD.  Same double test as the other
 * transport's: pump only if the queue looks empty, then re-test, so a pump
 * that produced nothing still returns -7 rather than reading a stale slot.
 *
 * THE COPY IS CLAMPED AND THE RETURN IS NOT, again: a caller with a buffer
 * smaller than the record gets a truncated copy and the FULL length back, so
 * comparing the two is the only way to notice.  Unlike the other transport
 * there is no minus-one here -- the stored length IS the payload length,
 * because this record format has no header byte inside the payload.
 */
int Rva00818BF0( struct Rva00816BF0Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	struct Rva00818BF0Record *record;
	int iCopy;

	if ( comm->m_recvReadOffset == comm->m_recvWriteOffset )
		Rva00818CB0( 0, 0, comm );

	if ( comm->m_recvReadOffset == comm->m_recvWriteOffset )
		return -7;

	record = (struct Rva00818BF0Record *)( comm->m_recvBuffer
		+ comm->m_recvReadOffset );

	if ( record->m_length < size )
		iCopy = record->m_length;
	else
		iCopy = size;

	memcpy( buffer, record->m_data, iCopy );

	if ( when != 0 )
		*when = record->m_tick;

	return record->m_length;
}

char *__cdecl strchr( const char *text, int ch );

/* 0x00818FF0 computes the SESSION HASH from a connection string.
 *
 * It looks for a '#' and does nothing at all if there is none -- the field
 * keeps whatever it had, rather than being cleared -- then hashes from the
 * '#' INCLUSIVE to the end of the string.  Including the separator is
 * deliberate in the sense that the bytes show it: the scan starts at the
 * pointer strchr returned, not one past it.
 *
 * The hash is the same rotating-XOR used at 0x007FF080 in the socket unit:
 * top five bits saved, accumulator shifted left five, saved bits brought back
 * at the bottom by an ARITHMETIC shift right of 27, character folded in last.
 * The sar is what makes the accumulator signed, and the character is read with
 * movsx, so the text is plain char.
 */
void Rva00818FF0( struct Rva00816BF0Comm *comm, const char *text )
{
	char *p;
	int i;
	int uHash;
	int uCarry;

	p = strchr( text, '#' );

	if ( p != 0 )
	{
		for ( i = 0, uHash = 0; p[ i ] != 0; i++ )
		{
			uCarry = uHash & 0xF8000000;
			uHash = uHash << 5;
			uHash = ( uCarry >> 27 ) ^ uHash;
			uHash = p[ i ] ^ uHash;
		}

		comm->m_sessionHash = uHash;
	}
}

/* 0x00818620 SENDS THE CONNECT MESSAGE, and it is the close's counterpart:
 * the same stack message, the same three words filled in, differing only in
 * the code -- 1 here against 3 there.
 *
 * TWO DIFFERENCES FROM THE CLOSE ARE WORTH NOTING.  There is no state guard,
 * so this can be sent from any state; and the session hash is NOT cleared
 * afterwards, where the close clears it.  So connect carries the hash and
 * keeps it, and close carries it and gives it up -- which is consistent with
 * the field identifying the session for as long as one is wanted.
 *
 * It also returns the submit result, where the close discards it.
 */
int Rva00818620( struct Rva00816BF0Comm *comm )
{
	struct Rva00816F60Message message;

	message.m_length = 0;
	message.m_code = 1;
	message.m_value = comm->m_sessionHash;

	return Rva00817030( comm, &message );
}

/* 0x00819260 RESETS THE CONNECTION without touching the buffers themselves --
 * only the cursors, the counters, the two sequences and the two clocks.  So it
 * is a reuse path: the allocations the constructor made survive it.
 *
 * BOTH SEQUENCES START AT 0x65, NOT ZERO.  Starting at 101 is what lets a peer
 * tell "nothing has been sent yet" from "sequence zero arrived", which a
 * zero-initialised sequence cannot express.
 *
 * BOTH CLOCKS ARE BACKDATED FIVE SECONDS, the same trick the handshake uses
 * with one second: setting them to the past rather than to now makes the first
 * timeout comparison behave as though the interval had already elapsed, so
 * whatever they gate fires immediately instead of waiting out a full period.
 * The two calls are separate, so the two fields can differ by however long the
 * first one took.
 */
void Rva00819260( struct Rva00816BF0Comm *comm )
{
	comm->m_sendWriteOffset = 0;
	comm->m_sendReadOffset = 0;
	comm->m_sendAckOffset = 0;
	comm->m_sendSequence = 0x65;

	comm->m_recvWriteOffset = 0;
	comm->m_recvReadOffset = 0;
	comm->m_recvSequence = 0x65;
	comm->m_recvCounter = 0;

	comm->m_tickA = Rva007FEA00() - 5000;
	comm->m_tickB = Rva007FEA00() - 5000;
}

/* The socket callback installer from the socket unit.  Its second argument is
 * a small INTEGER here -- 2 -- not a pointer, which is worth recording because
 * that unit's own name for the field it lands in reads like a callback. */
int Rva007FDE80( struct Rva007FD4E0Socket *socket, int mask, unsigned int rate,
	void *data,
	int ( __cdecl *proc )( unsigned int, int, struct Rva00816BF0Comm * ) );

/* 0x00819590 ADOPTS A SOCKET and starts connecting on it.
 *
 * THE CALLER GIVES UP THE SOCKET EITHER WAY.  If the transport is not idle the
 * body DESTROYS the socket it was handed and returns -2 -- it does not hand it
 * back -- so a caller must not keep using one it passed in, whatever the
 * return value.  That is the kind of ownership rule a signature cannot carry
 * and only the failure path shows.
 *
 * On the accepting path the old socket is detached first, the connection is
 * reset, the peer address is copied in, the new socket is attached, and the
 * global pump is installed as that socket's callback at a 100ms rate.  THAT
 * INSTALL IS THE PROOF that the pump's three unread parameters really are the
 * socket-callback signature: it is registered here as one.
 */
int Rva00819590( struct Rva00816BF0Comm *comm,
	struct Rva007FD4E0Socket *socket, const void *peer )
{
	if ( comm->m_state != 1 )
	{
		Rva007FD3F0( socket );
		return -2;
	}

	Rva00816DF0( comm, 0 );
	Rva00819260( comm );

	memcpy( comm->m_peer, peer, 0x10 );

	Rva00816DF0( comm, socket );
	Rva007FDE80( socket, 2, 0x64, 0, Rva00818CB0 );

	comm->m_state = 2;
	return 0;
}

int Rva007FDB60( struct Rva007FD4E0Socket *socket, int selector, void *buffer,
	int bufferLength );
int Rva007FDEE0( void );

extern char g_Rva012C4D48Message[];

/* 0x00818500 RECORDS BOTH ENDPOINTS, and it is the same body the ring
 * transport has at 0x00816160 -- same field offsets, same order, same 'bind'
 * query, differing only in which message it logs through.  Two transports with
 * two objects and one shared piece of code, duplicated rather than shared.
 *
 * As there, THE LOCAL ADDRESS DOES NOT COME FROM THE BIND QUERY.  A bound
 * socket's own address is usually 0.0.0.0, so the routing query at 0x007FDEE0
 * is used instead -- the body whose purpose was corrected once already, and
 * this is a second independent caller storing its result as a local address.
 */
void Rva00818500( struct Rva00816BF0Comm *comm, const unsigned char *from )
{
	char local[ 0x10 ];

	comm->m_peerAddress = ( ( ( ( from[ 4 ] << 8 ) | from[ 5 ] ) << 8 )
		| from[ 6 ] ) << 8 | from[ 7 ];
	comm->m_peerPort = (unsigned short)( ( from[ 2 ] << 8 ) | from[ 3 ] );

	Rva007FDB60( comm->m_socket, 'bind', local, 0x10 );

	comm->m_localAddress = Rva007FDEE0();
	comm->m_localPort = (unsigned short)
		( ( ( (unsigned char *)local )[ 2 ] << 8 )
		| ( (unsigned char *)local )[ 3 ] );

	Rva007FE780( g_Rva012C4D48Message, comm->m_peerAddress, comm->m_peerPort,
		comm->m_localAddress, comm->m_localPort );
}

/* A QUEUED SEND RECORD carries its sequence number at +0x08.  Only that field
 * is established here; the rest of the layout belongs to whatever builds these,
 * which is not in this file. */
struct Rva008186C0SendRecord
{
	int m_reserved0;
	int m_reserved4;
	unsigned int m_sequence;        /* +0x08 */
};

/* 0x00817640 is the address-derived send kick.  Its identity comes from the
 * two retransmit callers and the complete body shape, not from a surviving
 * diagnostic string. */
void Rva00817640( struct Rva00816BF0Comm *comm )
{
	int iOffset;
	int iCount;
	int iBudget;
	int iChunk;
	struct Rva00816F60Message packet;
	struct Rva00816F60Message *record;
	unsigned int uNextCode;

	iBudget = 0x800;
	iChunk = 0x200;
	iOffset = comm->m_sendReadOffset;

	for ( ; iOffset != comm->m_sendAckOffset;
		iOffset = ( iOffset + comm->m_sendRecordSize )
			% comm->m_sendBufferSize )
	{
		record = (struct Rva00816F60Message *)( comm->m_sendBuffer
			+ iOffset );
		iBudget = iBudget - record->m_length;
	}

	if ( iBudget < 0x100
		&& Rva007FEA00() - comm->m_tickA > 0xFA )
	{
		iBudget = 0x100;
	}

	while ( iBudget > 0 )
	{
		iChunk = 0x218;
		if ( iChunk > iBudget )
			iChunk = iBudget;

		iCount = 0;
		for ( ; iCount < 8 && iChunk > 0
			&& comm->m_sendAckOffset != comm->m_sendWriteOffset;
			++iCount )
		{
			record = (struct Rva00816F60Message *)( comm->m_sendBuffer
				+ comm->m_sendAckOffset );
			iChunk = iChunk - ( record->m_length + 1 );

			if ( iCount > 0 && iChunk <= 0 )
				break;

			comm->m_sendAckOffset = ( comm->m_sendAckOffset
				+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;

			if ( record->m_length > 0xFA )
			{
				++iCount;
				break;
			}
		}

		if ( iCount == 0 )
			break;

		iOffset = ( comm->m_sendAckOffset + comm->m_sendBufferSize
			- comm->m_sendRecordSize ) % comm->m_sendBufferSize;
		record = (struct Rva00816F60Message *)( comm->m_sendBuffer
			+ iOffset );
		memcpy( &packet, record, record->m_length + 0x10 );
		--iCount;

		for ( ; iCount > 0; --iCount )
		{
			iOffset = ( iOffset + comm->m_sendBufferSize
				- comm->m_sendRecordSize ) % comm->m_sendBufferSize;
			record = (struct Rva00816F60Message *)( comm->m_sendBuffer
				+ iOffset );

			if ( comm->m_sendProc != 0 )
				comm->m_sendProc( comm, record->m_body,
					record->m_length, 0 );

			packet.m_code += 0x10000000;
			memcpy( packet.m_body + packet.m_length, record->m_body,
				record->m_length );
			packet.m_length += record->m_length;
			packet.m_body[ packet.m_length ] =
				(unsigned char)record->m_length;
			++packet.m_length;
		}

		while ( iOffset != comm->m_sendReadOffset
			&& (unsigned int)packet.m_code <= g_Rva012C4DF4 )
		{
			iOffset = ( iOffset + comm->m_sendBufferSize
				- comm->m_sendRecordSize ) % comm->m_sendBufferSize;
			record = (struct Rva00816F60Message *)( comm->m_sendBuffer
				+ iOffset );

			if ( packet.m_length + record->m_length > 0x40 )
				break;

			if ( comm->m_sendProc != 0 )
				comm->m_sendProc( comm, record->m_body,
					record->m_length, 0 );

			packet.m_code += 0x10000000;
			memcpy( packet.m_body + packet.m_length, record->m_body,
				record->m_length );
			packet.m_length += record->m_length;
			packet.m_body[ packet.m_length ] =
				(unsigned char)record->m_length;
			++packet.m_length;
		}

		if ( iOffset == comm->m_sendReadOffset )
		{
			g_Rva012C4DF4 = 0x20000000;
		}
		else
		{
			if ( g_Rva012C4DF4 < 0x80000000 )
				uNextCode = g_Rva012C4DF4 << 1;
			else
				uNextCode = 0xF0000000;
			g_Rva012C4DF4 = uNextCode;
		}

		comm->m_reportedSequence = comm->m_recvSequence;
		packet.m_value = comm->m_reportedSequence - 1;
		if ( Rva00817030( comm, &packet ) < 0 )
			break;

		iBudget = iBudget - packet.m_length;
	}
}

/* 0x008186C0 IS THE ACKNOWLEDGEMENT HANDLER: it retires every queued send
 * whose sequence is at or below the one just acknowledged.
 *
 * THE ACKNOWLEDGED SEQUENCE IS OFF BY ONE FOR CODE 4 AND NOT FOR ANYTHING
 * ELSE.  A code-4 message means "I want sequence N next", so everything below
 * N is retired; any other code means "I have N", so N itself goes too.  That
 * single decrement is the whole difference between the two conventions, and
 * getting it backwards would retire one packet too many or too few every time.
 *
 * The comparison is UNSIGNED, so a sequence space that has wrapped past
 * 0x80000000 still retires correctly.
 *
 * Code 4 does one more thing: it snaps the transmit cursor back to the
 * acknowledgement cursor and kicks the sender.  That is a RETRANSMIT REQUEST
 * -- the peer is saying it wants N next, so everything from there on has to go
 * out again -- which is why the same message both retires and rewinds.
 *
 * The flag is computed once into a local with sete rather than tested twice;
 * both uses read that local.
 */
void Rva008186C0( struct Rva00816BF0Comm *comm,
	struct Rva00816F60Message *message )
{
	int bRewind;
	unsigned int uAcked;
	struct Rva008186C0SendRecord *record;
	int iAcked;

	bRewind = ( message->m_code == 4 );

	if ( bRewind )
		iAcked = message->m_value - 1;
	else
		iAcked = message->m_value;

	uAcked = iAcked;

	while ( comm->m_sendReadOffset != comm->m_sendWriteOffset )
	{
		record = (struct Rva008186C0SendRecord *)( comm->m_sendBuffer
			+ comm->m_sendReadOffset );

		if ( uAcked < record->m_sequence )
			break;

		if ( comm->m_sendAckOffset == comm->m_sendReadOffset )
		{
			comm->m_sendAckOffset = ( comm->m_sendAckOffset
				+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;
		}

		comm->m_sendReadOffset = ( comm->m_sendReadOffset
			+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;
	}

	if ( bRewind )
	{
		comm->m_sendAckOffset = comm->m_sendReadOffset;
		Rva00817640( comm );
	}
}

/* 0x00818AD0 IS THE IDLE DECISION: with nothing new to send, either retransmit
 * or acknowledge.
 *
 * If the send queue is non-empty AND the transmit cursor has caught up to the
 * write cursor -- everything queued has gone out and none of it has been
 * acknowledged -- it backs the transmit cursor up by ONE RECORD and kicks the
 * sender.  Backing up by subtracting the record size and taking the modulus,
 * rather than by comparing against the base, is what makes it wrap correctly
 * at the start of the ring.  So a stalled connection retransmits its most
 * recent packet rather than its oldest, which is the one an ack would be
 * answering.
 *
 * Otherwise it sends a bare message carrying its own sequence and the peer's
 * progress: code gets the send sequence, value gets the reported receive
 * sequence minus one.  The minus one is the same convention the ack handler
 * decodes -- "I want this next" rather than "I have this".
 *
 * The kind word is written LAST, after the two fields it describes, which is
 * retail's order and not the one a reader would write.
 */
void Rva00818AD0( struct Rva00816BF0Comm *comm )
{
	struct Rva00816F60Message message;

	if ( comm->m_sendReadOffset != comm->m_sendWriteOffset
		&& comm->m_sendAckOffset == comm->m_sendWriteOffset )
	{
		comm->m_sendAckOffset = ( comm->m_sendAckOffset
			+ comm->m_sendBufferSize - comm->m_sendRecordSize )
			% comm->m_sendBufferSize;

		Rva00817640( comm );
	}
	else
	{
		message.m_code = comm->m_sendSequence;
		comm->m_reportedSequence = comm->m_recvSequence;
		message.m_value = comm->m_reportedSequence - 1;
		message.m_length = 0;

		Rva00817030( comm, &message );
	}
}

/* The socket-address compare from the text unit: it compares only 6 bytes for
 * AF_INET, so two addresses agreeing on family, port and address compare equal
 * whatever their trailing bytes hold.  Returns 0 when they match. */
int Rva007FF720( const void *a, const void *b );

/* The bind wrapper from the socket unit. */
int Rva007FD510( struct Rva007FD4E0Socket *socket, const void *address,
	int addressLength );

/* 0x00819090 BINDS -- and it is where SOCKET SHARING COMES FROM.
 *
 * Before binding anything it walks the global transport list looking for
 * another transport already bound to the SAME ADDRESS, asking each one's
 * socket for its bound address and comparing.  If it finds one it takes that
 * transport's socket and DESTROYS THE ONE IT WAS HANDED, so two transports end
 * up sharing a socket.  That is exactly the situation the destructor's
 * shared-socket scan exists to handle, and this body is the only place it can
 * arise.
 *
 * The comparison ignores the trailing eight bytes of an AF_INET address, so
 * two binds agreeing on family, port and address share even if those bytes
 * differ.
 *
 * THE CALLER GIVES UP THE SOCKET ON EVERY PATH: destroyed if the transport is
 * not idle, destroyed if a shared one is found, destroyed if the bind fails,
 * adopted otherwise.  There is no path that hands it back.
 *
 * A FAILED BIND LEAVES THE STATE AT 0, which is not one of the five values any
 * other body uses -- 1 through 5 are the live ones.  So 0 means "construction
 * got as far as binding and failed", a state the object cannot otherwise
 * reach, and nothing here moves it out again.
 *
 * On success the state is 3 whether the socket was shared or freshly bound; a
 * bound listener is treated as established from the start.
 */
int Rva00819090( struct Rva00816BF0Comm *comm,
	struct Rva007FD4E0Socket *socket, const void *address )
{
	/* Declared scalars-first: retail's frame has the result nearest ebp, then
	 * the walk pointer, then the buffer. */
	int iResult;
	struct Rva00816BF0Comm *p;
	char local[ 0x10 ];

	if ( comm->m_state != 1 )
	{
		Rva007FD3F0( socket );
		return -2;
	}

	Rva00816DF0( comm, 0 );
	Rva00819260( comm );

	memset( local, 0, 0x10 );
	memset( comm->m_peer, 0, 0x10 );

	for ( p = g_Rva0130B188List; p != 0; p = p->m_next )
	{
		/* THE FIRST TWO TESTS SHARE ONE CONTINUE, joined by ||, and the bytes
		 * are specific about it: there is a SINGLE two-byte jump back to the
		 * increment, with the first test jumping TO it and the second falling
		 * INTO it.  Two separate continues would emit two such jumps, and an
		 * && wrapping the rest would send both operands past the whole body
		 * instead. */
		if ( p == comm || p->m_socket == 0 )
			continue;

		if ( Rva007FDB60( p->m_socket, 'bind', local, 0x10 ) < 0 )
			continue;

		if ( Rva007FF720( address, local ) == 0 )
		{
			Rva00816DF0( comm, p->m_socket );
			Rva007FD3F0( socket );
			break;
		}
	}

	if ( p == 0 )
	{
		iResult = Rva007FD510( socket, address, 0x10 );

		if ( iResult < 0 )
		{
			comm->m_state = 0;
			Rva007FD3F0( socket );
			return -5;
		}

		Rva00816DF0( comm, socket );
		Rva007FDE80( socket, 2, 0x64, 0, Rva00818CB0 );
	}

	comm->m_state = 3;
	return 0;
}

extern char g_Rva012C4DF8Message[];

/* 0x008187E0 ACCEPTS A RECEIVED RECORD into the receive queue, and it is where
 * the sequence discipline actually lives.
 *
 * A FULL QUEUE IS DETECTED BEFORE ANYTHING ELSE, by advancing the write cursor
 * one record and seeing whether it would land on the read cursor -- so one
 * record's worth of the ring is always left empty and the two cursors never
 * mean "full" and "empty" at the same time.
 *
 * CODE 6 IS UNSEQUENCED and takes a different path: rather than being checked
 * against the expected sequence it is admitted only while more than four
 * records are free, so a flood of them cannot fill the queue and starve
 * sequenced traffic.  It also does not advance the sequence or the byte
 * counter on the way in.
 *
 * Everything else is sequenced, and the three outcomes are the protocol:
 *   - BELOW the expected sequence is a duplicate and is dropped silently;
 *   - ABOVE it means something was missed, and the incoming record is
 *     REWRITTEN IN PLACE into a code-4 retransmit request naming the sequence
 *     actually wanted and sent straight back.  Reusing the caller's buffer
 *     rather than building a message is why this returns -1: the record it was
 *     handed no longer holds what arrived.
 *   - equal, but empty, is a pure acknowledgement and is dropped.
 *
 * The callback is invoked with the payload from +0x10, and the depth counter
 * is raised before the copy and lowered after the callback returns -- so it
 * spans the one window in which a caller could re-enter.
 */
int Rva008187E0( struct Rva00816BF0Comm *comm,
	struct Rva00816F60Message *record )
{
	struct Rva00816F60Message *slot;
	int iUsed;
	int iFree;

	if ( ( comm->m_recvWriteOffset + comm->m_recvRecordSize )
		% comm->m_recvBufferSize == comm->m_recvReadOffset )
	{
		Rva007FE780( g_Rva012C4DF8Message );
		return 2;
	}

	if ( record->m_code == 6 )
	{
		iUsed = ( comm->m_recvWriteOffset + comm->m_recvBufferSize
			- comm->m_recvReadOffset ) % comm->m_recvBufferSize;

		iFree = ( comm->m_recvBufferSize - iUsed ) / comm->m_recvRecordSize;

		if ( iFree <= 4 )
			return 2;
	}
	else
	{
		if ( (unsigned int)record->m_code < (unsigned int)comm->m_recvSequence )
			return 0;

		if ( (unsigned int)record->m_code > (unsigned int)comm->m_recvSequence )
		{
			record->m_code = 4;
			record->m_value = comm->m_recvSequence;
			record->m_length = 0;

			Rva00817030( comm, record );
			return -1;
		}

		if ( record->m_length == 0 )
			return 0;
	}

	slot = (struct Rva00816F60Message *)( comm->m_recvBuffer
		+ comm->m_recvWriteOffset );

	memcpy( slot, record, comm->m_recvRecordSize );

	comm->m_depth = comm->m_depth + 1;

	comm->m_recvWriteOffset = ( comm->m_recvWriteOffset
		+ comm->m_recvRecordSize ) % comm->m_recvBufferSize;

	if ( record->m_code != 6 )
	{
		comm->m_recvSequence = comm->m_recvSequence + 1;
		comm->m_recvCounter = comm->m_recvCounter + slot->m_length;
	}

	comm->m_flags = comm->m_flags | 1;

	if ( comm->m_receiveProc != 0 )
	{
		comm->m_receiveProc( comm, (char *)slot + 0x10, slot->m_length,
			slot->m_tick );
	}

	comm->m_depth = comm->m_depth - 1;
	return 1;
}
