// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail RVA009A3880 is 35 bytes through RET4 at +0x20, bounded by INT3.
// The first call, RVA009A3440, takes an ignored reference and one dword,
// stores the dword at this+0, returns this in EAX, and ends in RET8.
// Neither address proves an allocator/node template specialization.
// Keep address-derived ABI views; native allocator<Rva009A3880Node>
// supplies the separately named retail pool allocation of 0x18 bytes.
// An explicit empty constructor preserves the uninitialized empty-object
// temporary; aggregate value initialization would add a zero-byte store.
#include <memory>
struct Rva009A3880Allocator { Rva009A3880Allocator() {} };
class Rva009A3440Proxy {
protected:
    unsigned m_value;
public:
    Rva009A3440Proxy(const Rva009A3880Allocator &, unsigned);
};
struct Rva009A3880Node { unsigned char bytes[0x18]; };
class Rva009A3880Owner : public Rva009A3440Proxy {
public:
    Rva009A3880Owner(const Rva009A3880Allocator &);
};
Rva009A3880Owner::Rva009A3880Owner(const Rva009A3880Allocator &)
    : Rva009A3440Proxy(Rva009A3880Allocator(), 0)
{
    m_value = (unsigned)_STL::allocator<Rva009A3880Node>().allocate(1);
}
