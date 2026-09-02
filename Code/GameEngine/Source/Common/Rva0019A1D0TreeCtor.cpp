// cl: /DNDEBUG /MD /EHsc

namespace _STL
{

template <class Type> class allocator {};
template <class First, class Second> struct pair {};
template <class Pair> struct _Select1st {};
template <class Type> struct less {};

struct _Rb_tree_node_base
{
	char _M_color;
	char _M_pad[3];
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	_Rb_tree()
	{
		_M_header = 0;
		_M_header = (_Rb_tree_node_base *)__new_alloc::allocate(0x1C);
		_M_node_count = 0;
		_M_header->_M_color = 0;
		_M_header->_M_parent = 0;
		_M_header->_M_left = _M_header;
		_M_header->_M_right = _M_header;
	}
	~_Rb_tree();

	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
	Compare _M_key_compare;
};

}

class Rva0019A1D0Member
{
public:
	Rva0019A1D0Member(int);

private:
	char m_body[12];
};

class Rva0019A1D0Owner
{
public:
	Rva0019A1D0Owner();

private:
	_STL::_Rb_tree<int, int, _STL::_Select1st<int>, _STL::less<int>, _STL::allocator<int> > m_tree;
	Rva0019A1D0Member m_member;
	short m_a;
	short m_b;
};

Rva0019A1D0Owner::Rva0019A1D0Owner()
	: m_member(1)
{
	m_a = 0;
	m_b = 0;
}
