// ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z
// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082B870 is STLport's _STL::_Rb_global<bool>::_M_increment. The body is
// verbatim from inputs/vendor/stlport/stl/_tree.c, defined under its real name so
// every TU that walks a map/set links against it.
//
// Retail built the STLport tree helpers unoptimised, hence /Od above: every load
// of _M_node comes straight back off the stack slot, and __y lives in [ebp-4].

namespace _STL {

typedef bool _Rb_tree_Color_type;

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
  static _Rb_tree_node_base* __cdecl _M_increment(_Rb_tree_node_base*);
};

template <class _Dummy>
_Rb_tree_node_base* __cdecl
_Rb_global<_Dummy>::_M_increment(_Rb_tree_node_base* _M_node)
{
  if (_M_node->_M_right != 0) {
    _M_node = _M_node->_M_right;
    while (_M_node->_M_left != 0)
      _M_node = _M_node->_M_left;
  }
  else {
    _Base_ptr __y = _M_node->_M_parent;
    while (_M_node == __y->_M_right) {
      _M_node = __y;
      __y = __y->_M_parent;
    }
    // check special case: This is necessary if _M_node is the _M_head and
    // the tree contains only a single node __y. In that case parent, left
    // and right all point to __y!
    if (_M_node->_M_right != __y)
      _M_node = __y;
  }
  return _M_node;
}

template class _Rb_global<bool>;

}
