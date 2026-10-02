// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA0093E140 is 35 bytes through RET4 at +0x20, bounded by INT3.
// The first call, RVA0093D500, takes an ignored reference and one dword,
// stores the dword at this+0, returns this in EAX, and ends in RET8.
// Neither address proves an allocator/node template specialization.
// Keep address-derived ABI views; native allocator<Rva0093E140Node>
// supplies the separately named retail pool allocation of 0x18 bytes.
// An explicit empty constructor preserves the uninitialized empty-object
// temporary; aggregate value initialization would add a zero-byte store.
#include <memory>
struct Rva0093E140Allocator { Rva0093E140Allocator() {} };
class Rva0093D500Proxy {
protected:
    unsigned m_value;
public:
    Rva0093D500Proxy(const Rva0093E140Allocator &, unsigned);
};
struct Rva0093E140Node { unsigned char bytes[0x18]; };
class Rva0093E140Owner : public Rva0093D500Proxy {
public:
    Rva0093E140Owner(const Rva0093E140Allocator &);
};
Rva0093E140Owner::Rva0093E140Owner(const Rva0093E140Allocator &)
    : Rva0093D500Proxy(Rva0093E140Allocator(), 0)
{
    m_value = (unsigned)_STL::allocator<Rva0093E140Node>().allocate(1);
}
