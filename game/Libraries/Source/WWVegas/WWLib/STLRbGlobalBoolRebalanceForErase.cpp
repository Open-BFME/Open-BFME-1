// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082CB60 is STLport's
//   _STL::_Rb_global<bool>::_Rebalance_for_erase(_Rb_tree_node_base*,
//                                                _Rb_tree_node_base*&, 
//                                                _Rb_tree_node_base*&, 
//                                                _Rb_tree_node_base*&)
// (?_Rebalance_for_erase@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@AAPAU32@11@Z).
// Keep the STLport node layout and source order: the neighbouring rotate
// helpers at 0x0082B970 and 0x0082BA00 are the same /Od build.

namespace _STL
{

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

  static _Base_ptr _S_minimum(_Base_ptr __x)
  {
    while (__x->_M_left != 0) __x = __x->_M_left;
    return __x;
  }

  static _Base_ptr _S_maximum(_Base_ptr __x)
  {
    while (__x->_M_right != 0) __x = __x->_M_right;
    return __x;
  }
};

template <class _Dummy> class _Rb_global
{
public:
  typedef _Rb_tree_node_base* _Base_ptr;

  static _Base_ptr _Rebalance_for_erase(_Rb_tree_node_base* __z,
                                        _Rb_tree_node_base*& __root,
                                        _Rb_tree_node_base*& __leftmost,
                                        _Rb_tree_node_base*& __rightmost);
  static void _Rotate_left(_Rb_tree_node_base* __x,
                           _Rb_tree_node_base*& __root);
  static void _Rotate_right(_Rb_tree_node_base* __x,
                            _Rb_tree_node_base*& __root);
};

template <class _Dummy>
typename _Rb_global<_Dummy>::_Base_ptr
_Rb_global<_Dummy>::_Rebalance_for_erase(_Rb_tree_node_base* __z,
                                         _Rb_tree_node_base*& __root,
                                         _Rb_tree_node_base*& __leftmost,
                                         _Rb_tree_node_base*& __rightmost)
{
  _Rb_tree_node_base* __y = __z;
  _Rb_tree_node_base* __x = 0;
  _Rb_tree_node_base* __x_parent = 0;
  if (__y->_M_left == 0)
    __x = __y->_M_right;
  else
    if (__y->_M_right == 0)
      __x = __y->_M_left;
    else {
      __y = __y->_M_right;
      while (__y->_M_left != 0)
        __y = __y->_M_left;
      __x = __y->_M_right;
    }
  {
  _Rb_tree_node_base* __w_right;
  _Rb_tree_node_base* __w_left;
  if (__y != __z) {
    __z->_M_left->_M_parent = __y;
    __y->_M_left = __z->_M_left;
    if (__y != __z->_M_right) {
      __x_parent = __y->_M_parent;
      if (__x) __x->_M_parent = __y->_M_parent;
      __y->_M_parent->_M_left = __x;
      __y->_M_right = __z->_M_right;
      __z->_M_right->_M_parent = __y;
    }
    else
      __x_parent = __y;
    if (__root == __z)
      __root = __y;
    else if (__z->_M_parent->_M_left == __z)
      __z->_M_parent->_M_left = __y;
    else
      __z->_M_parent->_M_right = __y;
    __y->_M_parent = __z->_M_parent;
    _Rb_tree_Color_type __color = __y->_M_color;
    __y->_M_color = __z->_M_color;
    __z->_M_color = __color;
    __y = __z;
  }
  else {
    __x_parent = __y->_M_parent;
    if (__x) __x->_M_parent = __y->_M_parent;
    if (__root == __z)
      __root = __x;
    else
      if (__z->_M_parent->_M_left == __z)
        __z->_M_parent->_M_left = __x;
      else
        __z->_M_parent->_M_right = __x;
    if (__leftmost == __z)
      if (__z->_M_right == 0)
        __leftmost = __z->_M_parent;
      else
        __leftmost = _Rb_tree_node_base::_S_minimum(__x);
    if (__rightmost == __z)
      if (__z->_M_left == 0)
        __rightmost = __z->_M_parent;
      else
        __rightmost = _Rb_tree_node_base::_S_maximum(__x);
  }
  if (__y->_M_color != _S_rb_tree_red) {
    while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
      if (__x == __x_parent->_M_left) {
        __w_right = __x_parent->_M_right;
        if (__w_right->_M_color == _S_rb_tree_red) {
          __w_right->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rotate_left(__x_parent, __root);
          __w_right = __x_parent->_M_right;
        }
        if ((__w_right->_M_left == 0 ||
             __w_right->_M_left->_M_color == _S_rb_tree_black) &&
            (__w_right->_M_right == 0 ||
             __w_right->_M_right->_M_color == _S_rb_tree_black)) {
          __w_right->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        }
        else {
          if (__w_right->_M_right == 0 ||
              __w_right->_M_right->_M_color == _S_rb_tree_black) {
            if (__w_right->_M_left)
              __w_right->_M_left->_M_color = _S_rb_tree_black;
            __w_right->_M_color = _S_rb_tree_red;
            _Rotate_right(__w_right, __root);
            __w_right = __x_parent->_M_right;
          }
          __w_right->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w_right->_M_right)
            __w_right->_M_right->_M_color = _S_rb_tree_black;
          _Rotate_left(__x_parent, __root);
          break;
        }
      }
      else {
        __w_left = __x_parent->_M_left;
        if (__w_left->_M_color == _S_rb_tree_red) {
          __w_left->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rotate_right(__x_parent, __root);
          __w_left = __x_parent->_M_left;
        }
        if ((__w_left->_M_right == 0 ||
             __w_left->_M_right->_M_color == _S_rb_tree_black) &&
            (__w_left->_M_left == 0 ||
             __w_left->_M_left->_M_color == _S_rb_tree_black)) {
          __w_left->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        }
        else {
          if (__w_left->_M_left == 0 ||
              __w_left->_M_left->_M_color == _S_rb_tree_black) {
            if (__w_left->_M_right)
              __w_left->_M_right->_M_color = _S_rb_tree_black;
            __w_left->_M_color = _S_rb_tree_red;
            _Rotate_left(__w_left, __root);
            __w_left = __x_parent->_M_left;
          }
          __w_left->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w_left->_M_left)
            __w_left->_M_left->_M_color = _S_rb_tree_black;
          _Rotate_right(__x_parent, __root);
          break;
        }
      }
    if (__x) __x->_M_color = _S_rb_tree_black;
  }
  }
  return __y;
}

template _STL::_Rb_tree_node_base* __cdecl
_STL::_Rb_global<bool>::_Rebalance_for_erase(
  _STL::_Rb_tree_node_base*, _STL::_Rb_tree_node_base*&,
  _STL::_Rb_tree_node_base*&, _STL::_Rb_tree_node_base*&);

}
