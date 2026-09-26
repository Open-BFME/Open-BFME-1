// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082BA90 is STLport's
//   _STL::_List_global<bool>::_Transfer(_List_node_base*, _List_node_base*, _List_node_base*)
// (?_Transfer@?$_List_global@_N@_STL@@SAXPAU_List_node_base@2@00@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_list.c; it is emitted under
// the object symbol the ledger pins for this row.
//
// Retail built the STLport list helper unoptimised, hence /Od above: __tmp lives
// on the stack ([ebp-4]) rather than in a register.

namespace _STL {

struct _List_node_base
{
  _List_node_base* _M_next;
  _List_node_base* _M_prev;
};

}

extern "C" void __cdecl
bfme_ListGlobalBoolTransfer_82BA90(_STL::_List_node_base* __position,
                                    _STL::_List_node_base* __first,
                                    _STL::_List_node_base* __last)
{
  using _STL::_List_node_base;

  if (__position != __last) {
    // Remove [first, last) from its old position.
    __last->_M_prev->_M_next = __position;
    __first->_M_prev->_M_next = __last;
    __position->_M_prev->_M_next = __first;

    // Splice [first, last) into its new position.
    _List_node_base* __tmp = __position->_M_prev;
    __position->_M_prev = __last->_M_prev;
    __last->_M_prev = __first->_M_prev;
    __first->_M_prev = __tmp;
  }
}
