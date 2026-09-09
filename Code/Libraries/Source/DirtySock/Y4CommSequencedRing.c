// cl: /Od /GZ /GS /MD /DNDEBUG
/* EA DirtySock -- a fourth /Od /GZ comm object, past the range the three
 * already converted occupy.  Its ring sits at +0xD4..+0xE0, where the others
 * are at +0x98, +0xB0 and +0xB8, so it is a distinct object again; nothing
 * here identifies the module, and both bodies are placed by address
 * neighbourhood.
 *
 * Only the fields these two bodies actually touch are declared.  The gaps are
 * left as gaps rather than filled with plausible names.
 */

struct Rva0081BD40Comm
{
	char m_head[ 0x38 ];
	/* THE SEND CALLBACK, called by 0x0081A8C0 just before each record goes out
	 * with the transport, the payload, its length and a zero.  Null means
	 * nobody is watching; it does not stop the send. */
	void ( __cdecl *m_sendProc )( struct Rva0081BD40Comm *comm,
		const void *payload, int length, int reserved );  /* +0x38 */
	/* THE RECEIVE CALLBACK, called by 0x0081AB40 with the transport, the
	 * payload, its length and its arrival tick -- the send one beside it gets
	 * a zero in that last slot instead. */
	void ( __cdecl *m_recvProc )( struct Rva0081BD40Comm *comm,
		const void *payload, int length, unsigned int tick );  /* +0x3C */
	char m_head2a[ 0x3C ];
	void *m_handle;                 /* +0x7C */
	char m_head2b[ 0x28 ];
	char m_streamOverlapped[ 0x10 ]; /* +0xA8 */
	void *m_event;                  /* +0xB8 */
	char m_head2d[ 0x08 ];
	unsigned int m_streamWritten;   /* +0xC4 */
	char m_head2c[ 0x04 ];
	/* A STATE.  0x0081B790 and 0x0081B910 both require it to be 1 before
	 * doing anything, and both convert a 5 into their own result -- 3 and 2
	 * respectively.  Nothing converted so far shows what sets it to 5. */
	int m_state;                    /* +0xCC */
	int m_pendingValue;             /* +0xD0, sent by the state transition */
	int m_recvRecordSize;               /* +0xD4 */
	int m_recvBufferSize;               /* +0xD8 */
	int m_recvWriteOffset;              /* +0xDC */
	int m_recvReadOffset;               /* +0xE0 */
	unsigned char *m_recvBuffer;        /* +0xE4 */
	/* THE EXPECTED RECEIVE SEQUENCE.  0x0081A8C0 stamps one less than this
	 * into every outgoing record's ack field, which is the "I want N next"
	 * convention the acknowledgement handler above decodes. */
	int m_recvSequence;             /* +0xE8 */
	/* THE SEND RING, the same five fields plus an ack cursor that the third
	 * transport has at +0xB0..+0xC8.  0x0081AA20 is the same acknowledgement
	 * handler that transport has at 0x008186C0, walking these instead. */
	int m_sendRecordSize;           /* +0xEC */
	int m_sendBufferSize;           /* +0xF0 */
	int m_sendWriteOffset;          /* +0xF4 */
	int m_sendReadOffset;           /* +0xF8 */
	int m_sendAckOffset;            /* +0xFC */
	unsigned char *m_sendBuffer;    /* +0x100 */
	/* THE NEXT SEND SEQUENCE.  0x0081BA60 stamps it into each queued record
	 * and then increments it, so it is the counter the acknowledgement
	 * handler's comparisons are against. */
	unsigned int m_sendSequence;    /* +0x104 */
	char m_gap[ 0x0804 ];
	unsigned char m_streamBuffers[ 2 ][ 0x800 ]; /* +0x90C */
	int m_streamCapacity;          /* +0x190C */
	int m_streamLength;            /* +0x1910 */
	int m_streamSlot;              /* +0x1914 */
	unsigned int m_streamTick;     /* +0x1918 */
	char m_streamGap[ 0x04 ];      /* +0x191C */
	/* A CRITICAL SECTION, and its SIZE is the evidence: the two bodies that
	 * take it pass +0x1920 to a pair of one-argument stdcall imports, and the
	 * busy flag below starts exactly 0x18 bytes later -- which is sizeof
	 * CRITICAL_SECTION on x86.  The import names never reach the bytes, so
	 * the declarations below are address-derived. */
	char m_lock[ 0x18 ];            /* +0x1920 */
	/* A RE-ENTRANCY DEPTH, and the two bodies that touch it say different
	 * halves of the story.  0x0081AB40 raises it across the copy and the user
	 * callback and lowers it after; 0x0081BC80 SPINS WHILE IT IS NON-ZERO.  So
	 * a reader does not wait on a lock, it waits for a delivery in progress to
	 * finish -- which is why the dequeue has no timeout and needs none. */
	int m_depth;                    /* +0x1938 */
	int m_flags;                    /* +0x193C */
};

