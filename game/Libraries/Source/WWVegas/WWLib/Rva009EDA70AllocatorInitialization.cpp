// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA009EDA70 is 35 bytes through RET4 at +0x20, bounded by INT3.
// The first call, RVA009ED490, takes an ignored reference and one dword,
// stores the dword at this+0, returns this in EAX, and ends in RET8.
// Neither address proves an allocator/node template specialization.
// Keep address-derived ABI views; native allocator<Rva009EDA70Node>
// supplies the separately named retail pool allocation of 0x18 bytes.
// An explicit empty constructor preserves the uninitialized empty-object
// temporary; aggregate value initialization would add a zero-byte store.
#include <memory>
struct Rva009EDA70Allocator { Rva009EDA70Allocator() {} };
class Rva009ED490Proxy {
protected:
    unsigned m_value;
public:
    Rva009ED490Proxy(const Rva009EDA70Allocator &, unsigned);
};
struct Rva009EDA70Node { unsigned char bytes[0x18]; };
class Rva009EDA70Owner : public Rva009ED490Proxy {
public:
    Rva009EDA70Owner(const Rva009EDA70Allocator &);
};
Rva009EDA70Owner::Rva009EDA70Owner(const Rva009EDA70Allocator &)
    : Rva009ED490Proxy(Rva009EDA70Allocator(), 0)
{
    m_value = (unsigned)_STL::allocator<Rva009EDA70Node>().allocate(1);
}
