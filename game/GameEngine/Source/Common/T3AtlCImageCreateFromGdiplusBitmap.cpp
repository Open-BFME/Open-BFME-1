// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
// Open-BFME-1: this tracked VS2003 header is the genuine source of the private
// CImage::CreateFromGdiplusBitmap body.  The public Load(IStream*) call below
// is an absent-from-retail emission anchor for that inline COMDAT; retail's own
// Load body reaches the same private member through ILT 0x0003CF29.

#include <atlimage.h>

namespace Rva0005FAC0Emission
{
__declspec(noinline) HRESULT EmitCImageLoad(ATL::CImage &image, IStream *stream)
{
	return image.Load(stream);
}
}
