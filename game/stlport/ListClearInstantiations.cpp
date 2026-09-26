// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Exact STLport 4.5.3 list clear instantiations.  The synthetic payload names
// encode only the element width proven by the retail node deallocation size;
// their destructor pins preserve the concrete call targets without claiming
// an unproven game-class identity.

#include <list>

#define BFME_LIST_CLEAR(TAG, WIDTH)                                      \
    struct Z1Elem##TAG                                                   \
    {                                                                    \
        ~Z1Elem##TAG();                                                  \
        char m_pad[WIDTH];                                               \
    };                                                                   \
    template void _STL::_List_base<Z1Elem##TAG,                          \
        _STL::allocator<Z1Elem##TAG> >::clear();

BFME_LIST_CLEAR(00129220, 0x1C)
BFME_LIST_CLEAR(0013BF00, 0x24)
BFME_LIST_CLEAR(0056D960, 0x3C)
BFME_LIST_CLEAR(0076AE50, 0x14)

// The destructor at 0x0056E160 calls the 0x0056D960 clear() above and then
// hands the head node back to the node allocator at the 0x44 width that
// element proves, so it is this same instantiation's ~_List_base.  Destroying
// one through a helper is what instantiates it; the helper itself is absent
// from retail.
void z1Destroy0056D960(
	_STL::_List_base<Z1Elem0056D960, _STL::allocator<Z1Elem0056D960> > *base)
{
	base->~_List_base();
}
