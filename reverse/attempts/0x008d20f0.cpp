// ?walk@Rva008D20F0Node@@QAEPAU1@XZ
// partial score=0.95 date=2026-09-09
// Address-derived: walk this->m_next while the packed +0x4 field's low 6 bits
// read kind 0x12 or 0x13 and bit 15 of that field is clear; otherwise return
// the current node.
struct Rva008D20F0Node
{
	unsigned char m_pad0[4];
	unsigned int m_kind;
	unsigned char m_pad8[0x4C - 8];
	Rva008D20F0Node *m_next;

	Rva008D20F0Node *walk();
};

Rva008D20F0Node *Rva008D20F0Node::walk()
{
	Rva008D20F0Node *node = this;
	for ( ;; )
	{
		unsigned int tag = node->m_kind & 0x3f;
		if ( tag == 0x12 )
		{
			if ( !((unsigned char)(~(node->m_kind >> 15)) & 1) )
				return node;
		}
		if ( tag == 0x13 )
		{
			if ( !((unsigned char)(~(node->m_kind >> 15)) & 1) )
				return node;
		}
		node = node->m_next;
	}
}
