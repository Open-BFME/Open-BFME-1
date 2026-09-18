// cl: /DNDEBUG /MD /EHsc
// The carved body at retail RVA 0x00214D70 is ret 4, which consumes one
// four-byte argument and performs no work. The address-derived type records
// that calling convention without inventing a semantic owner.

class Rva00214D70Noop
{
public:
    void call(int unused);
};

void Rva00214D70Noop::call(int unused)
{
}
