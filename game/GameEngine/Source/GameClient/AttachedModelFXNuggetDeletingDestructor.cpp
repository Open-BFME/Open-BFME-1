// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AttachedModelFXNugget.
// Vtable 0x00CF3480 slots name this class (?doFXObj@AttachedModelFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x000227D7 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00008823 reaches cleanup body 0x00429B60.

// Explicit scalar-delete operations; see 20261111-explicit-scalar-wrapper.md.
void __cdecl operator delete(void *);
class Rva00429B60
{
public:
    ~Rva00429B60();
};
class Rva00429B30Wrapper
{
public:
    void *method(unsigned int flags);
};
void *Rva00429B30Wrapper::method(unsigned int flags)
{
    ((Rva00429B60 *)this)->Rva00429B60::~Rva00429B60();
    if (flags & 1)
        ::operator delete(this);
    return this;
}
