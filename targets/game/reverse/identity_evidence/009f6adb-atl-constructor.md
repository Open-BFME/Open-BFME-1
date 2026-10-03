# ATL base-module constructor at RVA009F6ADB

The matched CRT initializer at C6E34D calls this exact entry at C6E352
with ECX=&g_rva0134FB48 and no stack arguments. Its existing declaration
names `Rva009F6ADBObject` and establishes the constructor contract; retain
that address-qualified binding rather than introduce another owner name.
Retail and Ghidra read_memory at VA00DF6ADB agree: complete171B through
RET009F6B85, immediately followed by the independently matched
AddResourceInstance entry009F6B86. There is no intervening INT3 padding.

VS2003 atlmfc/src/atl/atls/atlbase.cpp lines28..64 independently supplies
the complete constructor algorithm. Native atlcore.h declares the60B
_ATL_BASE_MODULE70 layout, its critical section at+18, and resource array
at+30. The TU includes this header and the native PlatformSDK declarations.
The already-matched26B Rva009F69B1 base constructor initializes this same
layout. A view derived from the native layout preserves that existing
callee symbol without inventing another critical-section constructor.
The two /I paths use build.py's documented relocatable Vc7 path resolver.

With /O1 /GS /MD, the native algorithm matches171B and all nine relocations:

| Offset | Binding | Independent evidence |
| --- | --- | --- |
| 0C | ___security_cookie, VA012DBDB0 | Existing /GS data pin and checker |
| 17 | Rva009F69B1 constructor | Existing matched26B body |
| 1C | ___ImageBase, VA00400000 | PE optional-header image base; native source uses &__ImageBase |
| 3C | _memset via009F75C4 | Existing import route;148B OSVERSIONINFO zeroing |
| 50 | GetVersionExA IAT VA01358E20 | Existing import binding and native source |
| 87 | GUID_ATLVer70, VA01145854 | All16 retail bytes e03d4c396f3cd211817b00c04f797ab7 equal native atlbase.cpp line26 |
| 8C | ATL::CComCriticalSection::Init via0003AEC7 | Existing canonical pin and matched007E5860 body |
| 96 | ATL::CAtlBaseModule::m_bInitFailed, VA0130A440 | Existing DIR32 binding; matched CAtlWinModule constructor007E85A0 writes this same flag on Init failure |
| A2 | @__security_check_cookie@4,009F74F4 | Existing compiler helper binding |

The native version constant is0x710, and the Win32 version comparisons
retain the native NT5/Win98 behavior. Strict add_match/build passes1/1,
including five DIR32 references. No pin, header, shim or baseline changes.
