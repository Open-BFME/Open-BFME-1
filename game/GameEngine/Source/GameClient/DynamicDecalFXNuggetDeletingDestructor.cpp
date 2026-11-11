// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DynamicDecalFXNugget.
// Vtable 0x00CF3420 slots name this class (?doFXObj@DynamicDecalFXNugget@@UBEXPBVObject@@0@Z); its slot zero routes
// through ILT 0x00027F52 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0002E3FC reaches cleanup body 0x004293F0.

// Explicit scalar-delete operations; see 20261111-explicit-scalar-wrapper.md.
void __cdecl operator delete(void *);
class Rva004293F0
{
public:
    ~Rva004293F0();
};
class Rva004293C0Wrapper
{
public:
    void *method(unsigned int flags);
};
void *Rva004293C0Wrapper::method(unsigned int flags)
{
    ((Rva004293F0 *)this)->Rva004293F0::~Rva004293F0();
    if (flags & 1)
        ::operator delete(this);
    return this;
}
