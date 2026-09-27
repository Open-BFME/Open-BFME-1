// cl: /O2 /MD
// Retail 0x00C6C6E0 is the dynamic initializer for the global at 0x013072FC:
// in-place construction through the 0x007D8880 ScreenMotionBlurFilter ctor
// (reached via ILT 0x0002CBA6) with teardown registered at exit. The owning
// TU is unknown, so the global takes an address-derived name. The ledger name
// is address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class ScreenMotionBlurFilter
{
public:
    ScreenMotionBlurFilter();
    ~ScreenMotionBlurFilter() {}
    unsigned char m_storage[0x1C];
};
ScreenMotionBlurFilter g_rva013072FCObject;
extern "C" int __cdecl atexit(void (__cdecl *callback)());
