// cl: /O2 /MD
// Retail 0x00C6C770 is the dynamic initializer for the global at 0x0130A45C:
// in-place construction through the 0x007E85A0 ATL CAtlWinModule ctor
// (reached via ILT 0x0001C96D) with teardown registered at exit. The owning
// TU is unknown, so the global takes an address-derived name. The ledger name
// is address-derived; the verified body is this TU's own _$E1 (see the
// object-symbol note): the source defines the global so MSVC emits the $E
// body, which runs at startup from the CRT init table.

namespace ATL
{
class CAtlWinModule
{
public:
    CAtlWinModule();
    ~CAtlWinModule();			// retail 0x007E8600 (Rva007E8600Clear.cpp)
    unsigned char m_storage[44];
};
}
extern "C" int __cdecl atexit(void (__cdecl *callback)());

// 0x0130A45C is recorded (DIR32) as ?TheBfmeObject_00C70C00@@3VGen_00C70C00Target@@A.
// Retire ?g_rva0130A45CObject@@3VCAtlWinModule@ATL@@A: define the storage under that symbol.
extern "C" { ATL::CAtlWinModule __identifier("?TheBfmeObject_00C70C00@@3VGen_00C70C00Target@@A"); }
#define g_rva0130A45CObject __identifier("?TheBfmeObject_00C70C00@@3VGen_00C70C00Target@@A")
