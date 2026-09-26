// cl: /Od /GZ /GS /MD /DNDEBUG
/* /GS is needed for 0x008155F0, whose local packet contains an array and so
 * carries a cookie.  It costs the other bodies here nothing: /GS only emits
 * a cookie in a function that HAS a local array, and none of them do. */
/* EA DirtySock -- the idle pump for a RING-BUFFERED comm transport.
 *
 * PLACEMENT IS BY ADDRESS NEIGHBOURHOOD ONLY, and is stated rather than
 * implied: these bodies sit inside the span commsrp.cpp already occupies, but
 * they cannot be part of that translation unit, because they are built /Od
 * with /GZ -- local fills of 0xCCCCCCCC and a stack check after every call --
 * and commsrp.cpp is optimised.  Two translation units interleaved in one
 * address range is ordinary; sharing a file with one that has different flags
 * is not possible.  Neither body reaches a string, so nothing here names the
 * module and the file name is address-derived like the symbols.
 *
 * WHAT THE FIELDS ARE, read from the arithmetic rather than assumed.  The two
 * bodies together use +0xB0, +0xB4, +0xB8 and +0xBC as a ring: an offset is
 * advanced by +0xB0 and reduced modulo +0xB4, so +0xB0 is a RECORD SIZE and
 * +0xB4 the buffer size in bytes; the backlog is computed as the distance from
 * +0xBC to +0xB8 taken modulo the buffer size and then DIVIDED BY THE RECORD
 * SIZE, which is what makes the result a count of records rather than bytes.
 * +0xBC is therefore the read cursor and +0xB8 the write cursor.  All the
 * divides are idiv, so every one of these is a signed int.
 */

/* The recursive lock helpers this library uses everywhere; the acquire is a
 * TRY, returning zero when the lock is held elsewhere. */
int Rva007FEB00( void *lock );
void Rva007FECB0( void *lock );

struct Rva00815B50Comm
{
	char m_head[ 0x48 ];
	struct Rva007FD4E0Socket *m_socketAlias; /* +0x48 */
	char m_gapHead[ 0x10 ];
	/* Byte and packet counters, both incremented by the send at 0x00815680
	 * and by nothing else here. */
	int m_bytesSent;                /* +0x5C */
	char m_gap0[ 0x04 ];
	int m_packetsSent;              /* +0x64 */
	char m_gap1[ 0x04 ];
	/* The four endpoint fields, all written by 0x00816160 and in this order:
	 * local address, peer address, local port, peer port.  The two ports are
	 * SHORTS -- both are stored with a 16-bit mov and read back with movzx --
	 * while the addresses are full words. */
	unsigned int m_localAddress;    /* +0x6C */
	unsigned int m_peerAddress;     /* +0x70 */
	unsigned short m_localPort;     /* +0x74 */
	unsigned short m_peerPort;      /* +0x76 */
	char m_gap1b[ 0x04 ];
	/* A POINTER TO THE SOCKET OBJECT, not a raw handle: 0x00816160 passes this
	 * field straight to SocketInfo, whose first parameter is the object.  The
	 * send path passes it the same way.  Both spellings are four bytes and
	 * compile identically, so only a caller that dereferences it could tell,
	 * and this is that caller. */
	struct Rva007FD4E0Socket *m_socket;     /* +0x7C */
	/* The PEER ADDRESS.  The send hands this to sendto with a length of 0x10,
	 * which is what fixes both its position and its size. */
	char m_peer[ 0x10 ];            /* +0x80 */
	/* THE CONNECTION STATE.  The handshake at 0x00816020 is what gives this
	 * field its meaning: it is tested against 1, 2 and 3 and driven to 3 and
	 * then 4, and every transition is gated on the state the peer's packet
	 * type implies.  1 and 2 are the two halves of an unfinished connect, 3 is
	 * established, 4 is closing. */
	int m_state;                    /* +0x90 */
	int m_sessionValue;             /* +0x94 */
	/* THE RECEIVE QUEUE.  The dequeue at 0x00816520 compares +0xA8 against
	 * +0xA4 to decide whether anything is waiting and reads the record at
	 * +0xAC plus +0xA8, which is what identifies the base and the two
	 * cursors; 0x008165F0 advances +0xA8 by +0x98 modulo +0xA0 after a
	 * successful read. */
	int m_recvRecordSize;           /* +0x98 */
	char m_gapB[ 0x04 ];
	int m_recvBufferSize;           /* +0xA0 */
	int m_recvWriteOffset;          /* +0xA4 */
	int m_recvReadOffset;           /* +0xA8 */
	unsigned char *m_recvBuffer;    /* +0xAC */
	/* THE SEND QUEUE, same five fields one ring further on.  The retransmit
	 * timer walks THIS one and hands its records to the send, and the ack
	 * handler at 0x00815FA0 retires from it -- which is what tells the two
	 * queues apart, since their shapes are identical. */
	int m_sendRecordSize;           /* +0xB0 */
	int m_sendBufferSize;           /* +0xB4 */
	int m_sendWriteOffset;          /* +0xB8 */
	int m_sendReadOffset;           /* +0xBC */
	unsigned char *m_sendBuffer;    /* +0xC0 */
	unsigned int m_lastSendTick;    /* +0xC4 */
	unsigned int m_lastRecvTick;    /* +0xC8 */
	char m_gap2[ 0x120 ];
	char m_lock[ 4 ];               /* +0x1EC */
	char m_gap1F0[ 0x24 ];
	int m_flags;                    /* +0x214 */
	void *m_value;                  /* +0x218 */
};

