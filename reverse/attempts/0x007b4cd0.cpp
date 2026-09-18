// ?bfmeOne928F@BfmeThing928F@@QAEXXZ
// partial score=0.99 date=2026-09-18
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB

inline void *operator new(unsigned int, void *place) { return place; }

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};

class __node_alloc
{
public:
	static void _M_deallocate(void *pointer, unsigned int size);
};

template <class T1, class T2>
inline void __cdecl _Construct(T1 *destination, const T2 &value)
{
	new (destination) T1(value);
}

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class T>
struct _List_node : public _List_node_base
{
	T _M_data;
};

template <class T>
class list
{
public:
	typedef _List_node<T> _Node;

	list()
	{
		_Node *node = (_Node *)__new_alloc::allocate(sizeof(_Node));
		node->_M_next = node;
		node->_M_prev = node;
		_M_node = node;
	}

	void push_back(const T &value)
	{
		_Node *node = (_Node *)__new_alloc::allocate(sizeof(_Node));
		_Construct(&node->_M_data, value);
		_List_node_base *at = _M_node;
		_List_node_base *before = at->_M_prev;
		node->_M_next = at;
		node->_M_prev = before;
		before->_M_next = node;
		at->_M_prev = node;
	}

	__forceinline void clear()
	{
		register _List_node_base *node = _M_node->_M_next;
		while (node != _M_node)
		{
			_List_node_base *old = node;
			node = node->_M_next;
			__node_alloc::_M_deallocate(old, sizeof(_Node));
		}
		_M_node->_M_next = _M_node;
		_M_node->_M_prev = _M_node;
	}

	__forceinline ~list()
	{
		clear();
		__node_alloc::_M_deallocate(_M_node, sizeof(_Node));
	}

	_Node *_M_node;
};
}

class Shadow
{
public:
	virtual void slot00(int);
	virtual void slot01(int);
	virtual void release();
	void rva00459960(int, int, int, int, int, int, int, int);
};

struct Rva007B4CD0Entry
{
	char m_pad00[0x34];
	int m_type;
	char m_pad38[0x9c];
	Rva007B4CD0Entry *m_next;
};

class BfmeThing928F
{
public:
	void bfmeOne928F();
	void *m_pad00;
	Rva007B4CD0Entry *m_list04;
	Rva007B4CD0Entry *m_list08;
};

void BfmeThing928F::bfmeOne928F()
{
	Rva007B4CD0Entry *entry;
	_STL::list<Shadow *> pending;
	int list = 0;
	while (list <= 1)
	{
		if (list != 0)
			entry = m_list04;
		else
			entry = m_list08;
		while (entry)
		{
			if (entry->m_type == 0x400 || entry->m_type == 0x800)
				pending.push_back((Shadow *)entry);
			entry = entry->m_next;
		}
		++list;
	}
	_STL::_List_node<Shadow *> *node = pending._M_node;
	while (node->_M_next != pending._M_node)
	{
		node = (_STL::_List_node<Shadow *> *)node->_M_next;
		((Shadow *)node->_M_data)->rva00459960(0, 0, 0, 0, 0, 0, 0, 0);
		((Shadow *)node->_M_data)->release();
	}
	pending.clear();
}
