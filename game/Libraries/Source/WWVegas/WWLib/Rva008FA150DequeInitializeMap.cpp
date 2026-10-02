// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// The ledger uses an opaque address-owned alias for this emission view.
// Retail elements occupy eight bytes; the old PartitionCell* identity is false.
// See identity_evidence/008fa150-eight-byte-deque.md.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>
struct Rva008FA150Element { unsigned char m_unmodelled00[8]; };
namespace _STL {
template void _Deque_base<Rva008FA150Element,
    allocator<Rva008FA150Element> >::_M_initialize_map(unsigned int);
}
