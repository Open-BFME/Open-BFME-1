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

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int size);
};

}

class Gen00627270Owner
{
private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/LISTNODE.H
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
		_STL::__node_alloc<true, 0>::_M_deallocate(old, sizeof(Node));
	}

	m_node->next = m_node;
	m_node->previous = m_node;
}
