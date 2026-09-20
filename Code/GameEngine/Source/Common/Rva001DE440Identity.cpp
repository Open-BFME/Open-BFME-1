// cl: /DNDEBUG /MD
// Retail RVA 0x001DE440 returns its this pointer unchanged.
// No caller or type evidence proves a semantic owner, so the name stays address-derived.

class Rva001DE440Identity
{
public:
    Rva001DE440Identity *identity();
};

Rva001DE440Identity *Rva001DE440Identity::identity()
{
    return this;
}
