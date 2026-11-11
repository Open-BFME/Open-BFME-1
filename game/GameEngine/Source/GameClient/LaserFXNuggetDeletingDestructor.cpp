// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for LaserFXNugget.
// Vtable 0x00CF3438 slots name this class (?doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z); its slot zero routes
// through ILT 0x00002ED7 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0001BA5E reaches cleanup body 0x004297D0.

// Explicit scalar-delete operations; see 20261111-explicit-scalar-wrapper.md.
void __cdecl operator delete(void *);
class Rva004297D0
{
public:
    ~Rva004297D0();
};
class Rva004297A0Wrapper
{
public:
    void *method(unsigned int flags);
};
void *Rva004297A0Wrapper::method(unsigned int flags)
{
    ((Rva004297D0 *)this)->Rva004297D0::~Rva004297D0();
    if (flags & 1)
        ::operator delete(this);
    return this;
}
