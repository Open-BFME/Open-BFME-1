// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA070: public tree find wrapper around the matched 0x009C9AA0
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9AA0Target();

class Rva009CA070FindRoute
{
public:
    typedef void *(Rva009CA070FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CA070Result
{
    void *m_node;
    explicit Rva009CA070Result(void *node) : m_node(node) {}
};

class Rva009CA070Owner
{
public:
    Rva009CA070Result find(const AsciiString &key) const;
};

Rva009CA070Result Rva009CA070Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CA070FindRoute::Call member; } route = { Rva009C9AA0Target };
    return Rva009CA070Result(
        (reinterpret_cast<const Rva009CA070FindRoute *>(this)->*route.member)(key));
}
