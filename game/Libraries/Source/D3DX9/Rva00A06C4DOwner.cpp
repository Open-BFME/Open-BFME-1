// cl: /O2 /MD
// Retail table VA01148F90 is installed at RVA00A1209C and00A06C59.
// Slot25 points directly to00A06DF9: XOR EAX,EAX; RET4 (five bytes).
// Ghidra memory and the baseline PE agree; the following00A06DFE is
// independently table-backed. Archive template twins leave identity opaque.
class Rva00A06C4DOwner
{
public:
    unsigned long __stdcall rva00A06DF9();
    unsigned long __stdcall rva00A06E6F();
    unsigned long __stdcall rva00A06E7C();
    unsigned long __stdcall rva00A06E89();
    unsigned long __stdcall rva00A06EB7();
    unsigned long __stdcall rva00A06EC4();
};

unsigned long __stdcall Rva00A06C4DOwner::rva00A06DF9()
{
    return 0;
}

// The same table's slots4/5/6/8/9 independently point to these entries.
// Each reads stack-this and one dword, then RET4. Sizes are13/13/10/13/13;
// the next body begins immediately after each return (no padding included).
unsigned long __stdcall Rva00A06C4DOwner::rva00A06E6F()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x264);
}

unsigned long __stdcall Rva00A06C4DOwner::rva00A06E7C()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x23c);
}

unsigned long __stdcall Rva00A06C4DOwner::rva00A06E89()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 4);
}

unsigned long __stdcall Rva00A06C4DOwner::rva00A06EB7()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x238);
}

unsigned long __stdcall Rva00A06C4DOwner::rva00A06EC4()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x214);
}
