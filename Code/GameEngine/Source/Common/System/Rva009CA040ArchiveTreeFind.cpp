// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA040: public tree find wrapper around the matched 0x009C9B70
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9B70Target();

class Rva009CA040FindRoute
{
public:
    typedef void *(Rva009CA040FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CA040Result
{
    void *m_node;
    explicit Rva009CA040Result(void *node) : m_node(node) {}
};

class Rva009CA040Owner
{
public:
    Rva009CA040Result find(const AsciiString &key) const;
};

Rva009CA040Result Rva009CA040Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CA040FindRoute::Call member; } route = { Rva009C9B70Target };
    return Rva009CA040Result(
        (reinterpret_cast<const Rva009CA040FindRoute *>(this)->*route.member)(key));
}