void Rva007FD3F0( struct Rva007FD4E0Socket *socket );

void Rva008154F0( struct Rva00815B50Comm *comm,
	struct Rva007FD4E0Socket *socket )
{
	comm->m_socket = socket;
	comm->m_socketAlias = socket;
}

void Rva00815730( struct Rva00815B50Comm *comm, void *value )
{
	comm->m_value = value;
	comm->m_flags |= 2;
}

int Rva00815790( struct Rva00815B50Comm *comm )
{
	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008154F0( comm, 0 );
	}
	comm->m_state = 0;
	return 0;
}

int Rva008157E0( struct Rva00815B50Comm *comm )
{
	if ( comm->m_socket != 0 )
	{
		Rva007FD3F0( comm->m_socket );
		Rva008154F0( comm, 0 );
	}
	comm->m_state = 0;
	return 0;
}

void Rva00815BB0( struct Rva00815B50Comm *comm );

/* The socket callback.  Its first two arguments -- the handle and the event
 * flags -- are IGNORED; only the ref is used, which is the shape DirtySock
 * installs everywhere.  The lock is TRIED rather than taken, so a callback
 * arriving while the transport is busy is dropped rather than queued.
 */
int Rva00815B50( unsigned int socket, int flags, struct Rva00815B50Comm *ref )
{
	struct Rva00815B50Comm *comm;

	comm = ref;

	if ( Rva007FEB00( comm->m_lock ) != 0 )
	{
		Rva00815BB0( comm );
		Rva007FECB0( comm->m_lock );
	}

	return 0;
}

/* Advance the write cursor by one record, pump the transport through its own
 * callback, and report how many records are outstanding.
 *
 * THE OUT-PARAMETER IS CLEARED AND NEVER WRITTEN AGAIN in this body, so a
 * caller always sees zero from it here; whatever it is for is filled in
 * elsewhere or not at all.  That is retail's, and it is the kind of thing a
 * reader would otherwise assume was an oversight in the conversion.
 *
 * The pump is invoked by CALLING THE CALLBACK DIRECTLY rather than by waiting
 * for the socket to fire it -- same function, same arguments the socket layer
 * would pass, with the handle taken out of the object.
 */
int Rva00815AB0( struct Rva00815B50Comm *comm, int *out )
{
	int iResult;

	*out = 0;

	comm->m_sendWriteOffset = ( comm->m_sendWriteOffset + comm->m_sendRecordSize )
		% comm->m_sendBufferSize;

	Rva00815B50( comm->m_socket, 0, comm );

	iResult = ( ( comm->m_sendWriteOffset + comm->m_sendBufferSize
		- comm->m_sendReadOffset ) % comm->m_sendBufferSize ) / comm->m_sendRecordSize;

	return iResult;
}

/* 0x00815FA0 RETIRES ONE RECORD, but only if the acknowledgement matches.
 *
 * It reads a sequence byte from the incoming packet and one from the record
 * currently at the read cursor, and advances the cursor only when they agree.
 * THE TWO BYTES ARE BIASED DIFFERENTLY -- 0xC0 is subtracted from the packet's
 * and 0x80 from the stored one -- so the two sides carry the same sequence
 * number in different tag spaces, and the constants are what say so.  Reading
 * either byte alone would tell you nothing.
 *
 * A mismatch is silently ignored: no error, no counter, no retransmit here.
 * The record simply stays at the cursor.
 *
 * Both bytes are read with movzx, so the tags are unsigned; the biased results
 * are then compared as ints, which is why an unexpected tag cannot wrap into
 * a false match.
 */
