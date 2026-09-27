// cl: /O2 /MD
// Retail 0x00C6C6C0 is the dynamic initializer for the global at 0x013072B8:
// in-place construction through the 0x007D85C0 ctor (reached via ILT
// 0x00035D87) with teardown registered at exit. The owning TU is unknown, so
// the class and the global take address-derived names. The ledger name is
// address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class Rva007D85C0
{
public:
    Rva007D85C0();
    ~Rva007D85C0() {}
    unsigned char m_storage[0x2C];
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());

Rva007D85C0 g_rva013072B8Object;
