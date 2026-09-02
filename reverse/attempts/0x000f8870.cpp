// ?removeValue@BfmeTunnelList@@QAEXPAX0@Z
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Circular-list value removal used by the TunnelTracker cluster.  The second
// parameter belongs to the caller-facing ABI but is not used by this body.

extern void __cdecl bfmeDeallocate( void *memory, unsigned int bytes );

struct BfmeTunnelListNode
{
	BfmeTunnelListNode *next;
	BfmeTunnelListNode *previous;
	void *value;
};

class BfmeTunnelList
{
public:
	void removeValue( void *value, void *unused );

private:
	unsigned char m_unmodelled_000[ 8 ];
	BfmeTunnelListNode *m_head;
	unsigned int m_unmodelled_00c;
	unsigned int m_count;
};

void BfmeTunnelList::removeValue( void *value, void *unused )
{
	BfmeTunnelListNode *head = m_head;
	BfmeTunnelListNode *node = head->next;

	if( node != head )
	{
		do
		{
			if( node->value == value )
				break;
			node = node->next;
		} while( node != head );
	}

	if( node != head )
	{
		BfmeTunnelListNode *next = node->next;
		BfmeTunnelListNode *previous = node->previous;
		previous->next = next;
		next->previous = previous;
		bfmeDeallocate( node, sizeof( BfmeTunnelListNode ) );
		--m_count;
	}
}