/* The one-argument stdcall import the socket unit already reaches with a 50
 * for a poll interval; here it is called with zero, which is a yield rather
 * than a wait.  The name is address-derived: an IAT call site is a DIR32 and
 * the gate fills it from retail, so nothing here asserts which API it is. */
__declspec(dllimport) void __stdcall Rva01358F30Wait( int interval );
__declspec(dllimport) unsigned int __stdcall Rva01358E0CTick( void );
__declspec(dllimport) int __stdcall Rva01358EDC( void *handle,
	unsigned int mask );
__declspec(dllimport) unsigned int __stdcall Rva01358F64Wait( void *handle,
	unsigned int timeout );
__declspec(dllimport) int __stdcall Rva01358F70Write( void *handle,
	const void *buffer, unsigned int length, unsigned int *written,
	void *overlapped );

/* A QUEUED RECORD.  Length at +0x00, tick at +0x04, payload at +0x10 -- the
 * same header the third transport uses, and again with no header byte inside
 * the payload. */
struct Rva0081BC80Record
{
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04 */
	char m_reserved[ 0x08 ];
	unsigned char m_data[ 4 ];      /* +0x10 */
};

/* 0x0081A360 is a 16-BIT HASH, and every part of that is in the bytes: the
 * accumulator is written and read back as a WORD, the multiply is by 13, and
 * the result is returned in ax rather than eax -- so the caller gets
 * 0x0000..0xFFFF and the upper half of the register is not part of the answer.
 *
 * The input byte is read with movzx, so the data is unsigned; the length is
 * compared with `jle`, so it is SIGNED and a negative length hashes nothing
 * rather than running away.
 *
 * Both parameters are walked in place rather than through locals, which is
 * why the frame holds only the accumulator.
 */
unsigned short Rva0081A360( const unsigned char *data, int length )
{
	unsigned short uHash;

	uHash = 0;

	while ( length > 0 )
	{
		uHash = (unsigned short)( uHash * 13 + *data );
		data++;
		length--;
	}

	return uHash;
}

/* 0x0081BD40 forwards four arguments and advances the ring cursor only when
 * the inner call reports success, so a failure leaves the slot to be retried.
 * The same shape appears once per transport in this library; this is the
 * fourth.
 */
/* Settled by converting it: a buffer, a size and an optional out-pointer. */
int Rva0081BC80( struct Rva0081BD40Comm *comm, void *buffer, int size,
	unsigned int *when );

int Rva0081BD40( struct Rva0081BD40Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	int iResult;

	iResult = Rva0081BC80( comm, buffer, size, when );

	if ( iResult >= 0 )
		comm->m_recvReadOffset = ( comm->m_recvReadOffset + comm->m_recvRecordSize )
			% comm->m_recvBufferSize;

	return iResult;
}

void *__cdecl memcpy( void *destination, const void *source,
	unsigned int count );

/* 0x0081BC80 DEQUEUES ONE RECORD, and it is the only one of these four that
 * BLOCKS.
 *
 * After finding the queue non-empty it spins while a flag at +0x1938 is set,
 * yielding the timeslice on each pass rather than sleeping for an interval --
 * the same import the socket unit calls with 50, called here with zero.  So a
 * reader can be held off indefinitely by whoever owns that flag, with no
 * timeout and no failure return for it; the only exits are an empty queue and
 * a successful read.
 *
 * Note the order: EMPTINESS IS TESTED BEFORE THE SPIN.  An empty queue returns
 * -7 immediately rather than waiting for a writer, so this blocks on the flag
 * and not on data.
 *
 * The rest matches its counterparts: the copy is clamped to the caller's size
 * while the RETURN IS THE FULL RECORD LENGTH, so comparing the two is the only
 * way to detect truncation, and the optional out-pointer receives the arrival
 * tick.
 */
