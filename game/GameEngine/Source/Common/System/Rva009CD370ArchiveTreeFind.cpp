// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CD370: public tree find wrapper around the matched 0x009C9B70
// _M_find specialization. The address-derived callable is pinned to that
// proven target. Several retail copies share these bytes, so the
// ledger identity must keep this address until a caller selects one copy.

class AsciiString;
extern void Rva009C9B70Target();

class Rva009CD370FindRoute
{
public:
    typedef void *(Rva009CD370FindRoute::*Call)(const AsciiString &) const;
};

struct Rva009CD370Result
{
    void *m_node;
    explicit Rva009CD370Result(void *node) : m_node(node) {}
};

class Rva009CD370Owner
{
public:
    Rva009CD370Result find(const AsciiString &key) const;
};

Rva009CD370Result Rva009CD370Owner::find(const AsciiString &key) const
{
    union { void (*address)(); Rva009CD370FindRoute::Call member; } route = { Rva009C9B70Target };
    return Rva009CD370Result(
        (reinterpret_cast<const Rva009CD370FindRoute *>(this)->*route.member)(key));
}
