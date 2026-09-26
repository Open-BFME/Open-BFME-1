// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail's 210-byte initializer divides capacity by six and allocates nodes
// of 120 bytes: these are 20-byte elements, not MapObject pointers or GameSpy
// request/response objects. The matched ShroudManagerImpl ctor at 0x008FB960
// calls this initializer for its 20-byte shroud-record deque.
// Its two constructor wrappers are the complete 76B/46B bodies at
// 0x008FA9A0/0x008FAE70. Original payload type spelling is not recovered.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>
struct Rva008FA2B0Element { unsigned char payload[20]; };
template class _STL::_Deque_base<Rva008FA2B0Element, _STL::allocator<Rva008FA2B0Element> >;

template class _STL::deque<Rva008FA2B0Element, _STL::allocator<Rva008FA2B0Element> >;
