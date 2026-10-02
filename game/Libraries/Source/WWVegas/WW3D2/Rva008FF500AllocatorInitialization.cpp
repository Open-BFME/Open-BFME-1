// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA008FF500 is 35 bytes through RET4 at +0x20, bounded by INT3.
// The first call, RVA008FEE70, takes an ignored reference and one dword,
// stores the dword at this+0, returns this in EAX, and ends in RET8.
// Neither address proves an allocator/node template specialization.
// Keep address-derived ABI views; native allocator<Rva008FF500Node>
// supplies the separately named retail pool allocation of 0x20 bytes.
// An explicit empty constructor preserves the uninitialized empty-object
// temporary; aggregate value initialization would add a zero-byte store.
#include <memory>
struct Rva008FF500Allocator { Rva008FF500Allocator() {} };
class Rva008FEE70Proxy {
protected:
    unsigned m_value;
public:
    Rva008FEE70Proxy(const Rva008FF500Allocator &, unsigned);
};
struct Rva008FF500Node { unsigned char bytes[0x20]; };
class Rva008FF500Owner : public Rva008FEE70Proxy {
public:
    Rva008FF500Owner(const Rva008FF500Allocator &);
};
Rva008FF500Owner::Rva008FF500Owner(const Rva008FF500Allocator &)
    : Rva008FEE70Proxy(Rva008FF500Allocator(), 0)
{
    m_value = (unsigned)_STL::allocator<Rva008FF500Node>().allocate(1);
}
