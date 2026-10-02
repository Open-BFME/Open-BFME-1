// cl: /O2 /Ob0 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00C6DCF0 initializes the singleton at VA 0x0133F468 and registers
// its matched 0x00C70FC0 cleanup wrapper. The 0x009009B0 constructor allocates
// a 32-byte red-black tree sentinel and initializes an empty two-word tree.
// Gen_p12cd preserves the existing anonymous template payload identity;
// the singleton's application-level identity is not established.
#include <map>
#include <new>

struct Gen_p12cd
{
    int a[3];
    Gen_p12cd();
    Gen_p12cd(const Gen_p12cd &);
    ~Gen_p12cd();
    Gen_p12cd &operator=(const Gen_p12cd &);
};

typedef _STL::pair<const int, Gen_p12cd> Rva00C6DCF0Pair;
typedef _STL::_Rb_tree<int, Rva00C6DCF0Pair,
    _STL::_Select1st<Rva00C6DCF0Pair>, _STL::less<int>,
    _STL::allocator<Rva00C6DCF0Pair> > Rva00C6DCF0Tree;

class BfmeList1016;
extern BfmeList1016 g_bfmeList1016;
void bfmeForward_00C70FC0();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void rva00C6DCF0Initialize()
{
    ((Rva00C6DCF0Tree *)&g_bfmeList1016)->Rva00C6DCF0Tree::_Rb_tree();
    atexit(bfmeForward_00C70FC0);
}
