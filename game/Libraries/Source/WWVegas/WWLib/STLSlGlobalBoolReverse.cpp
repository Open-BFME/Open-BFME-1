// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082BB20 is STLport's
//   _STL::_Sl_global<bool>::__reverse(_Slist_node_base*)
// (?__reverse@?$_Sl_global@_N@_STL@@SAPAU_Slist_node_base@2@PAU32@@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_slist_base.c; it is emitted
// under the object symbol the ledger pins for this row.
//
// Retail built the STLport slist helpers unoptimised, hence /Od above: __result
// and __next live on the stack ([ebp-4], [ebp-8]) rather than in registers.

namespace _STL {

struct _Slist_node_base
{
  _Slist_node_base* _M_next;
};

}

extern "C" _STL::_Slist_node_base* __cdecl
bfme_SlGlobalBoolReverse_82BB20(_STL::_Slist_node_base* __node)
{
  _STL::_Slist_node_base* __result = __node;
  __node = __node->_M_next;
  __result->_M_next = 0;
  while(__node) {
    _STL::_Slist_node_base* __next = __node->_M_next;
    __node->_M_next = __result;
    __result = __node;
    __node = __next;
  }
  return __result;
}
