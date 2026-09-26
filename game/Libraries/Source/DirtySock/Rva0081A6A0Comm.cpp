// cl: /Od /GZ /GS /MD /DNDEBUG
// Retail 0x0081A6A0: serial/sequenced control-record state transition.

struct Rva0081A6A0Comm
{
	char m_head[ 0xcc ];
	int m_state;                  /* +0xcc */
	int m_pendingValue;           /* +0xd0 */
};

struct Rva0081A6A0Record
{
	int m_length;                 /* +0x00 */
	unsigned int m_tick;          /* +0x04 */
	int m_sequence;               /* +0x08 */
	int m_ack;                    /* +0x0c */
};

extern "C" int Rva0081A3B0( struct Rva0081A6A0Comm *comm,
	struct Rva0081A6A0Record *record );

extern "C" void Rva0081A6A0( struct Rva0081A6A0Comm *comm,
	struct Rva0081A6A0Record *record )
{
	if ( record->m_length != 0
		|| record->m_ack != comm->m_pendingValue )
		return;

	if ( record->m_sequence == 1 )
	{
		record->m_sequence = 2;
		Rva0081A3B0( comm, record );
		return;
	}

	if ( record->m_sequence == 2 )
	{
		if ( comm->m_state == 2 )
			comm->m_state = 4;
	}
	else if ( record->m_sequence == 3 )
	{
		if ( comm->m_state == 4 )
			comm->m_state = 7;
	}
}
