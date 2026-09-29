// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// STLport list pop_back of a 4-byte refcounted handle: unlink the node
// behind the heap sentinel, run the inlined Release_Ref destructor, free
// the 12-byte node.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

namespace _STL
{
	// The node allocator's pool entry points are private STLport members
	// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
	// 0x0082E5F0); these TU-local helpers reach them under their real names.
	template <bool __threads, int __inst> class __node_alloc;
	static void nodePoolDeallocate(void *block, unsigned int bytes);
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend void nodePoolDeallocate(void *, unsigned int);
		static void *__cdecl _M_allocate(unsigned int __n);
		static void __cdecl _M_deallocate(void *__p, unsigned int __n);
	};
	static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Tools/Babylon/list.h
class ListNode
{
public:
	ListNode *m_next;
	ListNode *m_prev;
	ThingRef m_value;
};

class Open269DC90List
{
public:
	void pop_back();

	ListNode *m_node;
};

// ?pop_back@Open269DC90List@@QAEXXZ
void Open269DC90List::pop_back()
{
	ListNode *node = m_node->m_prev;
	ListNode *next = node->m_next;
	ListNode *prev = node->m_prev;
	prev->m_next = next;
	next->m_prev = prev;
	node->m_value.~ThingRef();
	_STL::nodePoolDeallocate(node, 12);
}
