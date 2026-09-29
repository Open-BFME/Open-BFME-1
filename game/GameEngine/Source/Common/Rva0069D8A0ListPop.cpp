// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Pop the head of a circular list whose sentinel is the list object itself
// (retail cmp [eax],eax). Unlink, free the 12-byte node, return the payload.

class Open269D8A0;
class Open269D8E0;

// The pool free is STLport's private __node_alloc<true, 0>::_M_deallocate
// (0x0082E5F0); /Ob0 keeps any forwarding helper out of line, so the two
// callers are befriended instead.
namespace _STL
{
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend class ::Open269D8A0;
		friend class ::Open269D8E0;
		static void __cdecl _M_deallocate(void *__p, unsigned int __n);
	};
}

class Open2ListNode
{
public:
	Open2ListNode *m_next;
	Open2ListNode *m_prev;
	void *m_value;
};

class Open269D8A0
{
public:
	void *popFront();

	char m_pad[0x9c0];
	Open2ListNode *m_list;
};

class Open269D8E0
{
public:
	void *popFront();

	char m_pad[0x9c4];
	Open2ListNode *m_list;
};

// @?popFront@Open269D8A0@@QAEPAXXZ 0x0069D8A0
void *Open269D8A0::popFront()
{
	void *list = m_list;
	if (*(void *volatile *)list != list)
	{
		Open2ListNode *node = (Open2ListNode *)*(void **)list;
		Open2ListNode *next = node->m_next;
		Open2ListNode *prev = node->m_prev;
		void *value = node->m_value;

		prev->m_next = next;
		next->m_prev = prev;
		_STL::__node_alloc<true, 0>::_M_deallocate(node, 12);
		return value;
	}
	return 0;
}

// @?popFront@Open269D8E0@@QAEPAXXZ 0x0069D8E0
void *Open269D8E0::popFront()
{
	void *list = m_list;
	if (*(void *volatile *)list != list)
	{
		Open2ListNode *node = (Open2ListNode *)*(void **)list;
		Open2ListNode *next = node->m_next;
		Open2ListNode *prev = node->m_prev;
		void *value = node->m_value;

		prev->m_next = next;
		next->m_prev = prev;
		_STL::__node_alloc<true, 0>::_M_deallocate(node, 12);
		return value;
	}
	return 0;
}