void Rva00815FA0( struct Rva00815B50Comm *comm, const unsigned char *packet )
{
	int iPacketTag;
	int iRecordTag;
	unsigned char *pRecord;

	pRecord = comm->m_sendBuffer + comm->m_sendReadOffset;

	iPacketTag = packet[ 8 ] - 0xC0;
	iRecordTag = pRecord[ 8 ] - 0x80;

	if ( iPacketTag == iRecordTag )
	{
		comm->m_sendReadOffset = ( comm->m_sendReadOffset + comm->m_sendRecordSize )
			% comm->m_sendBufferSize;
	}
}

/* The wire packet.  Twelve bytes, and the builder at 0x008155F0 leaves the
 * FIRST FOUR UNINITIALISED -- only the length and the leading data byte are
 * set -- so whatever +0x00 is, it is not part of what gets transmitted.
 */
struct Rva00815680Packet
{
	/* THE RETRANSMIT TIMESTAMP.  The builder at 0x008155F0 leaves this alone,
	 * which is why it first read as unused; the retransmit timer at
	 * 0x00816490 is what gives it meaning -- it stamps this field after every
	 * successful send and compares against it to decide when to send again.
	 * Zero means "never sent", which is why a fresh record goes out at once. */
	unsigned int m_sendTick;        /* +0x00 */
	int m_length;                   /* +0x04 */
	unsigned char m_data[ 4 ];      /* +0x08 */
};

struct Rva007FD4E0Socket;

int Rva007FD920( struct Rva007FD4E0Socket *socket, const char *buffer,
	int length, int flags, void *to, int toLength );
int Rva007FE780( const char *format, ... );

extern char g_Rva012C4B64Message[];

/* 0x00815680 SENDS ONE PACKET.  The length on the wire is the payload length
 * PLUS ONE, and the buffer starts at +0x08 -- so the leading data byte is a
 * header the payload length does not count.  That off-by-one is deliberate and
 * is the only thing distinguishing the two.
 *
 * A SHORT WRITE IS TREATED AS A HARD FAILURE, not a partial send: the sent
 * count is compared for EQUALITY against the requested length, and anything
 * else is reported and returns -1.  Nothing retries the remainder, so this
 * transport assumes a datagram socket where a send is all-or-nothing.
 *
 * On success three pieces of state move together -- the last-send tick, the
 * byte counter and the packet counter -- and the tick is read AFTER the send
 * returns, so it records completion rather than submission.
 */
int Rva00815680( struct Rva00815B50Comm *comm, struct Rva00815680Packet *packet )
{
	/* Declared in this order because retail's frame has the length nearest
	 * ebp; swapping them compiles cleanly and matches nothing. */
	int iLength;
	int iSent;

	iLength = 1;
	iLength = iLength + packet->m_length;

	iSent = Rva007FD920( comm->m_socket, (const char *)packet->m_data,
		iLength, 0, comm->m_peer, 0x10 );

	if ( iSent != iLength )
	{
		Rva007FE780( g_Rva012C4B64Message, iSent );
		return -1;
	}

	comm->m_lastSendTick = Rva007FEA00();
	comm->m_bytesSent = comm->m_bytesSent + iLength;
	comm->m_packetsSent = comm->m_packetsSent + 1;

	return iLength;
}

/* 0x008155F0 sends a ONE-BYTE control packet: payload length zero, the kind
 * byte in the first data slot.  The packet is a local, and it is the local
 * ARRAY that pulls in the /GS cookie this body carries and the neighbouring
 * ones do not.
 */
unsigned int Rva007FEA00( void );

int Rva008155F0( struct Rva00815B50Comm *comm, char kind )
{
	struct Rva00815680Packet packet;

	packet.m_length = 0;
	packet.m_data[ 0 ] = kind;

	return Rva00815680( comm, &packet );
}

int Rva008155A0( struct Rva00815B50Comm *comm )
{
	if ( comm->m_state != 3 )
	{
		return 0;
	}

	Rva008155F0( comm, 0x14 );
	comm->m_sessionValue = 0;
	comm->m_state = 4;
	return 0;
}

void *__cdecl memcpy( void *destination, const void *source,
	unsigned int count );

