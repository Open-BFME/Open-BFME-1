// cl: /DNDEBUG /MD /EHs-c-

namespace _STL
{

template <class Type> class allocator {};
template <class First, class Second> struct pair {};
template <class Pair> struct _Select1st {};
template <class Type> struct less {};

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

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	void clear()
	{
		if (_M_node_count != 0)
		{
			_M_erase((_Node *)(void *)_M_root());
			_M_leftmost() = _M_header;
			_M_root() = 0;
			_M_rightmost() = _M_header;
			_M_node_count = 0;
		}
	}

private:
	typedef _Rb_tree_node<Value> _Node;
	_Rb_tree_node_base *&_M_root() const { return _M_header->_M_parent; }
	_Rb_tree_node_base *&_M_leftmost() const { return _M_header->_M_left; }
	_Rb_tree_node_base *&_M_rightmost() const { return _M_header->_M_right; }
	void _M_erase(_Node *x);
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	Compare _M_key_compare;
};

}

struct Gen_t_0019ad70_p12cd { int a[3]; };
struct Gen_t_0019e300_p12cd { int a[3]; };
typedef _STL::pair<const int, Gen_t_0019ad70_p12cd> PairA;
typedef _STL::pair<const int, Gen_t_0019e300_p12cd> PairB;

typedef _STL::_Rb_tree<int, PairA, _STL::_Select1st<PairA>, _STL::less<int>, _STL::allocator<PairA> > TreeA;
typedef _STL::_Rb_tree<int, PairB, _STL::_Select1st<PairB>, _STL::less<int>, _STL::allocator<PairB> > TreeB;

class Rva0019E800Owner
{
public:
	void clear(void);

private:
	char m_head[0x10];
	TreeA m_first;
	TreeB m_second;
};

void Rva0019E800Owner::clear(void)
{
	m_first.clear();
	m_second.clear();
}
