// cl: /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stringinline
// stlport
// The carved body at retail RVA 0x000FAA30 has the STLport vector-copy shape
// with 96-byte elements. Its caller and neighboring vector bodies prove the
// storage width, while the body itself does not prove a semantic owner.

#include <vector>

struct Rva000FAA30Elem
{
    Rva000FAA30Elem();
    Rva000FAA30Elem(const Rva000FAA30Elem &other);

    char m_body[0x60];
};

extern void j_0002013a();
extern void j_0001b9d7();
extern void j_0004845f();
#pragma comment(linker, "/alternatename:??0?$_Vector_base@URva000FAA30Elem@@V?$allocator@URva000FAA30Elem@@@_STL@@@_STL@@QAE@IABV?$allocator@URva000FAA30Elem@@@1@@Z=?j_0001b9d7@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva000FAA30Elem@@QAE@ABU0@@Z=?j_0004845f@@YAXXZ")
#pragma comment(linker, "/alternatename:?get_allocator@?$vector@URva000FAA30Elem@@V?$allocator@URva000FAA30Elem@@@_STL@@@_STL@@QBE?AV?$allocator@URva000FAA30Elem@@@2@XZ=?j_0002013a@@YAXXZ")

template class _STL::vector<Rva000FAA30Elem>;
