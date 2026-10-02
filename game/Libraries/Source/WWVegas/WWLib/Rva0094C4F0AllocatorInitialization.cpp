// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA0094C4F0 is 35 bytes through RET4 at +0x20, bounded by INT3.
// The first call, RVA0094C200, takes an ignored reference and one dword,
// stores the dword at this+0, returns this in EAX, and ends in RET8.
// Neither address proves an allocator/node template specialization.
// Keep address-derived ABI views; native allocator<Rva0094C4F0Node>
// supplies the separately named retail pool allocation of 0x18 bytes.
// An explicit empty constructor preserves the uninitialized empty-object
// temporary; aggregate value initialization would add a zero-byte store.
#include <memory>
struct Rva0094C4F0Allocator { Rva0094C4F0Allocator() {} };
class Rva0094C200Proxy {
protected:
    unsigned m_value;
public:
    Rva0094C200Proxy(const Rva0094C4F0Allocator &, unsigned);
};
struct Rva0094C4F0Node { unsigned char bytes[0x18]; };
class Rva0094C4F0Owner : public Rva0094C200Proxy {
public:
    Rva0094C4F0Owner(const Rva0094C4F0Allocator &);
};
Rva0094C4F0Owner::Rva0094C4F0Owner(const Rva0094C4F0Allocator &)
    : Rva0094C200Proxy(Rva0094C4F0Allocator(), 0)
{
    m_value = (unsigned)_STL::allocator<Rva0094C4F0Node>().allocate(1);
}
