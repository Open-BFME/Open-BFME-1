// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BfmeHolderCU.
// Constructor 0x005DD290 installs dedicated vtable 0x00D1126C; its slot
// zero routes through ILT 0x00003E3B to this 30-byte wrapper, whose complete
// destructor route ILT 0x0000CC16 reaches cleanup body 0x005DD320.

// Explicit scalar-delete semantics avoid synthesizing a second complete dtor.
void __cdecl operator delete(void *);
class Rva005DD320MultiTailDtor
{
public:
    virtual ~Rva005DD320MultiTailDtor();
};
class Rva005DD340Wrapper
{
public:
    void *method(unsigned int flags);
};
void *Rva005DD340Wrapper::method(unsigned int flags)
{
    ((Rva005DD320MultiTailDtor *)this)->Rva005DD320MultiTailDtor::~Rva005DD320MultiTailDtor();
    if (flags & 1)
        ::operator delete(this);
    return this;
}
