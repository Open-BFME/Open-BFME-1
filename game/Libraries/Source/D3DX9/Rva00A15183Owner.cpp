// cl: /O2 /MD
// Retail stores at 00A1518C and 00A1E076 install table VA01149250.
// Slots 3/4/15/16 independently point to these four 13-byte getters.
// Each loads stack-this, reads one dword and ends RET4 before the next
// table-backed or claimed body. Ghidra and baseline bytes agree.
// No semantic owner, member or method identity is asserted.
class Rva00A15183Owner
{
public:
    unsigned long __stdcall rva00A152E9();
    unsigned long __stdcall rva00A1533D();
    unsigned long __stdcall rva00A1534A();
    unsigned long __stdcall rva00A155C3();
    unsigned long __stdcall rva00A155D0();
};

unsigned long __stdcall Rva00A15183Owner::rva00A1533D()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x36c);
}

unsigned long __stdcall Rva00A15183Owner::rva00A1534A()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x370);
}

unsigned long __stdcall Rva00A15183Owner::rva00A155C3()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x380);
}

unsigned long __stdcall Rva00A15183Owner::rva00A155D0()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x384);
}

// Table slot 1 increments receiver dword +4 and returns its new value.
// Volatile readback preserves the separate retail load after the increment.
// It does not claim an original volatile member type.
unsigned long __stdcall Rva00A15183Owner::rva00A152E9()
{
    unsigned long *value = reinterpret_cast<unsigned long *>(
        reinterpret_cast<char *>(this) + 4);
    ++*value;
    return *static_cast<volatile unsigned long *>(value);
}
