// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

class QueuedDownload
{
public:
	~QueuedDownload();

private:
	char m_fields[0x1c];
};

namespace _STL
{
template <class T>
class allocator
{
};

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

class Gen00627270Owner
{
private:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/LISTNODE.H
	struct Node
	{
		Node *next;
		Node *previous;
		QueuedDownload value;
	};

public:
	void cleanup();

private:
	Node *m_node;
};

// ?cleanup@Gen00627270Owner@@QAEXXZ
void Gen00627270Owner::cleanup()
{
	Node *node = m_node->next;
	while (node != m_node)
	{
		Node *old = node;
		node = node->next;
		old->value.~QueuedDownload();
		_STL::nodePoolDeallocate(old, sizeof(Node));
	}

	m_node->next = m_node;
	m_node->previous = m_node;
}
