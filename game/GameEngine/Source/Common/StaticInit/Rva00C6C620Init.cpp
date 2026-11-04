// cl: /O2 /MD
// Retail 0x00C6C620 is the dynamic initializer for the global at 0x013071D4:
// in-place construction through the 0x007D2360 ctor (reached via ILT
// 0x00025AA9) with teardown registered at exit. The owning TU is unknown, so
// the class and the global take address-derived names. The ledger name is
// address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table. The real +0 store is
// vtable 0x011289D4 (seven slots, installed only by this ctor); this TU
// models the object as plain words the same way the owning ctor TU does.

class Rva007D2360
{
public:
    Rva007D2360();
    ~Rva007D2360();   // out of line: the atexit teardown jumps to it
    void *m_at00;
    int m_at04;
    int m_at08;
    int m_at0C;
};

extern "C" int __cdecl atexit(void (__cdecl *callback)());

// 0x013071D4 is recorded (DIR32) as ?Rva00F071D4Target986B@@3PADA;
// define the storage under that symbol.
// Retire ?g_rva013071D4Object@@3VRva007D2360@@A
extern "C" { Rva007D2360 __identifier("?Rva00F071D4Target986B@@3PADA"); }
