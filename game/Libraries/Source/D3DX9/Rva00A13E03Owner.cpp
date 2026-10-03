// cl: /O2 /MD
// Retail constructor00A13E03 stores table VA011491A8 at00A13E15;
// destructor00A148DD installs it at00A148EB. Slots4/5/28/29/30/31
// independently point to these six13-byte stack-this getters. Each ends
// RET4 immediately before the next entry. Ghidra and baseline agree.
// The owner and methods keep their addresses rather than template guesses.
class Rva00A13E03Owner
{
public:
    unsigned long __stdcall rva00A13EAE();
    unsigned long __stdcall rva00A13EBB();
    unsigned long __stdcall rva00A141B8();
    unsigned long __stdcall rva00A141C5();
    unsigned long __stdcall rva00A141D2();
    unsigned long __stdcall rva00A141DF();
};

unsigned long __stdcall Rva00A13E03Owner::rva00A13EAE()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2b4);
}

unsigned long __stdcall Rva00A13E03Owner::rva00A13EBB()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2c0);
}

unsigned long __stdcall Rva00A13E03Owner::rva00A141B8()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2b0);
}

unsigned long __stdcall Rva00A13E03Owner::rva00A141C5()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2ac);
}

unsigned long __stdcall Rva00A13E03Owner::rva00A141D2()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2b8);
}

unsigned long __stdcall Rva00A13E03Owner::rva00A141DF()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2bc);
}
