// cl: /O2 /MD
// Retail 0x00C6C640 is the dynamic initializer for the global at 0x013071E4:
// in-place construction through the 0x007D3580 ctor (reached via ILT
// 0x0000B0EB) with teardown registered at exit. The owning TU is unknown, so
// the class and the global take address-derived names. The ledger name is
// address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class Rva007D3580
{
public:
    Rva007D3580();
    ~Rva007D3580() {}
    unsigned char m_storage[0x10];
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());

Rva007D3580 g_rva013071E4Object;
