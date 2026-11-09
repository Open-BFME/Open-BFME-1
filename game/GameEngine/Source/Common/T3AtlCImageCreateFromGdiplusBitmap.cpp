// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
// Open-BFME-1: this tracked VS2003 header is the genuine source of the private
// CImage::CreateFromGdiplusBitmap body.  The public Load(IStream*) call below
// is an absent-from-retail emission anchor for that inline COMDAT; retail's own
// Load body reaches the same private member through ILT 0x0003CF29.

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

namespace Rva0005FAC0Emission
{
__declspec(noinline) HRESULT EmitCImageLoad(ATL::CImage &image, IStream *stream)
{
	return image.Load(stream);
}
}
