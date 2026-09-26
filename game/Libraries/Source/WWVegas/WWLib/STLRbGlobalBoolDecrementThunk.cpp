// cl: /DNDEBUG /MD /EHsc /Od

// _STL::_Rb_global<bool>::_M_decrement — STLport's red-black tree iterator
// decrement helper, verbatim from inputs/vendor/stlport/stl/_tree.c.  Retail built the
// STLport tree helpers unoptimised (frame pointer kept, both locals spilled),
// hence the /Od above.
//
// The row pins object-symbol=_bfme_RbGlobalBoolDecrement_82B8E0, so the body
// carries that extern "C" name; the shape below is the real template member.

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

}

extern "C" _STL::_Rb_tree_node_base* __cdecl
bfme_RbGlobalBoolDecrement_82B8E0(_STL::_Rb_tree_node_base* _M_node)
{
  typedef _STL::_Rb_tree_node_base* _Base_ptr;

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
