// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// STLport list::erase(iterator) of a 4-byte refcounted handle: unlink the
// node, Release_Ref the payload, free the 12-byte node, return next via sret.

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
	~ThingRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

private:
	RefCountedThing *m_ptr;
};

class ListNode
{
public:
	ListNode *m_next;
	ListNode *m_prev;
	ThingRef m_value;
};

class ListIterator
{
public:
	ListIterator(ListNode *node) : m_node(node) {}

private:
	ListNode *m_node;
};

// ?erase@Open269DBE0List@@YG?AVListIterator@@PAVListNode@@@Z
ListIterator __stdcall erase_Open269DBE0(ListNode *node)
{
	ListNode *next = node->m_next;
	ListNode *prev = node->m_prev;
	prev->m_next = next;
	next->m_prev = prev;
	node->m_value.~ThingRef();
	_STL::__node_alloc<true, 0>::_M_deallocate(node, 12);
	return ListIterator(next);
}
