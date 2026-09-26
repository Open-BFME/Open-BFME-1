// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA090: public tree find wrapper around the matched 0x009C9AA0
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9AA0Target();

class Rva009CA090FindRoute
{
public:
    typedef void *(Rva009CA090FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CA090Result
{
    void *m_node;
    explicit Rva009CA090Result(void *node) : m_node(node) {}
};

class Rva009CA090Owner
{
public:
    Rva009CA090Result find(const AsciiString &key) const;
};

Rva009CA090Result Rva009CA090Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CA090FindRoute::Call member; } route = { Rva009C9AA0Target };
    return Rva009CA090Result(
        (reinterpret_cast<const Rva009CA090FindRoute *>(this)->*route.member)(key));
}
