// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// Retail 0x0093E820 is the non-const narrow-key tree find over the
// map<UnsignedShort, UnsignedByte> whose _M_find body sits at 0x0093DCE0.
// The owning map is not identified, so the wrapper keeps its address token.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

typedef unsigned short Rva0093E820Key;
typedef unsigned char Rva0093E820Mapped;
typedef _STL::pair<const Rva0093E820Key, Rva0093E820Mapped> Rva0093E820Value;
typedef _STL::_Rb_tree<Rva0093E820Key, Rva0093E820Value,
	_STL::_Select1st<Rva0093E820Value>, _STL::less<Rva0093E820Key>,
	_STL::allocator<Rva0093E820Value> > Rva0093E820Tree;

extern void Rva0093DCE0Target();

class Rva0093E820FindRoute
{
public:
    typedef void *(Rva0093E820FindRoute::*Call)(const Rva0093E820Key &) const;
};

struct Rva0093E820Result
{
    void *m_node;
    explicit Rva0093E820Result(void *node) : m_node(node) {}
};

class Rva0093E820Find
{
public:
    Rva0093E820Result find(const Rva0093E820Key &key) const;
};

Rva0093E820Result Rva0093E820Find::find(const Rva0093E820Key &key) const
{
    union { void (*address)(); Rva0093E820FindRoute::Call member; } route = { Rva0093DCE0Target };
    return Rva0093E820Result(
        (reinterpret_cast<const Rva0093E820FindRoute *>(this)->*route.member)(key));
}