int Rva0081BC80( struct Rva0081BD40Comm *comm, void *buffer, int size,
	unsigned int *when )
{
	struct Rva0081BC80Record *record;
	int iCopy;

	if ( comm->m_recvReadOffset == comm->m_recvWriteOffset )
		return -7;

	while ( comm->m_depth != 0 )
		Rva01358F30Wait( 0 );

	record = (struct Rva0081BC80Record *)( comm->m_recvBuffer
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

__declspec(dllimport) void __stdcall Rva01358D18Enter( void *lock );
__declspec(dllimport) void __stdcall Rva01358E74Leave( void *lock );

int Rva0081B010( struct Rva0081BD40Comm *comm, void *argument );

/* 0x0081B790 and 0x0081B910 ARE THE SAME BODY BUT FOR ONE CONSTANT: both
 * refuse unless the argument is non-null and the state is 1, both take the
 * critical section, both call the same worker, and both convert a state of 5
 * into their own -- 3 for the first, 2 for the second -- before releasing.
 *
 * The pair is what makes 5 legible as a TRANSIENT the worker can leave behind:
 * neither body sets it, both check for it, and each replaces it with a
 * different settled value.  So the worker signals "decide what I became" and
 * the caller's identity is what decides.  Either body alone would just look
 * like an unexplained magic number.
 *
 * The refusal is an early return with an ||, which is legible in the jumps: a
 * null argument jumps straight to the return, while a state of 1 jumps PAST
 * it.  An && wrapping the body sends both operands to the same place instead.
 *
 * The worker's result is returned unchanged, and it is captured BEFORE the
 * state fixup -- so the fixup cannot affect what the caller sees.
 */
int Rva0081B790( struct Rva0081BD40Comm *comm, void *argument )
{
	int iResult;

	if ( argument == 0 || comm->m_state != 1 )
		return -2;

	Rva01358D18Enter( comm->m_lock );

	iResult = Rva0081B010( comm, argument );

	if ( comm->m_state == 5 )
		comm->m_state = 3;

	Rva01358E74Leave( comm->m_lock );
	return iResult;
}

int Rva0081B910( struct Rva0081BD40Comm *comm, void *argument )
{
	int iResult;

	if ( argument == 0 || comm->m_state != 1 )
		return -2;

	Rva01358D18Enter( comm->m_lock );

	iResult = Rva0081B010( comm, argument );

	if ( comm->m_state == 5 )
		comm->m_state = 2;

	Rva01358E74Leave( comm->m_lock );
	return iResult;
}

/* The control message: a code at +0x08 and a value at +0x0C, the same header
 * the other transports use. */
struct Rva0081AA20Message
{
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04 */
	int m_code;                     /* +0x08 */
	int m_value;                    /* +0x0C */
};

/* A queued send record carries its sequence at +0x08.  Only that is
 * established here. */
struct Rva0081AA20SendRecord
{
	int m_length;                   /* +0x00 */
	unsigned int m_tick;            /* +0x04 */
	unsigned int m_sequence;        /* +0x08, this record's own */
	int m_ack;                      /* +0x0C, piggybacked acknowledgement */
	unsigned char m_data[ 4 ];      /* +0x10 */
};

void Rva0081A8C0( struct Rva0081BD40Comm *comm );

/* 0x0081AA20 IS THE ACKNOWLEDGEMENT HANDLER, and it is the SAME BODY the third
 * transport has at 0x008186C0 -- same off-by-one for code 4, same
 * drag-the-ack-cursor loop, same rewind and kick -- walking this object's ring
 * at +0xEC..+0x100 instead of that one's at +0xB0..+0xC8.
 *
 * Because that one is already converted and explained, the reading here is not
 * a fresh inference: code 4 means "I want sequence N next" so everything BELOW
 * N is retired, anything else means "I have N" so N itself goes too, and the
 * comparison is unsigned so a wrapped sequence space still retires correctly.
 * Code 4 additionally snaps the transmit cursor back and kicks the sender,
 * which is what makes it a retransmit request.
 *
 * Duplicated code rather than shared: the two bodies differ only in field
 * offsets and which kick they call.
 */
void Rva0081AA20( struct Rva0081BD40Comm *comm,
	struct Rva0081AA20Message *message )
{
	int bRewind;
	unsigned int uAcked;
	struct Rva0081AA20SendRecord *record;
	int iAcked;

	bRewind = ( message->m_code == 4 );

	if ( bRewind )
		iAcked = message->m_value - 1;
	else
		iAcked = message->m_value;

	uAcked = iAcked;

	while ( comm->m_sendReadOffset != comm->m_sendWriteOffset )
	{
		record = (struct Rva0081AA20SendRecord *)( comm->m_sendBuffer
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
		Rva0081A8C0( comm );
	}
}

int Rva0081A3B0( struct Rva0081BD40Comm *comm,
	struct Rva0081AA20SendRecord *record )
{
	int iLength;
	unsigned short uHash;
	unsigned char *packet;

	if ( record != 0 )
	{
		iLength = record->m_length + 8;
		if ( comm->m_streamCapacity - comm->m_streamLength
			< iLength + 8 )
			return -1;

		packet = comm->m_streamBuffers[ comm->m_streamSlot ]
			+ comm->m_streamLength;
		packet[ 0 ] = 'G';
		packet[ 1 ] = 'S';
		packet[ 2 ] = (unsigned char)record->m_length;
		packet[ 3 ] = (unsigned char)( record->m_length ^ 0xFF );
		memcpy( packet + 4, (char *)record + 8, iLength );

		uHash = Rva0081A360( packet + 4, iLength );
		packet[ iLength + 4 ] = (unsigned char)uHash;
		packet[ iLength + 5 ] = (unsigned char)( uHash >> 8 );
		packet[ iLength + 6 ] = 0x0D;
		packet[ iLength + 7 ] = 0x0A;

		if ( comm->m_streamLength == 0 )
			Rva01358EDC( comm->m_handle, 2 );

		comm->m_streamLength = iLength + comm->m_streamLength + 8;
		comm->m_streamTick = Rva01358E0CTick();
	}

	if ( comm->m_streamLength == 0 )
		return 0;

	if ( Rva01358F64Wait( comm->m_event, 0 ) == 0x102 )
		return 0;

	Rva01358F70Write( comm->m_handle,
		comm->m_streamBuffers[ comm->m_streamSlot ],
		comm->m_streamLength, &comm->m_streamWritten,
		comm->m_streamOverlapped );

	comm->m_streamSlot = comm->m_streamSlot ^ 1;
	comm->m_streamLength = 0;

	return 0;
}

void Rva0081A810( struct Rva0081BD40Comm *comm )
{
	char packet[ 0x810 ];

	*(int *)( packet + 8 ) = comm->m_sendSequence;
	*(int *)( packet + 0xC ) = comm->m_recvSequence - 1;
	*(int *)packet = 0;

	Rva0081A3B0( comm, (struct Rva0081AA20SendRecord *)packet );
}

int Rva0081A5C0( struct Rva0081BD40Comm *comm )
{
	char packet[ 0x810 ];

	if ( comm->m_state == 1 || comm->m_state == 7 )
	{
		return 0;
	}

	*(int *)packet = 0;
	*(int *)( packet + 8 ) = 3;
	*(int *)( packet + 0xC ) = comm->m_pendingValue;

	Rva0081A3B0( comm, (struct Rva0081AA20SendRecord *)packet );

	comm->m_pendingValue = 0;
	comm->m_state = 7;

	return 0;
}

/* 0x0081A8C0 IS A WINDOWED SENDER: it transmits queued records while a
 * BYTE BUDGET lasts, and the budget is 0x800 -- 2048 bytes in flight.
 *
 * It computes the budget by walking everything ALREADY IN FLIGHT -- from the
 * read cursor up to the transmit cursor -- and subtracting each record's
 * length from 0x800.  So the window counts bytes outstanding, not packets, and
 * a few large records close it as effectively as many small ones.
 *
 * THE FIRST RECORD ALWAYS GOES OUT REGARDLESS OF THE BUDGET.  The stop test is
 * "transmit cursor is not at the read cursor AND this record is bigger than
 * what is left", so when nothing is in flight the size check is skipped
 * entirely.  Without that exception a record larger than 2048 bytes could
 * never be sent at all -- the window would never open wide enough -- and the
 * connection would wedge.  Reading the test as a plain budget check misses
 * that completely.
 *
 * Every record is stamped with one less than the expected receive sequence on
 * its way out, which is how acknowledgements ride along with data.
 *
 * The optional send callback fires BEFORE the transmit and its result is not
 * consulted; a failed transmit breaks the loop and leaves the transmit cursor
 * where it was, so the record is retried rather than skipped.
 */
void Rva0081A8C0( struct Rva0081BD40Comm *comm )
{
	int iOffset;
	int iBudget;
	struct Rva0081AA20SendRecord *p;
	struct Rva0081AA20SendRecord *record;

	iBudget = 0x800;

	for ( iOffset = comm->m_sendReadOffset;
		iOffset != comm->m_sendAckOffset;
		iOffset = ( iOffset + comm->m_sendRecordSize )
			% comm->m_sendBufferSize )
	{
		p = (struct Rva0081AA20SendRecord *)( comm->m_sendBuffer + iOffset );
		iBudget = iBudget - p->m_length;
	}

	while ( comm->m_sendAckOffset != comm->m_sendWriteOffset )
	{
		record = (struct Rva0081AA20SendRecord *)( comm->m_sendBuffer
			+ comm->m_sendAckOffset );

		if ( comm->m_sendAckOffset != comm->m_sendReadOffset
			&& record->m_length > iBudget )
			break;

		iBudget = iBudget - record->m_length;
		record->m_ack = comm->m_recvSequence - 1;

		if ( comm->m_sendProc != 0 )
		{
			comm->m_sendProc( comm, (char *)record + 0x10, record->m_length,
				0 );
		}

		if ( Rva0081A3B0( comm, record ) < 0 )
			break;

		comm->m_sendAckOffset = ( comm->m_sendAckOffset
			+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;
	}
}

/* 0x0081AB40 ACCEPTS A RECEIVED RECORD, and is the simpler sibling of the
 * third transport's 0x008187E0: same full-queue test by advancing the write
 * cursor one record, same three sequenced outcomes, but no unsequenced code-6
 * path and no byte counter.
 *
 *   - BELOW the expected sequence is a duplicate and is dropped;
 *   - ABOVE it means something was missed, and the incoming record is
 *     REWRITTEN IN PLACE into a code-4 retransmit request and sent straight
 *     back -- so a caller must treat its buffer as consumed;
 *   - equal but empty is a pure acknowledgement and is dropped.
 *
 * Everything else is copied in, the sequence advances by one, and the callback
 * is handed the payload from +0x10.
 *
 * The depth at +0x1938 is raised BEFORE the copy and lowered AFTER the
 * callback, so it covers the whole window in which the queue is being written
 * and a caller could re-enter.  That is what the dequeue's spin is waiting
 * out.
 */
void Rva0081AB40( struct Rva0081BD40Comm *comm,
	struct Rva0081AA20SendRecord *record )
{
	struct Rva0081AA20SendRecord *slot;

	if ( ( comm->m_recvWriteOffset + comm->m_recvRecordSize )
		% comm->m_recvBufferSize == comm->m_recvReadOffset )
		return;

	if ( (unsigned int)record->m_sequence
		< (unsigned int)comm->m_recvSequence )
		return;

	if ( (unsigned int)record->m_sequence
		> (unsigned int)comm->m_recvSequence )
	{
		record->m_sequence = 4;
		record->m_ack = comm->m_recvSequence;
		record->m_length = 0;

		Rva0081A3B0( comm, record );
		return;
	}

	if ( record->m_length == 0 )
		return;

	slot = (struct Rva0081AA20SendRecord *)( comm->m_recvBuffer
		+ comm->m_recvWriteOffset );

	memcpy( slot, record, comm->m_recvRecordSize );

	comm->m_depth = comm->m_depth + 1;

	comm->m_recvWriteOffset = ( comm->m_recvWriteOffset
		+ comm->m_recvRecordSize ) % comm->m_recvBufferSize;

	comm->m_recvSequence = comm->m_recvSequence + 1;

	if ( comm->m_recvProc != 0 )
	{
		comm->m_recvProc( comm, (char *)slot + 0x10, slot->m_length,
			slot->m_tick );
	}

	comm->m_depth = comm->m_depth - 1;
	comm->m_flags = comm->m_flags | 1;
}

/* 0x0081BA60 IS THE PUBLIC SEND: queue one payload and try to push it out.
 *
 * It refuses unless the state is 4 or 5, and returns 0 rather than an error
 * when the queue is full -- so a caller distinguishes "cannot ever" from "not
 * right now" by sign, and only the second is worth retrying.
 *
 * A ZERO LENGTH IS A QUERY, NOT A SEND.  It returns the queue depth plus one
 * without touching anything, which is how a caller asks how much is
 * outstanding through the same entry point.  That branch is taken before the
 * record is written, so a zero-length payload can never be queued.
 *
 * The size ceiling is the record size PLUS 0x800 -- the same 0x800 the
 * windowed sender uses as its in-flight budget.  Why a per-record limit is
 * expressed as a record plus a window is not something these bytes explain,
 * and it is reproduced rather than rationalised; over it, the answer is -6.
 *
 * The record is stamped with its own sequence, the sequence is advanced, the
 * peer's expected receive sequence minus one rides along as the
 * acknowledgement, and the arrival clock is read last.  THE SENDER IS THEN
 * CALLED UNDER THE LOCK, which is the only reason this body takes it.
 *
 * The return is the queue depth, floored at 1 -- so a successful send never
 * reports zero, which would otherwise be indistinguishable from the
 * queue-full case above.
 */
int Rva0081BA60( struct Rva0081BD40Comm *comm, const void *payload,
	int length )
{
	int iCount;
	struct Rva0081AA20SendRecord *slot;
	int iDepth;

	if ( comm->m_state != 4 && comm->m_state != 5 )
		return -2;

	if ( ( comm->m_sendWriteOffset + comm->m_sendRecordSize )
		% comm->m_sendBufferSize == comm->m_sendReadOffset )
		return 0;

	if ( length == 0 )
	{
		iCount = ( ( comm->m_sendWriteOffset + comm->m_sendBufferSize
			- comm->m_sendReadOffset ) % comm->m_sendBufferSize )
			/ comm->m_sendRecordSize;

		return iCount + 1;
	}

	slot = (struct Rva0081AA20SendRecord *)( comm->m_sendBuffer
		+ comm->m_sendWriteOffset );

	slot->m_length = length;

	/* UNSIGNED: retail compares with jbe, so a negative length does not slip
	 * under the ceiling -- it wraps to a huge value and is rejected.  A signed
	 * compare here would accept it and then memcpy with it. */
	if ( (unsigned int)( slot->m_length + 4 )
		> (unsigned int)( comm->m_sendRecordSize + 0x800 ) )
		return -6;

	memcpy( (char *)slot + 0x10, payload, length );

	slot->m_sequence = comm->m_sendSequence;
	comm->m_sendSequence = comm->m_sendSequence + 1;
	slot->m_ack = comm->m_recvSequence - 1;
	slot->m_tick = Rva01358E0CTick();

	comm->m_sendWriteOffset = ( comm->m_sendWriteOffset
		+ comm->m_sendRecordSize ) % comm->m_sendBufferSize;

	Rva01358D18Enter( comm->m_lock );
	Rva0081A8C0( comm );
	Rva01358E74Leave( comm->m_lock );

	iCount = ( ( comm->m_sendWriteOffset + comm->m_sendBufferSize
		- comm->m_sendReadOffset ) % comm->m_sendBufferSize )
		/ comm->m_sendRecordSize;

	if ( iCount > 0 )
		iDepth = iCount;
	else
		iDepth = 1;

	return iDepth;
}
