// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
// Open-BFME-1: this tracked VS2003 header is the genuine source of the private
// CImage::CreateFromGdiplusBitmap body.  The public Load(IStream*) call below
// is an absent-from-retail emission anchor for that inline COMDAT; retail's own
// Load body reaches the same private member through ILT 0x0003CF29.

// Retail's ATL::GetStringTypeExWFake and CompareStringWFake are the
// W3Win9xGetStringType.cpp and W3Win9xCompareString.cpp bodies; rename the
// header's inline copies so this TU does not emit competing COMDATs.
#pragma push_macro("GetStringTypeExWFake")
#pragma push_macro("CompareStringWFake")
#define GetStringTypeExWFake GetStringTypeExWFakeCStringT
#define CompareStringWFake CompareStringWFakeCStringT
#include <atlimage.h>
#pragma pop_macro("CompareStringWFake")
#pragma pop_macro("GetStringTypeExWFake")

namespace Rva0005FAC0Emission
{
__declspec(noinline) HRESULT EmitCImageLoad(ATL::CImage &image, IStream *stream)
{
	return image.Load(stream);
}
}
