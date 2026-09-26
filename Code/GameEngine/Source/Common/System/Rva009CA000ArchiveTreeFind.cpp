// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA000: public tree find wrapper around the matched 0x009C9AA0
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9AA0Target();

class Rva009CA000FindRoute
{
public:
    typedef void *(Rva009CA000FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CA000Result
{
    void *m_node;
    explicit Rva009CA000Result(void *node) : m_node(node) {}
};

class Rva009CA000Owner
{
public:
    Rva009CA000Result find(const AsciiString &key) const;
};

Rva009CA000Result Rva009CA000Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CA000FindRoute::Call member; } route = { Rva009C9AA0Target };
    return Rva009CA000Result(
        (reinterpret_cast<const Rva009CA000FindRoute *>(this)->*route.member)(key));
}
