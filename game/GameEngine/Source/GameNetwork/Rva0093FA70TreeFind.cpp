// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// Retail 0x0093FA70 is the non-const narrow-key tree find over the
// map<UnsignedShort, UnsignedByte> whose _M_find body sits at 0x0093DCE0.
// The owning map is not identified, so the wrapper keeps its address token.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

typedef unsigned short Rva0093FA70Key;
typedef unsigned char Rva0093FA70Mapped;
typedef _STL::pair<const Rva0093FA70Key, Rva0093FA70Mapped> Rva0093FA70Value;
typedef _STL::_Rb_tree<Rva0093FA70Key, Rva0093FA70Value,
	_STL::_Select1st<Rva0093FA70Value>, _STL::less<Rva0093FA70Key>,
	_STL::allocator<Rva0093FA70Value> > Rva0093FA70Tree;

extern void Rva0093DCE0Target();

class Rva0093FA70FindRoute
{
public:
    typedef void *(Rva0093FA70FindRoute::*Call)(const Rva0093FA70Key &) const;
};

struct Rva0093FA70Result
{
    void *m_node;
    explicit Rva0093FA70Result(void *node) : m_node(node) {}
};

class Rva0093FA70Find
{
public:
    Rva0093FA70Result find(const Rva0093FA70Key &key) const;
};

Rva0093FA70Result Rva0093FA70Find::find(const Rva0093FA70Key &key) const
{
    union { void (*address)(); Rva0093FA70FindRoute::Call member; } route = { Rva0093DCE0Target };
    return Rva0093FA70Result(
        (reinterpret_cast<const Rva0093FA70FindRoute *>(this)->*route.member)(key));
}
