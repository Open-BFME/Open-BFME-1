// cl: /DNDEBUG /MD /EHsc
// Unlink a node from one of 14 doubly-linked slot lists. Heads at +0x0C,
// tails at +0x44, occupancy at +0x84. The slot index is a lazy pointer at
// node+0x4C whose +0x7C field is the index.

class BfmeSlotIndex
{
public:
	unsigned char m_pad[ 0x7C ];
	int m_index;
};

class ParticleSystem;
ParticleSystem *Make00001B18( void );

class BfmeSlotIndexPtr
{
public:
	operator BfmeSlotIndex *( void ) const
	{
		return (BfmeSlotIndex *)m_target;
	}

	BfmeSlotIndex *operator->( void ) const
	{
		ParticleSystem *target = m_target;
		if ( !target )
			target = Make00001B18();
		return (BfmeSlotIndex *)target;
	}

private:
	ParticleSystem *m_target;
};

class BfmeSlotNode
{
public:
	unsigned char m_pad[ 0x44 ];
	BfmeSlotNode *m_next;
	BfmeSlotNode *m_prev;
	BfmeSlotIndexPtr m_kind;
	unsigned char m_pad50[ 0x7A - 0x50 ];
	unsigned char m_inList;
};

class Rva005C2070
{
public:
	void remove( BfmeSlotNode *node );

	unsigned char m_pad[ 0x0C ];
	BfmeSlotNode *m_heads[ 14 ];
	BfmeSlotNode *m_tails[ 14 ];
	int m_at7c;
	void *m_list;
	int m_count;
};

void Rva005C2070::remove( BfmeSlotNode *node )
{
	if ( !node->m_inList )
		return;

	int index = node->m_kind->m_index;

	if ( node->m_next )
		node->m_next->m_prev = node->m_prev;
	if ( node->m_prev )
		node->m_prev->m_next = node->m_next;
	if ( node == m_heads[ index ] )
		m_heads[ index ] = node->m_next;
	if ( node == m_tails[ index ] )
		m_tails[ index ] = node->m_prev;

	node->m_prev = 0;
	node->m_next = 0;
	node->m_inList = 0;
	--m_count;
}
