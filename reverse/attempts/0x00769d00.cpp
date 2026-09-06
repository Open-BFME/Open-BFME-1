// ?eraseId@Rva00769D00Owner@@QAEXH@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: 0x00769D00 (79 B), a game-class wrapper erasing an int key from
// the STLport set<int> at this+0x80 (20-byte nodes): find (iterator returned
// through a hidden pointer, thunk 0x0000B221), and when it is not the header,
// rebalance the node out, free it and drop the count. No element destructor.
namespace _STL
{
struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	Value _M_value_field;
};

template <bool dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_Rebalance_for_erase(_Rb_tree_node_base *z, _Rb_tree_node_base *&root,
		_Rb_tree_node_base *&leftmost, _Rb_tree_node_base *&rightmost);
};

template <bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};

template <class Value>
struct _Rb_tree_iterator
{
	_Rb_tree_iterator() {}
	_Rb_tree_iterator(const _Rb_tree_iterator &other) : _M_node(other._M_node) {}
	_Rb_tree_node_base *_M_node;
};

template <class Key, class Value>
class _Rb_tree
{
public:
	typedef _Rb_tree_iterator<Value> iterator;
	typedef _Rb_tree_node<Value> _Node;
	iterator find(const Key &key);
	__forceinline unsigned int erase_unique(const Key &key)
	{
		iterator it = find(key);
		if (it._M_node != _M_header)
		{
			erase(it);
			return 1;
		}
		return 0;
	}
	__forceinline void erase(iterator position)
	{
		_Node *y = (_Node *)_Rb_global<true>::_Rebalance_for_erase(position._M_node,
			_M_header->_M_parent, _M_header->_M_left, _M_header->_M_right);
		if (y != 0)
			__node_alloc<true, 0>::_M_deallocate(y, sizeof(_Node));
		--_M_node_count;
	}
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
};
}

typedef _STL::_Rb_tree<int, int> Rva00769D00IntSet;

class Rva00769D00Owner
{
public:
	void eraseId(int id);
private:
	char m_head[0x80];
	Rva00769D00IntSet m_ids;
};

void Rva00769D00Owner::eraseId(int id)
{
	m_ids.erase_unique(id);
}
