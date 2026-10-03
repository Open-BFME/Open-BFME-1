// cl: /O2 /MD
// Retail VA011360E8 slot6; constructor 899CB0 installs it at 899CEA.
// Complete 4B LEA EAX,[ECX+8]; RET; followed by INT3. Ghidra agrees.
// Constructor evidence establishes this opaque owner; the method keeps its RVA.
class Rva89ACB0Holder
{
public:
    void * rva00899D40();
};

void * Rva89ACB0Holder::rva00899D40()
{
    return reinterpret_cast<char *>(this) + 8;
}
