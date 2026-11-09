// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
// Open-BFME5: the VS2003 ATL CImage::Load(LPCTSTR) inline body at retail
// 0x00060010.  The header's ANSI CT2W temporary, GDI+ Bitmap lifetime, and
// private CreateFromGdiplusBitmap call are the witnessed retail sequence.

// Retail's ATL::GetStringTypeExWFake and CompareStringWFake are the
// W3Win9xGetStringType.cpp and W3Win9xCompareString.cpp bodies; rename the
// header's inline copies so this TU does not emit competing COMDATs.
// Retail imports KERNEL32!GetStringTypeA (not ExA) and KERNEL32!lstrcmpi
// (not lstrcmpiA): the cstringt.h Win9x fallbacks call the ExA/A forms, so
// spell them retail's way. windows.h comes first on purpose: its own
// `#define lstrcmpi lstrcmpiA` would neutralize the swap, and its include
// guards keep the second inclusion (through atlimage.h) from reverting it.
#include <windows.h>
// windows.h maps the generic lstrcmpi to lstrcmpiA; drop that mapping and
// declare retail's undecorated KERNEL32!lstrcmpi import instead, so both the
// bare uses in ATL headers and the swapped lstrcmpiA below converge on it.
#pragma push_macro("lstrcmpi")
#undef lstrcmpi
extern "C" __declspec(dllimport) int __stdcall lstrcmpi(const char *a, const char *b);
#pragma push_macro("GetStringTypeExWFake")
#pragma push_macro("CompareStringWFake")
#pragma push_macro("GetStringTypeExA")
#pragma push_macro("lstrcmpiA")
#define GetStringTypeExWFake GetStringTypeExWFakeCStringT
#define CompareStringWFake CompareStringWFakeCStringT
#define GetStringTypeExA GetStringTypeA
#define lstrcmpiA lstrcmpi
#include <atlimage.h>
#pragma pop_macro("lstrcmpiA")
#pragma pop_macro("GetStringTypeExA")
#pragma pop_macro("CompareStringWFake")
#pragma pop_macro("GetStringTypeExWFake")
#pragma pop_macro("lstrcmpi")

typedef HRESULT (ATL::CImage::*Rva00060010CImageLoadAnsi)(LPCSTR);

Rva00060010CImageLoadAnsi rva00060010CImageLoadAnsi = &ATL::CImage::Load;
