// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
// Open-BFME5: the VS2003 ATL CImage::Load(LPCTSTR) inline body at retail
// 0x00060010.  The header's ANSI CT2W temporary, GDI+ Bitmap lifetime, and
// private CreateFromGdiplusBitmap call are the witnessed retail sequence.

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

typedef HRESULT (ATL::CImage::*Rva00060010CImageLoadAnsi)(LPCSTR);

Rva00060010CImageLoadAnsi rva00060010CImageLoadAnsi = &ATL::CImage::Load;
