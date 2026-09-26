// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082BB70 is STLport's
//   _STL::_Sl_global<bool>::__splice_after(_Slist_node_base*,
//                                          _Slist_node_base*,
//                                          _Slist_node_base*)
// (?__splice_after@?$_Sl_global@_N@_STL@@SAXPAU_Slist_node_base@2@00@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_slist_base.c; it is
// emitted under the object symbol the ledger pins for this row.
//
// Retail built the STLport slist helpers unoptimised, hence /Od above:
// __first and __after live on the stack ([ebp-4], [ebp-8]).

namespace _STL {

struct _Slist_node_base
{
  _Slist_node_base* _M_next;
};

}

extern "C" void __cdecl
bfme_SlGlobalBoolSpliceAfter3_82BB70(_STL::_Slist_node_base* __pos,
                                     _STL::_Slist_node_base* __before_first,
                                     _STL::_Slist_node_base* __before_last)
{
  if (__pos != __before_first && __pos != __before_last) {
    _STL::_Slist_node_base* __first = __before_first->_M_next;
    _STL::_Slist_node_base* __after = __pos->_M_next;
    __before_first->_M_next = __before_last->_M_next;
    __pos->_M_next = __first;
    __before_last->_M_next = __after;
  }
}
