// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA020: public tree find wrapper around the matched 0x009C9AA0
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9AA0Target();

class Rva009CA020FindRoute
{
public:
    typedef void *(Rva009CA020FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CA020Result
{
    void *m_node;
    explicit Rva009CA020Result(void *node) : m_node(node) {}
};

class Rva009CA020Owner
{
public:
    Rva009CA020Result find(const AsciiString &key) const;
};

Rva009CA020Result Rva009CA020Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CA020FindRoute::Call member; } route = { Rva009C9AA0Target };
    return Rva009CA020Result(
        (reinterpret_cast<const Rva009CA020FindRoute *>(this)->*route.member)(key));
}