void Rva00816160( struct Rva00815B50Comm *comm, const void *from );

extern char g_Rva012C4B98Message[];
extern char g_Rva012C4B38Message[];

/* 0x00816020 is the CONTROL-PACKET HANDLER -- the connection handshake.  The
 * packet's first data byte selects the action, and the five recognised values
 * are 0x10..0x14.
 *
 * EVERY CASE GUARDS ITS ACTION AND THEN BREAKS UNCONDITIONALLY -- the guard's
 * failure jumps to that case's OWN break, not into the next one.  A packet
 * arriving in an unexpected state is therefore dropped silently rather than
 * re-offered to another handler.  Reading the guards as wrapping the break
 * instead produces a fallthrough chain that compiles cleanly, is two bytes
 * off per case, and describes behaviour the transport does not have.
 *
 * The first thing the body does, before it has looked at anything, is stamp
 * +0xC8 with the current tick MINUS ONE SECOND.  Backdating rather than
 * stamping "now" makes the next timeout comparison behave as though the last
 * activity were already a second old, which is what keeps a handshake moving
 * instead of resetting its own timer.
 *
 * An unrecognised type is reported and otherwise ignored.
 */
void Rva00816020( struct Rva00815B50Comm *comm,
	struct Rva00815680Packet *packet, const void *from )
{
	comm->m_lastRecvTick = Rva007FEA00() - 1000;

	/* THE SUBTRACTION OF 0x10 IN THE BYTES IS THE COMPILER'S, NOT THE
	 * SOURCE'S.  MSVC normalises a switch whose cases start at 0x10 by
	 * storing the value into its single temporary, subtracting the base in
	 * place, and bounds-checking the result -- which is exactly the
	 * store/reload/sub/store the bytes show, in ONE stack slot.  Writing the
	 * subtraction out as a statement costs a second slot and a copy; folding
	 * it into the switch expression loses the reload.  Neither matches. */
	switch ( packet->m_data[ 0 ] )
	{
	case 0x10:
		/* THE REPLY IS UNCONDITIONAL; only the state change is guarded.  The
		 * jne skips the three statements above the send and lands ON it, so a
		 * connect request is always answered with a 0x12 whatever state we
		 * are in -- and only a peer we were actually expecting advances us to
		 * established.  Putting the send inside the if compiles to a jump 19
		 * bytes further along and is how this body was first read wrong. */
		if ( comm->m_state == 2 )
		{
			memcpy( comm->m_peer, from, 0x10 );
			Rva00816160( comm, from );
			comm->m_state = 3;
		}
		Rva008155F0( comm, 0x12 );
		break;

	case 0x11:
		if ( comm->m_state == 1 )
			memcpy( comm->m_peer, from, 0x10 );
		break;

	case 0x12:
		if ( comm->m_state == 1 )
		{
			Rva00816160( comm, from );
			comm->m_state = 3;
		}
		break;

	case 0x13:
		if ( comm->m_state == 3 )
			comm->m_state = 4;
		break;

	case 0x14:
		break;

	default:
		Rva007FE780( g_Rva012C4B98Message, packet->m_data[ 0 ] );
		break;
	}
}

/* 0x00816160 COMPLETES A CONNECTION by recording both endpoints.
 *
 * The peer's address and port come out of the sockaddr the packet arrived
 * from, big-endian at +4..+7 and +2..+3 as everywhere else in this library.
 * The local port comes from a 'bind' SocketInfo query -- the same
 * four-character selector the socket layer dispatches on.
 *
 * THE LOCAL ADDRESS DOES NOT COME FROM THAT QUERY.  A bound socket's own
 * address is usually 0.0.0.0, which is useless to report, so the body calls
 * 0x007FDEE0 instead -- the routing query that asks which interface would be
 * used to reach an outside address and returns that.  It is why that body
 * exists, and it is what corrects its earlier reading as a self test.
 *
 * Everything is then logged in one call, peer first and local second.
 */
int Rva007FDB60( struct Rva007FD4E0Socket *socket, int selector, void *buffer,
	int bufferLength );
int Rva007FDEE0( void );

void Rva00816160( struct Rva00815B50Comm *comm, const unsigned char *from )
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

	Rva007FE780( g_Rva012C4B38Message, comm->m_peerAddress, comm->m_peerPort,
		comm->m_localAddress, comm->m_localPort );
}

