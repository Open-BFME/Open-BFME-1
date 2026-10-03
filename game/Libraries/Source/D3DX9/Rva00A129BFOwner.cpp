// cl: /O2 /MD
// Retail constructor00A129BF stores table VA011490F8 at00A129D1;
// destructor00A134A0 installs it at00A134AE. Slots4/5/28/29/30/31
// independently point to these six13-byte stack-this getters. Each ends
// RET4 immediately before the next entry. Ghidra and baseline agree.
// The owner and methods keep their addresses rather than template guesses.
class Rva00A129BFOwner
{
public:
    unsigned long __stdcall rva00A12A4A();
    unsigned long __stdcall rva00A12A6B();
    unsigned long __stdcall rva00A12A78();
    unsigned long __stdcall rva00A12D75();
    unsigned long __stdcall rva00A12D82();
    unsigned long __stdcall rva00A12D8F();
    unsigned long __stdcall rva00A12D9C();
};

unsigned long __stdcall Rva00A129BFOwner::rva00A12A6B()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2b4);
}

unsigned long __stdcall Rva00A129BFOwner::rva00A12A78()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2c0);
}

unsigned long __stdcall Rva00A129BFOwner::rva00A12D75()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2b0);
}

unsigned long __stdcall Rva00A129BFOwner::rva00A12D82()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2ac);
}

unsigned long __stdcall Rva00A129BFOwner::rva00A12D8F()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2b8);
}

unsigned long __stdcall Rva00A129BFOwner::rva00A12D9C()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x2bc);
}

// Slot 1 increments receiver dword +4 and returns the updated value.
// Only the readback is volatile, preserving retail INC [this+4] followed
// by a separate load. This does not assert an original volatile member type.
unsigned long __stdcall Rva00A129BFOwner::rva00A12A4A()
{
    unsigned long *value = reinterpret_cast<unsigned long *>(
        reinterpret_cast<char *>(this) + 4);
    ++*value;
    return *static_cast<volatile unsigned long *>(value);
}
