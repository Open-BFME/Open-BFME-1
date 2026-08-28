// ?d_007fa240@@YAXXZ
// partial score=1.0 date=2026-08-28
// cl: /GX-

// The retail assertion path in this span names jabba/fesl/source/transactor.cpp.
// The member and type names that remain unproved are kept address-derived.

struct FeslTransactionSlot
{
	unsigned int m_id;
	int m_state;
	void *m_reply;
	void *m_callback;
	void *m_context;
	unsigned int m_deadline;
	void *m_data;
};

class FeslTransactor
{
public:
	void Rva007FA240( unsigned int now );

private:
	void Rva007FA170( FeslTransactionSlot *slot, int result );

	char m_head[ 0x18 ];
	unsigned int m_nextDeadline;
	char m_beforeSlots[ 0x0C ];
	FeslTransactionSlot m_slots[ 32 ];
};

void FeslTransactor::Rva007FA240( unsigned int now )
{
	unsigned int nextDeadline = 0;
	bool noTimeout = true;

	for( int i = 0; i < 32; ++i )
	{
		FeslTransactionSlot *slot = &m_slots[ i ];
		if( slot->m_state != 0 )
		{
			if( now >= slot->m_deadline )
			{
				Rva007FA170( slot, -102 );
				noTimeout = false;
			}
			else if( nextDeadline == 0 || nextDeadline > slot->m_deadline )
			{
				nextDeadline = slot->m_deadline;
			}
		}
	}

	if( noTimeout )
		m_nextDeadline = nextDeadline;
}