/* 0x00816490 is the RETRANSMIT TIMER, and it is what gives the packet's +0x00
 * field its meaning.
 *
 * It looks only at the record at the read cursor -- the oldest unacknowledged
 * one -- and only while the connection is established and the queue is
 * non-empty.  A record whose stamp is ZERO has never been sent and goes out
 * immediately; otherwise it waits until 250 milliseconds have passed.  The
 * elapsed comparison is `jb`, i.e. UNSIGNED, so it survives a tick rollover.
 *
 * THE STAMP IS ONLY UPDATED IF THE SEND SUCCEEDS.  A failed send leaves the
 * old stamp in place, so the next tick retries immediately rather than waiting
 * another 250 milliseconds -- and a never-sent record whose first send fails
 * keeps its zero and stays eligible.  Moving the stamp outside the success
 * test would silently turn a failure into a quarter-second stall.
 *
 * Only the head of the queue is ever retransmitted; nothing here walks past
 * it.
 */
void Rva00816490( struct Rva00815B50Comm *comm )
{
	struct Rva00815680Packet *packet;

	/* The two guards WRAP the body rather than returning early.  Retail has a
	 * single conditional jump for each; an early return compiles to a short
	 * jump over an unconditional one, which is two instructions where retail
	 * has one. */
	if ( comm->m_state == 3 && comm->m_sendWriteOffset != comm->m_sendReadOffset )
	{
		packet = (struct Rva00815680Packet *)( comm->m_sendBuffer
			+ comm->m_sendReadOffset );

		if ( packet->m_sendTick == 0
			|| Rva007FEA00() - packet->m_sendTick >= 250 )
		{
			/* THE SEND FAILURE IS AN EARLY RETURN, not another && term.  It
			 * compiles to `jge` over a `jmp`, where folding it into the
			 * condition above gives a single `jl`.  The styles really are
			 * mixed in this body: wrapping ifs for the outer guards, a
			 * short-circuit || for the timer, an early return here. */
			if ( Rva00815680( comm, packet ) < 0 )
				return;

			packet->m_sendTick = Rva007FEA00();
		}
	}
}

/* 0x008165F0 is the outbound-ring counterpart of 0x00814F70 in the other
 * transport: forward to the dequeue and advance the RECEIVE read cursor only
 * when it reports success, so a failed read leaves the record in place.
 */
int Rva008165F0( struct Rva00815B50Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	int iResult;

	iResult = Rva00816520( comm, buffer, size, when );

	if ( iResult >= 0 )
	{
		comm->m_recvReadOffset = ( comm->m_recvReadOffset + comm->m_recvRecordSize )
			% comm->m_recvBufferSize;
	}

	return iResult;
}

/* 0x00816520 DEQUEUES ONE RECEIVED RECORD.
 *
 * It pumps the transport first, but ONLY IF THE QUEUE LOOKS EMPTY -- and then
 * re-tests, so a pump that produced nothing still returns -7 rather than
 * reading a stale slot.  That double test is not redundant: the pump is what
 * fills the queue.
 *
 * The length it reports is the stored record length MINUS ONE, the inverse of
 * the plus-one the send applies, and the payload it copies starts at +9 rather
 * than +8 -- both skip the same one-byte header.
 *
 * THE COPY IS CLAMPED BUT THE RETURN IS NOT.  A caller passing a buffer
 * smaller than the record gets a truncated copy and the FULL length back, so
 * the return value is "how big it was", not "how much you got"; comparing them
 * is the only way to detect truncation.  Nothing here reports it otherwise.
 *
 * The optional out-parameter receives the record's +0x00 word.  In the send
 * queue that field is the retransmit stamp; here it is the arrival stamp the
 * receive path wrote.  Same offset, different meaning per queue.
 */
int Rva00816520( struct Rva00815B50Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	struct Rva00815680Packet *packet;
	int iLength;
	int iCopy;

	if ( comm->m_recvReadOffset == comm->m_recvWriteOffset )
		Rva00815B50( 0, 0, comm );

	if ( comm->m_recvReadOffset == comm->m_recvWriteOffset )
		return -7;

	packet = (struct Rva00815680Packet *)( comm->m_recvBuffer
		+ comm->m_recvReadOffset );

	iLength = packet->m_length - 1;

	if ( iLength < size )
		iCopy = iLength;
	else
		iCopy = size;

	memcpy( buffer, (char *)packet + 9, iCopy );

	if ( when != 0 )
		*when = packet->m_sendTick;

	return iLength;
}
