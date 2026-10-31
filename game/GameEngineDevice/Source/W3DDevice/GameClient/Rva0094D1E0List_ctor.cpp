// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Rva0094D1E0List constructor, retail 0x0094D1E0 (ret 8): called by the
// W3DTreeBuffer and W3DShrubBuffer constructors for the list members that
// Rva0094D1E0List::clear (0x0094CE50) empties. The STLport tree header node
// (0x24 bytes) is self-linked, the capacity is clamped to 0x800 and
// the cached node at +0x14 starts at the tree's leftmost link.

struct Rva0094D1E0ListTree;

namespace _STL
{
// The small-block allocation calls _M_allocate directly.  An inline
// allocate() forwarder here was emitted as a 5-byte
// ?allocate@?$__node_alloc@$00$0A@@_STL@@SAPAXI@Z COMDAT, not retail's
// 29-byte size-checking body.
template <bool threads, int inst>
class __node_alloc
{
	friend struct ::Rva0094D1E0ListTree;
	static void *_M_allocate( unsigned int n );
};
}

struct Rva0094D1E0ListNode
{
	unsigned char m_color;
	Rva0094D1E0ListNode *m_parent;
	Rva0094D1E0ListNode *m_left;
	Rva0094D1E0ListNode *m_right;
};

struct Rva0094D1E0ListTree
{
	Rva0094D1E0ListNode *m_header;
	int m_count;
	int m_compare;

	Rva0094D1E0ListTree()
	{
		m_header = 0;
		m_header = (Rva0094D1E0ListNode *)_STL::__node_alloc<true, 0>::_M_allocate( 0x24 );
		m_count = 0;
		m_header->m_color = 0;
		m_header->m_parent = 0;
		m_header->m_left = m_header;
		m_header->m_right = m_header;
	}
};

struct Rva0094D1E0ListCursor
{
	Rva0094D1E0ListNode *m_node;
	int m_index;

	Rva0094D1E0ListCursor() : m_node( 0 ), m_index( 0 ) {}
};

class Rva0094D1E0List
{
public:
	Rva0094D1E0List( int capacity, int extra );

private:
	int m_capacity;
	int m_extra;
	Rva0094D1E0ListTree m_tree;
	Rva0094D1E0ListCursor m_cursor;
	bool m_changed;
	bool m_reset;
};

Rva0094D1E0List::Rva0094D1E0List( int capacity, int extra ) :
	m_capacity( capacity ),
	m_extra( extra ),
	m_changed( false ),
	m_reset( false )
{
	if ( (unsigned int)m_capacity > 0x800 )
		m_capacity = 0x800;
	m_cursor.m_node = m_tree.m_header->m_left;
}
