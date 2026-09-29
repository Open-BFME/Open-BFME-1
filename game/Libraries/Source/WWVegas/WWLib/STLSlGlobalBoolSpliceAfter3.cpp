// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082BB70 is STLport's
//   _STL::_Sl_global<bool>::__splice_after(_Slist_node_base*,
//                                          _Slist_node_base*,
//                                          _Slist_node_base*)
// (?__splice_after@?$_Sl_global@_N@_STL@@SAXPAU_Slist_node_base@2@00@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_slist_base.c; it is
// defined under its real name.
//
// Retail built the STLport slist helpers unoptimised, hence /Od above:
// __first and __after live on the stack ([ebp-4], [ebp-8]).

namespace _STL {

struct _Slist_node_base
{
  _Slist_node_base* _M_next;
};

template <class _Dummy>
class _Sl_global
{
public:
  static void __cdecl __splice_after(_Slist_node_base*, _Slist_node_base*, _Slist_node_base*);
};

template <class _Dummy>
void __cdecl
_Sl_global<_Dummy>::__splice_after(_Slist_node_base* __pos,
                                   _Slist_node_base* __before_first,
                                   _Slist_node_base* __before_last)
{
  if (__pos != __before_first && __pos != __before_last) {
    _Slist_node_base* __first = __before_first->_M_next;
    _Slist_node_base* __after = __pos->_M_next;
    __before_first->_M_next = __before_last->_M_next;
    __pos->_M_next = __first;
    __before_last->_M_next = __after;
  }
}

template class _Sl_global<bool>;

}
