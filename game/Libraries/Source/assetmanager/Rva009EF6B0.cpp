// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail RVA 0x009EF6B0, 30 bytes. See the boundary and ABI evidence in
// targets/game/reverse/identity_evidence/009ef6b0-construction.md.
// The owning type and the meanings of the trailing fields are unproven.

#include <set>

// Existing ABI view of the tree copy constructor at RVA 0x009EE8E0.
// Keep its address-qualified key type so the call resolves to that body.
struct Gen_t_009ee8e0_k4
{
    int a[1];
    Gen_t_009ee8e0_k4();
    Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
    ~Gen_t_009ee8e0_k4();
    Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

typedef _STL::_Rb_tree<Gen_t_009ee8e0_k4, Gen_t_009ee8e0_k4,
    _STL::_Identity<Gen_t_009ee8e0_k4>, _STL::less<Gen_t_009ee8e0_k4>,
    _STL::allocator<Gen_t_009ee8e0_k4> > Rva009EE8E0Tree;

struct Rva009EF6B0
{
    Rva009EE8E0Tree m_tree;
    unsigned int m_field0c;
    bool m_field10;

    explicit Rva009EF6B0(const Rva009EE8E0Tree &tree);
};

typedef char Rva009EF6B0TreeSize[sizeof(Rva009EE8E0Tree) == 12 ? 1 : -1];
typedef char Rva009EF6B0Size[sizeof(Rva009EF6B0) == 20 ? 1 : -1];

Rva009EF6B0::Rva009EF6B0(const Rva009EE8E0Tree &tree)
    : m_tree(tree), m_field0c(0), m_field10(true)
{
}
