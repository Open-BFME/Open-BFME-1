// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

typedef bool Bool;

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};
template <class First, class Second>
struct pair
{
	First first;
	Second second;
};
template <class Pair> struct _Select1st {};

template <bool Threads, int Instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *node, unsigned int bytes);
};

struct _Rb_tree_node_base
{
	Bool color;
	_Rb_tree_node_base *parent;
	_Rb_tree_node_base *left;
	_Rb_tree_node_base *right;
};

template <class Value>
struct _Rb_tree_node : _Rb_tree_node_base
{
	Value value;
};

template <class Dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> Node;
	~_Rb_tree();
	_Rb_tree_node_base *m_header;
	unsigned int m_size;
	Alloc m_allocator;

	__forceinline void clear()
	{
		if (m_size != 0)
		{
			Node *node = reinterpret_cast<Node *>(m_header->parent);
			if (node != 0)
			{
				do
				{
					_M_erase(reinterpret_cast<Node *>(node->right));
					Node *left = reinterpret_cast<Node *>(node->left);
					_STL::__node_alloc<true, 0>::_M_deallocate(node, 0x18);
					node = left;
				} while (node != 0);
			}
			m_header->left = m_header;
			m_header->parent = 0;
			m_header->right = m_header;
			m_size = 0;
		}
	}

private:
	void _M_erase(Node *node);
};

template <class Key, class Value, class Compare = less<Key>,
	class Alloc = allocator<pair<const Key, Value> > >
class map
{
public:
	typedef pair<const Key, Value> Entry;
	typedef _Rb_tree<Key, Entry, _Select1st<Entry>, Compare, Alloc> Tree;

	__forceinline void clear() { m_tree.clear(); }

public:
	Tree m_tree;
};
}

struct Gen_t_00653710_p4pod
{
	void *value;
};

typedef _STL::_Rb_tree<int,
	_STL::pair<const int, Gen_t_00653710_p4pod>,
	_STL::_Select1st<_STL::pair<const int, Gen_t_00653710_p4pod> >,
	_STL::less<int>,
	_STL::allocator<_STL::pair<const int, Gen_t_00653710_p4pod> > > BFMENetworkList;

struct BFMENetworkListNode
{
	Bool color;
	char padding[3];
	BFMENetworkListNode *parent;
	BFMENetworkListNode *left;
	BFMENetworkListNode *right;
	int key;
	void *payload;
};

class ThreadClass
{
public:
	virtual ~ThreadClass();
	virtual void Execute();

protected:
	virtual void Thread_Function() = 0;

private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};

extern "C" void __cdecl ghttpCleanup();

class BFMENetworkBackend : public ThreadClass
{
public:
	virtual ~BFMENetworkBackend();
	virtual void Thread_Function();

private:
	char m_padding50[0x0c];
	BFMENetworkList m_list;
	void *m_ownerLock;
};

BFMENetworkBackend::~BFMENetworkBackend()
{
	BFMENetworkList &list = m_list;
	BFMENetworkListNode *node = reinterpret_cast<BFMENetworkListNode *>(
		list.m_header)->left;

	while (node != reinterpret_cast<BFMENetworkListNode *>(list.m_header))
	{
		if (node->payload != 0)
			::operator delete(node->payload);
		node = reinterpret_cast<BFMENetworkListNode *>(
			_STL::_Rb_global<bool>::_M_increment(
				reinterpret_cast<_STL::_Rb_tree_node_base *>(node)));
	}

	if (list.m_size != 0)
		list.clear();

	ghttpCleanup();
}
