// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <memory>

// The retail body frees a three-pointer vector base of eight-byte elements.
struct Rva009F5280VectorBuffer
{
    struct Entry { void *first; void *second; };
    Entry *begin;
    Entry *finish;
    Entry *end;
    ~Rva009F5280VectorBuffer();
};

Rva009F5280VectorBuffer::~Rva009F5280VectorBuffer()
{
    if (begin) {
        _STL::__node_alloc<true, 0>::deallocate(begin,
            (end - begin) * sizeof(Entry));
    }
}
