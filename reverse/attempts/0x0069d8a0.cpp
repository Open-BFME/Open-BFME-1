// ?d_0069d8a0@@YAXXZ
// partial score=0.95 date=2026-08-29
// A list pop written against a hand model of the container rather than the
// vendored STLport, because the two disagree about one thing that decides the
// first six bytes: retail's sentinel node is EMBEDDED at the head of the list
// (`cmp dword ptr [eax],eax` compares the head link against the list's own
// address), while the STLport in vendor/ holds a pointer to a heap sentinel
// and needs one more indirection to say the same thing.
//
// Everything after that agrees with upstream's `erase`: unlink through the
// node's own two links, then hand the twelve-byte node back to the node
// allocator.  The value is read BEFORE the unlink and returned, which is what
// makes this a pop rather than an erase.

namespace _STL
{
	template <bool THREADS, int INSTANCE>
	class __node_alloc
	{
	public:
		static void _M_deallocate( void *node, unsigned int bytes );	// retail 0x0082E5F0
	};
}

class Open2ListNode
{
public:
	Open2ListNode *m_next;
	Open2ListNode *m_prev;
	void *m_value;
};

class Open2List
{
public:
	Open2ListNode m_head;
};

class Open269D8A0
{
public:
	void *popFront( void );

	char m_pad[ 0x9c0 ];
	Open2List *m_list;
};

// @?popFront@Open269D8A0@@QAEPAXXZ 0x0069D8A0
void *Open269D8A0::popFront( void )
{
	Open2List *list = m_list;
	if( (Open2ListNode *)list != list->m_head.m_next )
	{
		Open2ListNode *node = list->m_head.m_next;
		Open2ListNode *next = node->m_next;
		Open2ListNode *prev = node->m_prev;
		void *value = node->m_value;

		prev->m_next = next;
		next->m_prev = prev;
		_STL::__node_alloc<true, 0>::_M_deallocate( node, 12 );
		return value;
	}
	return 0;
}
