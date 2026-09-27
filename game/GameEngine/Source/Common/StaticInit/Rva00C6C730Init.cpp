// cl: /O2 /MD
// Retail 0x00C6C730 is the dynamic initializer for the global at 0x013073C0:
// in-place construction through the 0x007DCA80 ctor (reached via ILT
// 0x0001616C) with teardown registered at exit. The owning TU is unknown, so
// the class and the global take address-derived names. The ledger name is
// address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class Rva007DCA80
{
public:
    Rva007DCA80();
    ~Rva007DCA80() {}
    unsigned char m_storage[0x60];
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());

Rva007DCA80 g_rva013073C0Object;
