// cl: /Od /GZ /GS /MD /DNDEBUG /Gy
// Open-BFME: DirtySock control-record helper at retail RVA 0x0081A740 (176B).

/* The object prefix is the independently recovered Rva0081BD40Comm layout
 * used by the neighboring Y4CommSequencedRing bodies.  This TU only needs the
 * pending control value at +0xD0, but retaining the proven prefix keeps the
 * receiver type and offset explicit without changing a shared source/header.
 */
struct Rva0081BD40Comm
{
	unsigned char m_head[ 0x38 ];
	void *m_sendProc;
	void *m_recvProc;
	unsigned char m_head2[ 0x8c ];
	int m_state;                         /* +0xcc */
	int m_pendingValue;                  /* +0xd0 */
};

/* A queued send record's header is established by the matched A3B0 callers:
 * length, tick, sequence and acknowledgement, followed by payload at +0x10.
 */
struct Rva0081AA20SendRecord
{
	int m_length;
	unsigned int m_tick;
	unsigned int m_sequence;
	int m_ack;
	unsigned char m_data[ 4 ];
};

extern "C" __declspec( dllimport ) unsigned int __stdcall GetTickCount( void );
extern "C" int Rva0081A3B0( struct Rva0081BD40Comm *comm,
	struct Rva0081AA20SendRecord *record );

/* No original source spelling is established; the neutral RVA name is kept.
 * The sole binary caller passes one comm pointer and removes four bytes. */
extern "C" void __cdecl Rva0081A740( struct Rva0081BD40Comm *comm )
{
	char packet[ 0x810 ];

	while ( comm->m_pendingValue == 0 )
	{
		comm->m_pendingValue = GetTickCount() ^ (unsigned int)comm;
	}

	*(int *)packet = 0;
	*(int *)( packet + 8 ) = 1;
	*(int *)( packet + 0xc ) = comm->m_pendingValue;

	Rva0081A3B0( comm, (struct Rva0081AA20SendRecord *)packet );
}
