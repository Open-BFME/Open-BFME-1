// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082BB20 is STLport's
//   _STL::_Sl_global<bool>::__reverse(_Slist_node_base*)
// (?__reverse@?$_Sl_global@_N@_STL@@SAPAU_Slist_node_base@2@PAU32@@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_slist_base.c; it is defined
// under its real name.
//
// Retail built the STLport slist helpers unoptimised, hence /Od above: __result
// and __next live on the stack ([ebp-4], [ebp-8]) rather than in registers.

namespace _STL {

struct _Slist_node_base
{
  _Slist_node_base* _M_next;
};

template <class _Dummy>
class _Sl_global
{
public:
  static _Slist_node_base* __cdecl __reverse(_Slist_node_base*);
};

template <class _Dummy>
_Slist_node_base* __cdecl
_Sl_global<_Dummy>::__reverse(_Slist_node_base* __node)
{
  _Slist_node_base* __result = __node;
  __node = __node->_M_next;
  __result->_M_next = 0;
  while(__node) {
    _Slist_node_base* __next = __node->_M_next;
    __node->_M_next = __result;
    __result = __node;
    __node = __next;
  }
  return __result;
}

template class _Sl_global<bool>;

}
