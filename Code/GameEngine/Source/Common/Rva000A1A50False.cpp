// cl: /DNDEBUG /MD /EHsc
// The carved body at retail RVA 0x000A1A50 returns false without reading
// arguments or object state. The address-derived type records that evidence
// without inventing a semantic owner.

class Rva000A1A50False
{
public:
    static bool get();
};

bool Rva000A1A50False::get()
{
    return false;
}
