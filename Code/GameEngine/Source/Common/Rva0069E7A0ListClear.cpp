// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// STLport list::clear of 4-byte refcounted handles: walk sentinel->next,
// inlined Release_Ref, free each 12-byte node, then relink the sentinel
// to itself.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

namespace _STL
{
	template <bool THREADS, int INSTANCE>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *node, unsigned int bytes);
	};
}

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class ThingRef
{
public:
	RefCountedThing *m_ptr;

	~ThingRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
};

class ListNode
{
public:
	ListNode *m_next;
	ListNode *m_prev;
	ThingRef m_value;
};

class Open269E7A0List
{
public:
	void clear();

	ListNode *m_node;
};

// ?clear@Open269E7A0List@@QAEXXZ
void Open269E7A0List::clear()
{
	ListNode *sentinel = m_node;
	ListNode *node = sentinel->m_next;
	while (node != sentinel)
	{
		ListNode *cur = node;
		node = node->m_next;
		cur->m_value.~ThingRef();
		_STL::__node_alloc<true, 0>::_M_deallocate(cur, 12);
		sentinel = m_node;
	}
	m_node->m_next = m_node;
	m_node->m_prev = m_node;
}
