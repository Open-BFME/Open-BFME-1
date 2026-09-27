// cl: /O2 /MD
// Retail 0x00C6C6A0 is the dynamic initializer for the global at 0x01307284:
// in-place construction through the 0x007D8580 ScreenHilightFilter ctor
// (reached via ILT 0x0001ABDB) with teardown registered at exit. The owning
// TU is unknown, so the global takes an address-derived name. The ledger name
// is address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class ScreenHilightFilter
{
public:
    ScreenHilightFilter();
    ~ScreenHilightFilter() {}
    unsigned char m_storage[0x34];
};
ScreenHilightFilter g_rva01307284Object;
extern "C" int __cdecl atexit(void (__cdecl *callback)());
