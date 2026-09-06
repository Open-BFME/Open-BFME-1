// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x006ABC00. The bytes are an STLport _Rb_tree::clear() of the
// int -> _SBServer* map at +0x1B8, so the class is named for the one member
// the body proves it owns and the method keeps the name of what it does.
//
// This is NOT PeerThreadClass::clearServers -- that name was recorded and then
// retracted (reverse/re_attempts.log), because addServerToMap puts
// m_stagingServers at +0x20C and the PeerThread.cpp compiland does not contain
// this address. The file used to carry the retracted name; nothing in the
// image names the real owner, so the name here describes the body only.

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

struct _SBServer;
typedef _STL::pair<const int, _SBServer *> SBServerPair;

typedef _STL::_Rb_tree<int,
	SBServerPair,
	_STL::_Select1st<SBServerPair>,
	_STL::less<int>,
	_STL::allocator<SBServerPair> > SBServerMapTree;

class SBServerMapOwner
{
public:
	void clear( void );

private:
	char m_head[0x1B8];
	SBServerMapTree m_map;			// @0x1B8
};

void SBServerMapOwner::clear( void )
{
	m_map.clear();
}
