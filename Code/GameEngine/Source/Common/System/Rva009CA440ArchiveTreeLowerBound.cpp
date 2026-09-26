// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA440: public tree lower_bound wrapper around the matched 0x009C9CE0
// _M_lower_bound specialization. The address-derived callable is pinned to that
// proven target. The tree owner remains unproven, so the ledger identity keeps this address.

class AsciiString;
extern void Rva009C9CE0Target();

class Rva009CA440LowerBoundRoute
{
public:
    typedef void *(Rva009CA440LowerBoundRoute::*Call)(const AsciiString &) const;
};

struct Rva009CA440Result
{
    void *m_node;
    explicit Rva009CA440Result(void *node) : m_node(node) {}
};

class Rva009CA440Owner
{
public:
    Rva009CA440Result lower_bound(const AsciiString &key) const;
};

Rva009CA440Result Rva009CA440Owner::lower_bound(const AsciiString &key) const
{
    union { void (*address)(); Rva009CA440LowerBoundRoute::Call member; } route = { Rva009C9CE0Target };
    return Rva009CA440Result(
        (reinterpret_cast<const Rva009CA440LowerBoundRoute *>(this)->*route.member)(key));
}
