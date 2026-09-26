// cl: /DNDEBUG /MD /EHsc

namespace _STL
{
	template <bool threads, int inst>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *address, unsigned size);
	};
}

struct Rva00124FC0RbTreeNode
{
	char m_header[8];
	Rva00124FC0RbTreeNode *m_left;
	Rva00124FC0RbTreeNode *m_right;
	char m_value[44];
};

class Rva00124FC0RbTree
{
public:
	void erase(Rva00124FC0RbTreeNode *node);
	void eraseViaThunk(Rva00124FC0RbTreeNode *node);
};

void Rva00124FC0RbTree::erase(Rva00124FC0RbTreeNode *node)
{
	while (node != 0)
	{
		eraseViaThunk(node->m_right);
		Rva00124FC0RbTreeNode *left = node->m_left;
		_STL::__node_alloc<false, 0>::_M_deallocate(node, sizeof(Rva00124FC0RbTreeNode));
		node = left;
	}
}
