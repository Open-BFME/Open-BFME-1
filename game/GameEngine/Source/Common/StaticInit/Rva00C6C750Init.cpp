// cl: /O2 /MD
// Retail 0x00C6C750 is the dynamic initializer for the global at 0x01309C18:
// in-place construction through the 0x007E4960 vfptr ctor (reached via ILT
// 0x00027CEB) with teardown registered at exit. The owning TU is unknown, so
// the class and the global take address-derived names. The ledger name is
// address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

class Rva007E4960
{
public:
    Rva007E4960();
    ~Rva007E4960() {}
    void *m_vptr;
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());

Rva007E4960 g_rva01309C18Object;
