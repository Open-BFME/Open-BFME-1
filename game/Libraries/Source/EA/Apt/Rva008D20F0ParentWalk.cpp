// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Walks the chain at +0x4C until a node whose packed field at +4 carries kind
// 0x12 or 0x13 with bit 15 set, then returns that node. The same packed-field
// idiom drives BfmeNode1220::bfmeAllows1220 at 0x008D2070, the body that ends
// four bytes below this one.
//
// The barrier between the two kind tests is reconstruction shaping, not
// original source. Without it MSVC 7.1 propagates kind 0x12 into the second
// test and folds the first exit branch into the second one; retail keeps both
// branches and re-tests the tag.

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

struct Rva008D20F0Node
{
	unsigned char m_pad0[ 4 ];
	unsigned int m_kind;
	unsigned char m_pad08[ 0x4C - 8 ];
	Rva008D20F0Node *m_next;

	Rva008D20F0Node *walk();
};

Rva008D20F0Node *Rva008D20F0Node::walk()
{
	Rva008D20F0Node *node = this;
	for ( ;; )
	{
		unsigned int kind = node->m_kind;
		unsigned int tag = kind & 0x3f;
		if ( tag == 0x12 )
		{
			if ( !((unsigned char)(~(kind >> 15)) & 1) )
				return node;
		}
		_ReadWriteBarrier();
		if ( tag == 0x13 )
		{
			if ( !((unsigned char)(~(kind >> 15)) & 1) )
				return node;
		}
		node = node->m_next;
	}
}
