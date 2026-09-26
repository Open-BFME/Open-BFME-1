// cl: /Od /GZ /GS /MD /DNDEBUG
// Open-BFME: DirtySock comm-ring reset at retail RVA 0x0081B700 (134 bytes).

/*
 * The matched Rva0081B010 worker calls this body with one pointer immediately
 * before opening the transport.  The sibling Rva0081BD40Comm definition in
 * Y4CommSequencedRing.c proves the ring fields and their offsets; this TU keeps
 * the reset view local so no shared header or already-landed source changes.
 */
struct Rva0081BD40Comm
{
	unsigned char m_head[ 0x38 ];
	void *m_sendProc;
	void *m_recvProc;
	unsigned char m_head2[ 0x8c ];
	int m_state;                         /* +0xcc */
	int m_pendingValue;                  /* +0xd0 */
	int m_recvRecordSize;                /* +0xd4 */
	int m_recvBufferSize;                /* +0xd8 */
	int m_recvWriteOffset;               /* +0xdc */
	int m_recvReadOffset;                /* +0xe0 */
	unsigned char *m_recvBuffer;         /* +0xe4 */
	unsigned int m_recvSequence;        /* +0xe8 */
	int m_sendRecordSize;                /* +0xec */
	int m_sendBufferSize;                /* +0xf0 */
	int m_sendWriteOffset;               /* +0xf4 */
	int m_sendReadOffset;                /* +0xf8 */
	int m_sendAckOffset;                 /* +0xfc */
	unsigned char *m_sendBuffer;         /* +0x100 */
	unsigned int m_sendSequence;         /* +0x104 */
	unsigned char m_unmodeledTail[ 0x1810 ]; /* +0x108..+0x1917 */
	unsigned int m_backdatedClock;       /* +0x1918 */
};

extern "C" __declspec( dllimport ) unsigned int __stdcall GetTickCount( void );

/* The retail caller and callee are cdecl: the caller removes this pointer. */
extern "C" void __cdecl Rva0081B700( struct Rva0081BD40Comm *comm )
{
	comm->m_sendWriteOffset = 0;
	comm->m_sendReadOffset = 0;
	comm->m_sendAckOffset = 0;
	comm->m_sendSequence = 0x65;
	comm->m_recvWriteOffset = 0;
	comm->m_recvReadOffset = 0;
	comm->m_recvSequence = 0x65;
	comm->m_backdatedClock = GetTickCount() - 5000;
}
