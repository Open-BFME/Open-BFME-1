// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CD0B0: public tree find wrapper around the matched 0x009C9B70
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9B70Target();

class Rva009CD0B0FindRoute
{
public:
    typedef void *(Rva009CD0B0FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CD0B0Result
{
    void *m_node;
    explicit Rva009CD0B0Result(void *node) : m_node(node) {}
};

class Rva009CD0B0Owner
{
public:
    Rva009CD0B0Result find(const AsciiString &key) const;
};

Rva009CD0B0Result Rva009CD0B0Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CD0B0FindRoute::Call member; } route = { Rva009C9B70Target };
    return Rva009CD0B0Result(
        (reinterpret_cast<const Rva009CD0B0FindRoute *>(this)->*route.member)(key));
}
