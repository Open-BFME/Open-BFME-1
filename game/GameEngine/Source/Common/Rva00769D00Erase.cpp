// ?eraseId@Rva00769D00Owner@@QAEXH@Z
// Open-BFME7: 0x00769D00 (79 B), a wrapper erasing an int key from the
// STLport set<int> at this+0x80. The find helper returns its iterator through
// a hidden pointer, and the tree node uses the 20-byte allocator shape.
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

template <class T>
struct _Identity
{
	const T &operator()(const T &value) const { return value; }
};

template <class T>
struct less
{
	bool operator()(const T &left, const T &right) const;
};

template <class T>
class allocator
{
};

template <class T>
struct _Nonconst_traits
{
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};

template <class T, class Alloc>
struct _Rb_tree_base
{
	typedef _Rb_tree_node<T> _Node;
	_STLP_alloc_proxy<_Node *, _Node, allocator<_Node> > _M_header;
};

template <class dummy>
struct _Rb_global
{
	static _Rb_tree_node_base *_Rebalance_for_erase(_Rb_tree_node_base *z, _Rb_tree_node_base *&root,
		_Rb_tree_node_base *&leftmost, _Rb_tree_node_base *&rightmost);
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

template <class Value, class Traits>
struct _Rb_tree_iterator
{
	_Rb_tree_iterator() {}
	_Rb_tree_iterator(const _Rb_tree_iterator &other) : _M_node(other._M_node) {}
	_Rb_tree_node_base *_M_node;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree : public _Rb_tree_base<Value, Alloc>
{
public:
	typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;
	template <class SearchKey>
	iterator find(const SearchKey &key);
	__forceinline void erase(iterator position)
	{
		_Rb_tree_node_base *y = _Rb_global<bool>::_Rebalance_for_erase((_Rb_tree_node_base *)position._M_node,
			_M_header._M_data->_M_parent, _M_header._M_data->_M_left, _M_header._M_data->_M_right);
		if (y != 0)
			_STL::nodePoolDeallocate(y, sizeof(_Rb_tree_node<Value>));
		--_M_node_count;
	}
	unsigned int _M_node_count;
};
}

typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > Rva00769D00IntSet;

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
	Rva00769D00IntSet::iterator it = m_ids.find(id);
	if (it._M_node != m_ids._M_header._M_data)
		m_ids.erase(it);
}
