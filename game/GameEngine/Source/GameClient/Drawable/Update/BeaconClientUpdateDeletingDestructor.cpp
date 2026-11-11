// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BeaconClientUpdate scalar-deleting destructor at retail RVA
// 0x00603210 (30 bytes). The exact constructor at 0x006030C0 installs vtable
// 0x01115248, whose slot zero routes through ILT 0x00041E25 to this wrapper.
// The named module factory at 0x00121B70 corroborates identity; the complete
// destructor is called through ILT 0x0003B31D.

// Explicit scalar-delete operations; see 20261111-explicit-scalar-wrapper.md.
void __cdecl operator delete(void *);
class Rva00603120TailDtor
{
public:
    virtual ~Rva00603120TailDtor();
};
class Rva00603210Wrapper
{
public:
    void *method(unsigned int flags);
};
void *Rva00603210Wrapper::method(unsigned int flags)
{
    ((Rva00603120TailDtor *)this)->Rva00603120TailDtor::~Rva00603120TailDtor();
    if (flags & 1)
        ::operator delete(this);
    return this;
}
