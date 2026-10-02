// cl: /O2 /MD
// Retail 0x00C6C480 is the dynamic initializer for the global at 0x012F878C:
// in-place construction through the CriticalSectionClass default ctor
// (0x009DB420) with teardown registered at exit. The owning TU is unknown, so
// the global takes an address-derived name; the class is redeclared locally
// with the same ctor shape as game/Libraries/Source/WWVegas/WWLib/mutex.h.
// The ledger name is address-derived; the verified body is this TU's own _$E1
// (see the object-symbol note): the source defines the global so MSVC emits
// the $E body, which runs at startup from the CRT init table.

class CriticalSectionClass
{
public:
    CriticalSectionClass();
    ~CriticalSectionClass();
    void *m_handle;
    unsigned m_locked;
};
extern "C" int __cdecl atexit(void (__cdecl *callback)());

CriticalSectionClass g_rva012F878CObject;
