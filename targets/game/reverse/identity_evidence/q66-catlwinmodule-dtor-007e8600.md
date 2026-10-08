# ATL::CAtlWinModule::~CAtlWinModule at 0x007E8600

The global at VA 0x0130A45C is built by the matched dynamic initializer
0x00C6C770: `mov ecx,0x130A45C; call` ILT 0x1C96D -> 0x007E85A0, the matched
ATL 7.1 `??0CAtlWinModule@ATL@@QAE@XZ` (AtlWinModuleConstructor.cpp), then
`push 0x00C70C00; call _atexit`. The registered teardown 0x00C70C00 is
`mov ecx,0x130A45C; jmp` ILT 0xEAFC -> 0x007E8600. So 0x007E8600 is the
destructor the compiler registers for a CAtlWinModule global.

The 47-byte body matches ATL 7.1 atlbase.h exactly: `~CAtlWinModule()`
calls `Term()` = `AtlWinModuleTerm(this, _AtlBaseModule.GetModuleInstance())`
(stdcall push of the dword at 0x0134FB4C and `this`, call ILT 0x476E0), then
the `m_rgWindowClassAtoms` CSimpleArray<ATOM> member destructor inlines
`RemoveAll()`: free m_aT at +0x20 and zero m_aT/m_nSize/m_nAllocSize at
+0x20/+0x24/+0x28, the offsets of that member in the 44-byte
_ATL_WIN_MODULE70 layout the constructor builds.

The old row `?run@Rva007E8600@@QAEXXZ` was an address-derived placeholder for
the same bytes; nothing called it by name. Callees keep their existing
address-derived names (rva007e8530_bar, g_rva007e8530).
