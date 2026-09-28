// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <memory>
// Independent starts after INT3, RET 8 before INT3. The element identity is
// unknown; only the eight-byte allocation stride is witnessed by retail.
struct Rva009F4A40Element { unsigned words[2]; };
struct Rva009F4A40 { void *body(unsigned count, const void *hint); };
void *Rva009F4A40::body(unsigned count, const void *hint)
{
    _STL::allocator<Rva009F4A40Element> allocator;
    return allocator.allocate(count, hint);
}
struct Rva009F4A70 { void body(void *memory, unsigned count); };
void Rva009F4A70::body(void *memory, unsigned count)
{
    _STL::allocator<Rva009F4A40Element> allocator;
    allocator.deallocate((Rva009F4A40Element *)memory, count);
}
