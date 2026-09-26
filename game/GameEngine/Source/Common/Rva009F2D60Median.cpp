// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
struct Rva009F2D60Elem { int m_a; float m_key; bool operator<(const Rva009F2D60Elem& o) const { return m_key > o.m_key; } };
template const Rva009F2D60Elem& _STL::__median<Rva009F2D60Elem>(const Rva009F2D60Elem&, const Rva009F2D60Elem&, const Rva009F2D60Elem&);
