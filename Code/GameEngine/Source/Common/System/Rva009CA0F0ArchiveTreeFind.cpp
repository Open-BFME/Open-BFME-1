// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA0F0: public tree find wrapper around the matched 0x009C9B70
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9B70Target();

class Rva009CA0F0FindRoute
{
public:
    typedef void *(Rva009CA0F0FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CA0F0Result
{
    void *m_node;
    explicit Rva009CA0F0Result(void *node) : m_node(node) {}
};

class Rva009CA0F0Owner
{
public:
    Rva009CA0F0Result find(const AsciiString &key) const;
};

Rva009CA0F0Result Rva009CA0F0Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CA0F0FindRoute::Call member; } route = { Rva009C9B70Target };
    return Rva009CA0F0Result(
        (reinterpret_cast<const Rva009CA0F0FindRoute *>(this)->*route.member)(key));
}
