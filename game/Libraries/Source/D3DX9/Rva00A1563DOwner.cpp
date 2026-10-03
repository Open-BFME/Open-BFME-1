// cl: /O2 /MD
// Retail stores at 00A15646 and 00A1E1E4 install table VA011492A0.
// Slots 3/4/15/16 independently point to these four 13-byte getters.
// Each loads stack-this, reads one dword and ends RET4 before the next
// table-backed or claimed body. Ghidra and baseline bytes agree.
// No semantic owner, member or method identity is asserted.
class Rva00A1563DOwner
{
public:
    unsigned long __stdcall rva00A157F7();
    unsigned long __stdcall rva00A15804();
    unsigned long __stdcall rva00A15A8B();
    unsigned long __stdcall rva00A15A98();
};

unsigned long __stdcall Rva00A1563DOwner::rva00A157F7()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x36c);
}

unsigned long __stdcall Rva00A1563DOwner::rva00A15804()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x370);
}

unsigned long __stdcall Rva00A1563DOwner::rva00A15A8B()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x380);
}

unsigned long __stdcall Rva00A1563DOwner::rva00A15A98()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x384);
}
