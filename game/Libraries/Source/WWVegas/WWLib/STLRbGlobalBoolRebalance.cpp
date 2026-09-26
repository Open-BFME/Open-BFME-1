// ?_Rebalance@?$_Rb_global@_N@_STL@@SAXPAU_Rb_tree_node_base@2@AAPAU32@@Z
// cl: /DNDEBUG /MD /EHsc /Od

namespace _STL
{

typedef bool _Rb_tree_Color_type;

#define _S_rb_tree_red false
#define _S_rb_tree_black true

struct _Rb_tree_node_base
{
	_Rb_tree_Color_type _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class Dummy>
class _Rb_global
{
public:
	static void __cdecl _Rebalance(_Rb_tree_node_base *x,
		_Rb_tree_node_base *&root);
	static void __cdecl _Rotate_left(_Rb_tree_node_base *x,
		_Rb_tree_node_base *&root);
	static void __cdecl _Rotate_right(_Rb_tree_node_base *x,
		_Rb_tree_node_base *&root);
};

template <class Dummy>
void __cdecl _Rb_global<Dummy>::_Rebalance(_Rb_tree_node_base *x,
	_Rb_tree_node_base *&root)
{
	x->_M_color = _S_rb_tree_red;
	while (x != root && x->_M_parent->_M_color == _S_rb_tree_red)
	{
		if (x->_M_parent == x->_M_parent->_M_parent->_M_left)
		{
			_Rb_tree_node_base *y = x->_M_parent->_M_parent->_M_right;
			if (y && y->_M_color == _S_rb_tree_red)
			{
				x->_M_parent->_M_color = _S_rb_tree_black;
				y->_M_color = _S_rb_tree_black;
				x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				x = x->_M_parent->_M_parent;
			}
			else
			{
				if (x == x->_M_parent->_M_right)
				{
					x = x->_M_parent;
					_Rotate_left(x, root);
				}
				x->_M_parent->_M_color = _S_rb_tree_black;
				x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				_Rotate_right(x->_M_parent->_M_parent, root);
			}
		}
		else
		{
			_Rb_tree_node_base *y = x->_M_parent->_M_parent->_M_left;
			if (y && y->_M_color == _S_rb_tree_red)
			{
				x->_M_parent->_M_color = _S_rb_tree_black;
				y->_M_color = _S_rb_tree_black;
				x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				x = x->_M_parent->_M_parent;
			}
			else
			{
				if (x == x->_M_parent->_M_left)
				{
					x = x->_M_parent;
					_Rotate_right(x, root);
				}
				x->_M_parent->_M_color = _S_rb_tree_black;
				x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
				_Rotate_left(x->_M_parent->_M_parent, root);
			}
		}
	}
	root->_M_color = _S_rb_tree_black;
}

template void __cdecl
_STL::_Rb_global<bool>::_Rebalance(_STL::_Rb_tree_node_base *,
	_STL::_Rb_tree_node_base *&);

}
