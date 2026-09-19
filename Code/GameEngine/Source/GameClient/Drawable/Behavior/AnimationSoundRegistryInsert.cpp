// The registry-head insertion body at retail 0x004091C0.
//
// Its only named caller is AnimationSoundClientBehavior's constructor at
// 0x00605380.  That constructor and the adjacent 0x00409140 removal body
// independently establish the node links (+0x14/+0x18), registry head/tail
// (+0x08/+0x0C), and count (+0x18) layout.  The method name remains an
// address-derived identity because the retail symbol is not recovered.

struct Rva004091C0Node
{
	unsigned char m_pad[0x14];
	Rva004091C0Node *m_next;
	Rva004091C0Node *m_prev;
};

class Rva004091C0Registry
{
public:
	void rva_004091C0( Rva004091C0Node *node );

private:
	unsigned char m_pad[8];
	Rva004091C0Node *m_head;
	Rva004091C0Node *m_tail;
	unsigned char m_second[8];
	int m_count;
};

void Rva004091C0Registry::rva_004091C0( Rva004091C0Node *node )
{
	if ( m_head )
	{
		m_head->m_prev = node;
	}

	node->m_next = m_head;
	node->m_prev = 0;
	m_head = node;

	if ( !m_tail )
	{
		m_tail = node;
	}

	++m_count;
}
