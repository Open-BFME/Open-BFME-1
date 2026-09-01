// ?link@Rva0060FE50@@QAEXPAUBfmeIntrusiveNode60FE50@@@Z
// partial score=0.95 date=2026-08-31
struct BfmeIntrusiveOwner60FE50;

struct BfmeIntrusiveNode60FE50
{
	BfmeIntrusiveOwner60FE50 *m_owner;
	BfmeIntrusiveNode60FE50 *m_previous;
	BfmeIntrusiveNode60FE50 *m_next;
};

struct BfmeIntrusiveOwner60FE50
{
	char m_head[ 0x98 ];
	BfmeIntrusiveNode60FE50 *m_first;
	BfmeIntrusiveNode60FE50 *m_last;
};

class Rva0060FE50
{
public:
	void link( BfmeIntrusiveNode60FE50 *node );

private:
	char m_head[ 0x14 ];
	BfmeIntrusiveOwner60FE50 *m_owner;
};

void Rva0060FE50::link( BfmeIntrusiveNode60FE50 *node )
{
	volatile int empty = 0;
	BfmeIntrusiveOwner60FE50 *owner = m_owner;
	node->m_owner = owner;

	if ( owner != 0 )
	{
		BfmeIntrusiveNode60FE50 *previous = owner->m_last;
		node->m_previous = previous;
		node->m_next = 0;
		owner->m_last = node;

		if ( previous != 0 )
		{
			previous->m_next = node;
			return;
		}

		owner->m_first = node;
		return;
	}

	node->m_next = 0;
	node->m_previous = 0;
}
