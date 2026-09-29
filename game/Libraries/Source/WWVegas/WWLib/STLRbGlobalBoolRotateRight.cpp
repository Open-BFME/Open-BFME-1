// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082BA00 is STLport's
//   _STL::_Rb_global<bool>::_Rotate_right(_Rb_tree_node_base*,
//                                         _Rb_tree_node_base*&)
// (?_Rotate_right@?$_Rb_global@_N@_STL@@SAXPAU_Rb_tree_node_base@2@AAPAU32@@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_tree.c; it is defined
// under its real name.
//
// Retail built the STLport tree helpers unoptimised, hence /Od above: __y
// lives on the stack ([ebp-4]) rather than in a register.

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

template <class _Dummy>
class _Rb_global
{
public:
  static void __cdecl _Rotate_right(_Rb_tree_node_base*, _Rb_tree_node_base*&);
};

template <class _Dummy>
void __cdecl
_Rb_global<_Dummy>::_Rotate_right(_Rb_tree_node_base* __x,
                                  _Rb_tree_node_base*& __root)
{
  _Rb_tree_node_base* __y = __x->_M_left;
  __x->_M_left = __y->_M_right;
  if (__y->_M_right != 0)
    __y->_M_right->_M_parent = __x;
  __y->_M_parent = __x->_M_parent;

  if (__x == __root)
    __root = __y;
  else if (__x == __x->_M_parent->_M_right)
    __x->_M_parent->_M_right = __y;
  else
    __x->_M_parent->_M_left = __y;
  __y->_M_right = __x;
  __x->_M_parent = __y;
}

template class _Rb_global<bool>;

}
