// ?_M_decrement@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z
// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082B8E0 is STLport's _STL::_Rb_global<bool>::_M_decrement, the
// red-black tree iterator decrement helper, verbatim from
// inputs/vendor/stlport/stl/_tree.c and defined under its real name. Retail built
// the STLport tree helpers unoptimised (frame pointer kept, both locals spilled),
// hence the /Od above.

namespace _STL {

typedef bool _Rb_tree_Color_type;

#define _S_rb_tree_red false
#define _S_rb_tree_black true

struct _Rb_tree_node_base
{
  typedef _Rb_tree_Color_type _Color_type;
  typedef _Rb_tree_node_base* _Base_ptr;

  _Color_type _M_color;
  _Base_ptr _M_parent;
  _Base_ptr _M_left;
  _Base_ptr _M_right;
};

typedef _Rb_tree_node_base* _Base_ptr;

template <class _Dummy>
class _Rb_global
{
public:
  static _Rb_tree_node_base* __cdecl _M_decrement(_Rb_tree_node_base*);
};

template <class _Dummy>
_Rb_tree_node_base* __cdecl
_Rb_global<_Dummy>::_M_decrement(_Rb_tree_node_base* _M_node)
{
  if (_M_node->_M_color == _S_rb_tree_red && _M_node->_M_parent->_M_parent == _M_node)
    _M_node = _M_node->_M_right;
  else if (_M_node->_M_left != 0) {
    _Base_ptr __y = _M_node->_M_left;
    while (__y->_M_right != 0)
      __y = __y->_M_right;
    _M_node = __y;
  }
  else {
    _Base_ptr __y = _M_node->_M_parent;
    while (_M_node == __y->_M_left) {
      _M_node = __y;
      __y = __y->_M_parent;
    }
    _M_node = __y;
  }
  return _M_node;
}

template class _Rb_global<bool>;

}
