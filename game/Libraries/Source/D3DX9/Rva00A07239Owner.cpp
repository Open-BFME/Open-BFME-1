// cl: /O2 /MD
// Retail owner stores00A07245 and00A1253D install table VA01149008.
// Slots4/5/6/8/9/25 independently select the methods below. Each is a
// complete stack-this stdcall leaf ending RET4; Ghidra and baseline agree.
// Adjacent archive template twins do not prove the original type identity.
class Rva00A07239Owner
{
public:
    unsigned long __stdcall rva00A073E5();
    unsigned long __stdcall rva00A0745B();
    unsigned long __stdcall rva00A07468();
    unsigned long __stdcall rva00A07475();
    unsigned long __stdcall rva00A074A3();
    unsigned long __stdcall rva00A074B0();
};

unsigned long __stdcall Rva00A07239Owner::rva00A073E5()
{
    return 0;
}

unsigned long __stdcall Rva00A07239Owner::rva00A0745B()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x264);
}

unsigned long __stdcall Rva00A07239Owner::rva00A07468()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x23c);
}

unsigned long __stdcall Rva00A07239Owner::rva00A07475()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 4);
}

unsigned long __stdcall Rva00A07239Owner::rva00A074A3()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x238);
}

unsigned long __stdcall Rva00A07239Owner::rva00A074B0()
{
    return *reinterpret_cast<const unsigned long *>(
        reinterpret_cast<const char *>(this) + 0x214);
}
