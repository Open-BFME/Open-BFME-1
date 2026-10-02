// cl: /O2 /MD
// Retail 0x00C6C680 is the dynamic initializer for the global at 0x01307228:
// in-place construction through the 0x007D6B70 ctor (reached via ILT
// 0x0002821D) with teardown registered at exit. The owning TU is unknown, so
// the class and the global take address-derived names. The ledger name is
// address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class Rva007D6B70
{
public:
    Rva007D6B70();
    ~Rva007D6B70();
    unsigned char m_storage[0x34];
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());

Rva007D6B70 g_rva01307228Object;
